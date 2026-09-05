import usb.core
import usb.util
import usb.backend.libusb1
import sys
import time
import os
import traceback

LIBUSB_ENDPOINT_IN = 0x80
LIBUSB_ENDPOINT_OUT = 0x00

# Test settings
TIMEOUT = 6000
VENDOR_ID = 0x1209
PRODUCT_ID = 0x0003
IE_CHOICE1 = 1
OE_CHOICE1 = 1
IE_CHOICE2 = 2
OE_CHOICE2 = 2
# Note wr_len must not exceed the DEV_EXPECTED_RD_LEN (this is also the device max read len)
DEV_EXPECTED_RD_LEN = 0xffffffff
CMD_RATE_TEST = 0x01
CMD_VERIFY_TEST = 0x02

IE_CHOICE1_CODE = IE_CHOICE1 | LIBUSB_ENDPOINT_IN
OE_CHOICE1_CODE = OE_CHOICE1 | LIBUSB_ENDPOINT_OUT
IE_CHOICE2_CODE = IE_CHOICE2 | LIBUSB_ENDPOINT_IN
OE_CHOICE2_CODE = OE_CHOICE2 | LIBUSB_ENDPOINT_OUT

# Units
KB = float(1000)
MB = float(1000000)

def format_bytes(size):
    B = float(size)
    if B < KB:
        return '{0:.2f} B/s'.format(B)
    elif B < MB:
        return '{0:.2f} KB/s'.format(B/KB)
    else :
        return '{0:.2f} MB/s'.format(B/MB)

def verify(rxdata, act_len, i):
    mismatch_count = 0
    test_count = 0

    for j in range(act_len):
        if rxdata[j] != test_count:
            mismatch_count = mismatch_count + 1
        test_count = (test_count + 1) % 256
    
    if mismatch_count > 0:
        print("Run {:3d}: Verify {}/{} {} errors (failed)".format(i, act_len - mismatch_count, act_len, mismatch_count))
    else:
        print("Run {:3d}: Verify {}/{} {} errors (passed)".format(i, act_len, act_len, mismatch_count))

