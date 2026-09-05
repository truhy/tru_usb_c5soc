# HPS USB 2.0 controller example demo for the Terasic DE10-Nano development board

## Overview

An example standalone program demonstrating the HPS USB 2.0 controller with various device classes.

## Build requirements

Minimum to build the C sources:
- GNU C/C++ cross toolchain for ARM processors supporting Cortex-A9
- newlib library.  This is usually included with the above toolchain

### Using my script to build

To build the C sources using the script under Windows, you will need a Windows port of GNU make with some shell facilities, a good solution is xPack's Build Tools.
Quick steps:
1. Edit the environment scripts in scripts-env with the correct tool paths.
2. Connect a USB cable from your computer to the UART-USB and another to USB Blaster II.
3. Start a serial terminal program with 115200 baud, 8 data bits, no parity and 1 stop bit
4. Apply power to DE10-Nano board
5. Run the provided prompt file, then you can build and run by typing in:
   make debug
   runelf debug
6. Connect a USB cable from DE10-Nano's USB 2.0 OTG socket and plug the other end to your computer, the USB device should enumerate on your computer

### Using "Eclipse IDE for Embedded C/C++ Developers" to build

To build the C sources using Eclipse, you can open with the included project file for Eclipse IDE, but you may need to setup other things first as described in my guide.
Quick steps:
1. Setup Eclipse for "Embedded C/C++ Developers"
2. Select from menu "File/Open Projects from File System..."
3. Browse "Directory..." to the source folder and click "Finish" button
4. Connect a USB cable from your computer to the UART-USB and another to USB Blaster II.
5. Apply power to DE10-Nano board
6. Start a serial terminal program with 115200 baud, 8 data bits, no parity and 1 stop bit
7. Select from menu "Run/Debug Configurations..."
8. Select the desired debug profile under "GDB OpenOCD Debugging"
9. Click "Debug" button
10. Connect a USB cable from DE10-Nano's USB 2.0 OTG socket and plug the other end to your computer, the USB device should enumerate on your computer

### Building the SD card image and U-Boot sources

To build these under Windows you will need to use WSL2 or Linux under a VM.  See the makefile or my guide for more information.

You can find the guide on my website:
[https://truhy.co.uk](https://truhy.co.uk)
