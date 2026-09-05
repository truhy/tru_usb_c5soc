#ifndef MY_USB_CMD_H
#define MY_USB_CMD_H

#include "cmd_line_and_vars.h"
#include "my_usb_enum.h"
#include "my_usb_dev.h"
#include "my_buf.h"
#include "my_file.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// ReportID padding, note the extra padding doesn't come from the device, it is added by this library or HID driver
#define REPORTID_PADDING 1

static const char m_error_usb_read[] = "USB read failed!";
static const char m_error_usb_write[] = "USB write failed!";
static const char m_error_usb_data_corrupt[] = "USB data corruption detected!";

void disp_msg_as_ascii(char *msg, int len);
void disp_msg_as_hex(unsigned char *msg, int len);
void process_report(cl_my_params *my_params, cl_usb_dev *usb_dev);

#endif
