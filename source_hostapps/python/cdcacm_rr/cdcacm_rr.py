#!/usr/bin/python3

import traceback
import sys
import serial
import time

CMD_RATE_TEST = 0x01
CMD_VERIFY_TEST = 0x02

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

def verify(rxdata, act_len):
    mismatch_count = 0
    test_count = 0

    for j in range(act_len):
        if rxdata[j] != test_count:
            mismatch_count = mismatch_count + 1
        test_count = (test_count + 1) % 256
    
    if mismatch_count > 0:
        print("Verify {}/{} {} errors (failed)".format(act_len - mismatch_count, act_len, mismatch_count))
    else:
        print("Verify {}/{} {} errors (passed)".format(act_len, act_len, mismatch_count))

def main():
    try:
        if len(sys.argv) != 6:
            raise ValueError("Not enough commandline parameters")
        
        dev_path = sys.argv[1]
        cmd_str = sys.argv[2]
        wr_len = int(sys.argv[3])
        rd_len = int(sys.argv[4])
        num_runs = int(sys.argv[5])
        
        if cmd_str == "rate":
            cmd_code = CMD_RATE_TEST
        elif cmd_str == "verify":
            cmd_code = CMD_VERIFY_TEST
        else:
            raise ValueError("Commandline parameter 2 is an invalid command")
        
        ser = serial.Serial(port=dev_path, baudrate=115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False, write_timeout=None, inter_byte_timeout=None, exclusive=None)
        #ser.set_buffer_size(rx_size = 64*1024, tx_size = 4096)
        
        cmd_block = bytes([cmd_code]) + wr_len.to_bytes(4, "little") + rd_len.to_bytes(4, "little")
        txdata = cmd_block + bytearray(wr_len - len(cmd_block))  # Command block + zero fill

        print("Serial port:", sys.argv[1])
        
        #ser.reset_input_buffer();
        #ser.reset_output_buffer();
        
        print("")
        print("Testing control lines")
        print("Set: DTR=0, RTS=0")
        ser.dtr = 0
        ser.rts = 0
        print("Get: DTR={} RTS={} DSR={} CTS={}".format(ser.dtr, ser.rts, ser.dsr, ser.cts))
        print("Set: DTR=1, RTS=1")
        ser.dtr = 1
        ser.rts = 1
        print("Get: DTR={} RTS={} DSR={} CTS={}".format(ser.dtr, ser.rts, ser.dsr, ser.cts))
        
        print("")
        print("Transfer test")
        for i in range(num_runs):
            tx_tstart = time.perf_counter_ns()
            #tx_tstart = time.process_time_ns()
            tx_act_len = ser.write(txdata)
            #ser.flush();
            tx_tstop = time.perf_counter_ns()
            #tx_tstop = time.process_time_ns()
            
            rx_tstart = time.perf_counter_ns()
            #rx_tstart = time.process_time_ns()
            rxdata = ser.read(rd_len)
            rx_tstop = time.perf_counter_ns()
            #rx_tstop = time.process_time_ns()
            rx_act_len = len(rxdata)
            
            if cmd_code == CMD_VERIFY_TEST:
                verify(rxdata, rx_act_len)
            else:
                print("Tx len: {} throughput: {}".format(tx_act_len, format_bytes(tx_act_len / (tx_tstop - tx_tstart)*1000000000)))
                print("Rx len: {} throughput: {}".format(rx_act_len, format_bytes(rx_act_len / (rx_tstop - rx_tstart)*1000000000)))
                #print("Rx bytes: {}".format(rxdata.hex()))
    except Exception:
        traceback.print_exc()
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())
    