def main():
    try:
        if len(sys.argv) != 7:
            raise ValueError("Not enough commandline parameters")
        
        cmd_str = sys.argv[1]
        wr_len1 = int(sys.argv[2])
        rd_len1 = int(sys.argv[3])
        wr_len2 = int(sys.argv[4])
        rd_len2 = int(sys.argv[5])
        num_runs = int(sys.argv[6])
        
        if cmd_str == "rate":
            cmd_code = CMD_RATE_TEST
        elif cmd_str == "verify":
            cmd_code = CMD_VERIFY_TEST
        else:
            raise ValueError("Commandline parameter 2 is an invalid command")
        
        backend = usb.backend.libusb1.get_backend()  # Find and load USB backend library by OS search path
        if backend is None:
            if os.name == 'nt':
                backend = usb.backend.libusb1.get_backend(find_library=lambda x: "./libusb-1.0.dll")  # Find and load libusb from current directory
            else:
                backend = usb.backend.libusb1.get_backend(find_library=lambda x: "./libusb-1.0.so")  # Find and load libusb from current directory

        if backend is None:
            raise ValueError('No USB backend found (libusb .dll/.so)')
            sys.exit(1)

        print('USB backend found:', backend.lib)

        dev = usb.core.find(idVendor=VENDOR_ID, idProduct=PRODUCT_ID)

        if dev is None:
            raise ValueError('USB device not found. VID PID: 0x{0:04x} 0x{1:04x}'.format(VENDOR_ID, PRODUCT_ID))
            sys.exit(1)

        # Set the active configuration. With no arguments, the first configuration will be the active one
        dev.set_configuration()

        #print(dev) # Show all device info

        str_manuf = usb.util.get_string(dev, dev.iManufacturer)
        str_product = usb.util.get_string(dev, dev.iProduct)
        str_serial = usb.util.get_string(dev, dev.iSerialNumber)
        print('VID PID     : 0x{0:04x} 0x{1:04x}'.format(VENDOR_ID, PRODUCT_ID))
        print('Manufacturer: ' + str_manuf)
        print('Product     : ' + str_product)
        print('Serial      : ' + str_serial)
        
        # Find IN and OUT EP descriptor
        oe1 = None
        ie1 = None
        oe2 = None
        ie2 = None
        cfg = dev.get_active_configuration()
        for intf in cfg:
            if intf.bAlternateSetting == 0:
                for ep in intf:
                    if ep.bEndpointAddress == OE_CHOICE1_CODE: oe1 = ep
                    if ep.bEndpointAddress == IE_CHOICE1_CODE: ie1 = ep
                    if ep.bEndpointAddress == OE_CHOICE2_CODE: oe2 = ep
                    if ep.bEndpointAddress == IE_CHOICE2_CODE: ie2 = ep
        
        if oe1 is None:
            raise ValueError('Failed to find OUT endpoint descriptor')
            sys.exit(1)
            
        if ie1 is None:
            raise ValueError('Failed to find IN endpoint descriptor')
            sys.exit(1)
            
        if oe2 is None:
            raise ValueError('Failed to find OUT endpoint descriptor')
            sys.exit(1)
            
        if ie2 is None:
            raise ValueError('Failed to find IN endpoint descriptor')
            sys.exit(1)
            
        print('OUT EP{0} MPS : {1}'.format(OE_CHOICE1, oe1.wMaxPacketSize))
        print('IN  EP{0} MPS : {1}'.format(IE_CHOICE1, ie1.wMaxPacketSize))
        print('OUT EP{0} MPS : {1}'.format(OE_CHOICE2, oe2.wMaxPacketSize))
        print('IN  EP{0} MPS : {1}'.format(IE_CHOICE2, ie2.wMaxPacketSize))

        # Display test settings
        print('\nTest settings (OUT = host to dev, IN = dev to host):')
        print('OUT EP{0} transfer len: {1} bytes'.format(OE_CHOICE1, wr_len1))
        print('IN  EP{0} transfer len: {1} bytes'.format(IE_CHOICE1, rd_len1))
        print('OUT EP{0} transfer len: {1} bytes'.format(OE_CHOICE2, wr_len2))
        print('IN  EP{0} transfer len: {1} bytes'.format(IE_CHOICE2, rd_len2))
        print('Number of runs: {0}'.format(num_runs))

        # Build command message to send
        cmd = bytes([cmd_code]) + rd_len1.to_bytes(4, "little") + bytearray(wr_len1 - 5)

        # Run first test
        print('\nTransfer rate test1:')
        print('Endpoints: Write = OUT EP{0} Read = IN EP{1}'.format(OE_CHOICE1, IE_CHOICE1))
        avg_in1 = 0
        min_in1 = 0
        max_in1 = 0
        avg_out1 = 0
        min_out1 = 0
        max_out1 = 0
        for i in range(num_runs):
            # Write to device
            time_begin = time.perf_counter()
            dev.write(OE_CHOICE1_CODE, cmd, TIMEOUT)
            if wr_len1 < DEV_EXPECTED_RD_LEN: dev.write(OE_CHOICE1_CODE, None, TIMEOUT)  # Write ZLP to end the transfer early
            #if wr_len1 % oe1.wMaxPacketSize == 0: dev.write(OE_CHOICE1_CODE, None, TIMEOUT)  # Write ZLP to end the transfer early
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_out1 = wr_len1 / elapsed
            else:
                rate_out1 = 0
            avg_out1 = (i * avg_out1 + rate_out1) / (i + 1)
            if i == 0 or rate_out1 < min_out1: min_out1 = rate_out1
            if rate_out1 > max_out1: max_out1 = rate_out1
            
            # Read from device
            time_begin = time.perf_counter()
            rxdata = dev.read(IE_CHOICE1_CODE, rd_len1, TIMEOUT)
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_in1 = rd_len1 / elapsed
            else:
                rate_in1 = 0
            avg_in1 = (i * avg_in1 + rate_in1) / (i + 1)
            if i == 0 or rate_in1 < min_in1: min_in1 = rate_in1
            if rate_in1 > max_in1: max_in1 = rate_in1
            
            if cmd_code == CMD_VERIFY_TEST:
                verify(rxdata, len(rxdata), i)
            else:
                print('Run {0:3d}: {1} {2}'.format(i, format_bytes(rate_out1), format_bytes(rate_in1)))

        # Build command message to send
        cmd = bytes([CMD_RATE_TEST]) + rd_len2.to_bytes(4, "little") + bytearray(wr_len2 - 5)

        # Run second test
        print('\nTransfer rate test2:')
        print('Endpoints: Write = OUT EP{0} Read = IN EP{1}'.format(OE_CHOICE2, IE_CHOICE2))
        avg_in2 = 0
        min_in2 = 0
        max_in2 = 0
        avg_out2 = 0
        min_out2 = 0
        max_out2 = 0
        for i in range(num_runs):
            # Write to device
            time_begin = time.perf_counter()
            dev.write(OE_CHOICE2_CODE, cmd, TIMEOUT)  # Write to host
            if wr_len2 < DEV_EXPECTED_RD_LEN: dev.write(OE_CHOICE2_CODE, None, TIMEOUT)  # Write ZLP to end the transfer early
            #if wr_len2 % oe2.wMaxPacketSize == 0: dev.write(OE_CHOICE2_CODE, None, TIMEOUT)  # Write ZLP to end the transfer early
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_out2 = wr_len2 / elapsed
            else:
                rate_out2 = 0
            avg_out2 = (i * avg_out2 + rate_out2) / (i + 1)
            if i == 0 or rate_out2 < min_out2: min_out2 = rate_out2
            if rate_out2 > max_out2: max_out2 = rate_out2
            
            # Read from device
            time_begin = time.perf_counter()
            rxdata2 = dev.read(IE_CHOICE2_CODE, rd_len2, TIMEOUT)  # Read from host
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_in2 = rd_len2 / elapsed
            else:
                rate_in2 = 0
            avg_in2 = (i * avg_in2 + rate_in2) / (i + 1)
            if i == 0 or rate_in2 < min_in2: min_in2 = rate_in2
            if rate_in2 > max_in2: max_in2 = rate_in2
            
            if cmd_code == CMD_VERIFY_TEST:
                verify(rxdata2, len(rxdata2), i)
            else:
                print('Run {0:3d}: {1} {2}'.format(i, format_bytes(rate_out2), format_bytes(rate_in2)))

        print('\nSummary:')
        print('Write EP{0} avg: {1} (min: {2} max: {3})'.format(OE_CHOICE1, format_bytes(avg_out1), format_bytes(min_out1), format_bytes(max_out1)))
        print('Read  EP{0} avg: {1} (min: {2} max: {3})'.format(IE_CHOICE1, format_bytes(avg_in1), format_bytes(min_in1), format_bytes(max_in1)))
        print('Write EP{0} avg: {1} (min: {2} max: {3})'.format(OE_CHOICE2, format_bytes(avg_out2), format_bytes(min_out2), format_bytes(max_out2)))
        print('Read  EP{0} avg: {1} (min: {2} max: {3})'.format(IE_CHOICE2, format_bytes(avg_in2), format_bytes(min_in2), format_bytes(max_in2)))
    except Exception:
        traceback.print_exc()
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())
