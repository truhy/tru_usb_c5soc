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
PRODUCT_ID = 0x0001
IE_CHOICE1 = 1
OE_CHOICE1 = 1
# Note wr_len must not exceed the DEV_EXPECTED_RD_LEN (this is also the device max read len)
DEV_EXPECTED_RD_LEN = 0xffffffff
CMD_0 = 0x00
CMD_1 = 0x01
CMD_2 = 0x02

OE_CHOICE1_CODE = OE_CHOICE1 | LIBUSB_ENDPOINT_OUT
IE_CHOICE1_CODE = IE_CHOICE1 | LIBUSB_ENDPOINT_IN

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

def main():
    try:
        if len(sys.argv) != 4:
            raise ValueError("Not enough commandline parameters")
        
        wr_len = int(sys.argv[1])
        rd_len = int(sys.argv[2])
        num_runs = int(sys.argv[3])
        
        backend = usb.backend.libusb1.get_backend()  # Find and load USB backend library using search path
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
        oe = None
        ie = None
        cfg = dev.get_active_configuration()
        for intf in cfg:
            if intf.bAlternateSetting == 0:
                for ep in intf:
                    if ep.bEndpointAddress == OE_CHOICE1_CODE: oe = ep
                    if ep.bEndpointAddress == IE_CHOICE1_CODE: ie = ep
        
        # For HID the interrupt OUT EP is optional
        #if oe is None:
        #    raise ValueError('Failed to find OUT endpoint descriptor')
        #    sys.exit(1)
        
        if ie is None:
            raise ValueError('Failed to find IN endpoint descriptor')
            sys.exit(1)
        
        if oe is None:
            print('The optional interrupt OUT EP{0} does not exist.  Will use the control OUT EP0 instead'.format(OE_CHOICE1))
        else:
            print('OUT EP{0} MPS : {1}'.format(OE_CHOICE1, oe.wMaxPacketSize))
        print('IN  EP{0} MPS : {1}'.format(IE_CHOICE1, ie.wMaxPacketSize))

        # Display test settings
        print('\nTest settings (OUT = host to dev, IN = dev to host):')
        if oe is None:
            print('OUT EP0 transfer len: {0} bytes'.format(wr_len))
        else:
            print('OUT EP{0} transfer len: {1} bytes'.format(OE_CHOICE1, wr_len))
        print('IN  EP{0} transfer len: {1} bytes'.format(IE_CHOICE1, rd_len))
        print('Number of runs: {0}'.format(num_runs))

        # Build command message to send
        cmd = bytes([CMD_1]) + rd_len.to_bytes(4, "little") + bytearray(wr_len - 5)

        # Run test
        print('\nTransfer rate test:')
        if oe is None:
            print('Endpoints: Write = OUT EP0 Read = IN EP{0}'.format(IE_CHOICE1))
        else:
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
            if oe is None:
                dev.ctrl_transfer(0x21, 0x09, 0x0200, 0x0000, cmd);
            else:
                dev.write(OE_CHOICE1_CODE, cmd, TIMEOUT)
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_out1 = wr_len / elapsed
            else:
                rate_out1 = 0
            avg_out1 = (i * avg_out1 + rate_out1) / (i + 1)
            if i == 0 or rate_out1 < min_out1: min_out1 = rate_out1
            if rate_out1 > max_out1: max_out1 = rate_out1
            
            # Read from device
            time_begin = time.perf_counter()
            ret = dev.read(IE_CHOICE1_CODE, rd_len, TIMEOUT)
            time_end = time.perf_counter()
            elapsed = time_end - time_begin
            if elapsed > 0:
                rate_in1 = rd_len / elapsed
            else:
                rate_in1 = 0
            avg_in1 = (i * avg_in1 + rate_in1) / (i + 1)
            if i == 0 or rate_in1 < min_in1: min_in1 = rate_in1
            if rate_in1 > max_in1: max_in1 = rate_in1
            
            print('Run {0:3d}: {1} {2}'.format(i, format_bytes(rate_out1), format_bytes(rate_in1)))

        print('\nSummary:')
        print('Write avg: {0} (min: {1}, max: {2})'.format(format_bytes(avg_out1), format_bytes(min_out1), format_bytes(max_out1)))
        print('Read  avg: {0} (min: {1}, max: {2})'.format(format_bytes(avg_in1), format_bytes(min_in1), format_bytes(max_in1)))
    except Exception:
        traceback.print_exc()
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())
