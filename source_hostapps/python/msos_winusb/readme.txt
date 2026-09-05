A Python script with PyUSB library (to use libusb) for testing USB device MSOS WinUSB demo

Instructions

1. Install libusb

For linux:
Download the latest release
https://github.com/libusb/libusb/releases

For Windows:
A prebuilt DLL is included with this script, simply copy libusb-1.0.dll to
path of this script

2. Install python

3. Install Python bindings for libusb by installing pyusb module, enter this into a command prompt:
py -m pip install pyusb

4. Plug your USB device in

5. Run this script, and you should see an output like this:

USB backend found: <WinDLL 'D:\Documents\Programming\FPGA\de10nano-c\tru_usb_client_python\msos1-test\libusb-1.0.dll', handle 7ffcbf690000 at 0x1825aaffc10>
USB device found
VID PID     : 0x1209 0x0003
Manufacturer: TRU
Product     : TRU
Serial      : 123

Test settings (OUT = host to dev, IN = dev to host):
EP1 OUT transfer len: 64 bytes
EP1 IN  transfer len: 2097152 bytes
Number of runs      : 16

Test:
Rate: 100 kbytes/s (EP1 OUT), 42757 (EP1 IN)
Rate: 107 kbytes/s (EP1 OUT), 42371 (EP1 IN)
Rate: 102 kbytes/s (EP1 OUT), 42320 (EP1 IN)
Rate: 88 kbytes/s (EP1 OUT), 41844 (EP1 IN)
Rate: 32 kbytes/s (EP1 OUT), 39767 (EP1 IN)
Rate: 36 kbytes/s (EP1 OUT), 40733 (EP1 IN)
Rate: 42 kbytes/s (EP1 OUT), 40606 (EP1 IN)
Rate: 44 kbytes/s (EP1 OUT), 41042 (EP1 IN)
Rate: 86 kbytes/s (EP1 OUT), 42280 (EP1 IN)
Rate: 59 kbytes/s (EP1 OUT), 41023 (EP1 IN)
Rate: 30 kbytes/s (EP1 OUT), 39402 (EP1 IN)
Rate: 30 kbytes/s (EP1 OUT), 39592 (EP1 IN)
Rate: 48 kbytes/s (EP1 OUT), 41674 (EP1 IN)
Rate: 80 kbytes/s (EP1 OUT), 42492 (EP1 IN)
Rate: 79 kbytes/s (EP1 OUT), 41989 (EP1 IN)
Rate: 47 kbytes/s (EP1 OUT), 40915 (EP1 IN)
Summary:
EP1 AVG OUT: 63 kbytes/s (MIN: 30 MAX: 107)
EP1 AVG IN : 41300 kbytes/s (MIN: 39402 MAX: 42757)

Trouble-shooting

If your USB device doesn't enumerate the first time, Windows will create an
entry in the registry which stops it from enumerating again.
Using regedit you will need to delete this entry:
Computer\\HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\usbflags\\VIDPIDREV

where VIDPIDREV is the VID, PID and REV string of the device.

Useful references

https://github.com/pyusb/pyusb/blob/master/docs/tutorial.rst
https://pid.codes/howto/
