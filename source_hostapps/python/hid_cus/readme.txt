A Python script with PyUSB library (to use libusb) for testing USB device custom HID demo

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

USB backend found: <WinDLL 'D:\Documents\Programming\FPGA\de10nano-verilog\f2h_usb\hid_dev_embed_20241224\Client App\tru_usb_hostapp_python\libusb-1.0.dll', handle 7ff9a12b0000 at 0x20473593390>
VID PID     : 0x1209 0x0001
Manufacturer: T
Product     : TRU
Serial      : 123
OUT EP1 MPS : 64
IN  EP1 MPS : 64

Test settings (OUT = host to dev, IN = dev to host):
OUT EP1 transfer len: 64 bytes
IN  EP1 transfer len: 64 bytes
Number of runs: 1

Transfer rate test:
Endpoints: Write = OUT EP1 Read = IN EP1
Run   0: 14.17 KB/s 8.88 KB/s

Summary:
Write avg: 14.17 KB/s (min: 14.17 KB/s, max: 14.17 KB/s)
Read  avg: 8.88 KB/s (min: 8.88 KB/s, max: 8.88 KB/s)

Trouble-shooting

Windows:
If your USB device doesn't enumerate the first time, Windows will create an
entry in the registry which stops it from enumerating again.
Using regedit you will need to delete this entry:
Computer\\HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\usbflags\\[VIDPIDREV]

Useful references

https://github.com/pyusb/pyusb/blob/master/docs/tutorial.rst
https://pid.codes/howto/
