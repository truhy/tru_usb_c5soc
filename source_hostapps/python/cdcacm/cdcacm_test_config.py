#!/usr/bin/python3

import traceback
import sys
import serial
import time

def main():
    try:
        dev_path = sys.argv[1]

        ser = serial.Serial(port=dev_path, baudrate=115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False, write_timeout=None, inter_byte_timeout=None, exclusive=None)
        #ser.set_buffer_size(rx_size = 64*1024, tx_size = 4096)

        print("Testing port", sys.argv[1])
        
        #ser.reset_input_buffer();
        #ser.reset_output_buffer();
        
        ser.dtr = 1
        ser.rts = 1
        print("DTR {} RTS {}".format(ser.dtr, ser.rts))
        print("CTS {} DSR {}".format(ser.cts, ser.dsr))
        ser.rts = 0
        ser.dtr = 0
        print("DTR {} RTS {}".format(ser.dtr, ser.rts))
        print("CTS {} DSR {}".format(ser.cts, ser.dsr))
    except Exception:
        traceback.print_exc()
        return 1
        
    return 0

if __name__ == "__main__":
    sys.exit(main())
    