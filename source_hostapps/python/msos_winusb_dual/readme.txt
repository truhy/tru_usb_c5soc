A Python script with PyUSB library (to use libusb) for testing USB device MSOS WinUSB demo

Instructions

1. Install libusb

For linux:
Download the latest release
https://github.com/libusb/libusb/releases

For Windows:
A prebuilt DLL is included with this script, simply copy libusb-1.0.dll to
path of this script

4. Plug your USB device in

5. Run this script, and you should see an output like this:

USB backend found: <WinDLL 'D:\Documents\Programming\FPGA\de10nano-c\tru_usb_client_python\msos2-test\libusb-1.0.dll', handle 7ffcb2b60000 at 0x1eb14e83810>
USB device found
VID PID     : 0x1209 0x0003
Manufacturer: TRU
Product     : TRU
Serial      : 123

Test settings (OUT = host to dev, IN = dev to host):
EP1 OUT transfer len: 64 bytes
EP1 IN  transfer len: 2097152 bytes
EP2 OUT transfer len: 64 bytes
EP2 IN  transfer len: 2097152 bytes
Number of runs      : 16

Test1:
Rate: 90 kbytes/s (EP1 OUT), 42683 (EP1 IN)
Rate: 112 kbytes/s (EP1 OUT), 42598 (EP1 IN)
Rate: 104 kbytes/s (EP1 OUT), 42233 (EP1 IN)
Rate: 62 kbytes/s (EP1 OUT), 40834 (EP1 IN)
Rate: 37 kbytes/s (EP1 OUT), 40095 (EP1 IN)
Rate: 27 kbytes/s (EP1 OUT), 42512 (EP1 IN)
Rate: 76 kbytes/s (EP1 OUT), 41328 (EP1 IN)
Rate: 39 kbytes/s (EP1 OUT), 40096 (EP1 IN)
Rate: 39 kbytes/s (EP1 OUT), 40054 (EP1 IN)
Rate: 35 kbytes/s (EP1 OUT), 40021 (EP1 IN)
Rate: 60 kbytes/s (EP1 OUT), 41048 (EP1 IN)
Rate: 30 kbytes/s (EP1 OUT), 39490 (EP1 IN)
Rate: 30 kbytes/s (EP1 OUT), 39388 (EP1 IN)
Rate: 37 kbytes/s (EP1 OUT), 41080 (EP1 IN)
Rate: 85 kbytes/s (EP1 OUT), 41952 (EP1 IN)
Rate: 22 kbytes/s (EP1 OUT), 40114 (EP1 IN)
Test2:
Rate: 50 kbytes/s (EP2 OUT), 40326 (EP2 IN)
Rate: 24 kbytes/s (EP2 OUT), 38058 (EP2 IN)
Rate: 22 kbytes/s (EP2 OUT), 38161 (EP2 IN)
Rate: 23 kbytes/s (EP2 OUT), 38841 (EP2 IN)
Rate: 36 kbytes/s (EP2 OUT), 39934 (EP2 IN)
Rate: 16 kbytes/s (EP2 OUT), 38434 (EP2 IN)
Rate: 16 kbytes/s (EP2 OUT), 38212 (EP2 IN)
Rate: 22 kbytes/s (EP2 OUT), 38708 (EP2 IN)
Rate: 26 kbytes/s (EP2 OUT), 40522 (EP2 IN)
Rate: 93 kbytes/s (EP2 OUT), 41217 (EP2 IN)
Rate: 34 kbytes/s (EP2 OUT), 39694 (EP2 IN)
Rate: 21 kbytes/s (EP2 OUT), 39018 (EP2 IN)
Rate: 52 kbytes/s (EP2 OUT), 40797 (EP2 IN)
Rate: 32 kbytes/s (EP2 OUT), 38245 (EP2 IN)
Rate: 34 kbytes/s (EP2 OUT), 38813 (EP2 IN)
Rate: 79 kbytes/s (EP2 OUT), 41316 (EP2 IN)
Summary:
EP1 AVG OUT: 56 kbytes/s (MIN: 22 MAX: 112)
EP1 AVG IN : 40970 kbytes/s (MIN: 39388 MAX: 42683)
EP2 AVG OUT: 36 kbytes/s (MIN: 16 MAX: 93)
EP2 AVG IN : 39394 kbytes/s (MIN: 38058 MAX: 41316)

Trouble-shooting

If your USB device doesn't enumerate the first time, Windows will create an
entry in the registry which stops it from enumerating again.
Using regedit you will need to delete this entry:
Computer\\HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\usbflags\\VIDPIDREV

where VIDPIDREV is the VID, PID and REV string of the device.

Useful references

https://github.com/pyusb/pyusb/blob/master/docs/tutorial.rst
https://pid.codes/howto/
