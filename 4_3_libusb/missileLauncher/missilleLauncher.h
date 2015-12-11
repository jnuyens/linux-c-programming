/*
 * missilleLauncher.h
 *
 *  Created on: Dec 10, 2015
 *      Author: student
 */

#ifndef MISSILLELAUNCHER_H_
#define MISSILLELAUNCHER_H_


#include <stdio.h>
#include <stdlib.h>
#include <usb.h>
#include <string.h>
#include <errno.h>


/* the missile launcher:
 "bus/device idVendor/idProduct
  002/006        2123/1010
- Unable to fetch manufacturer string
- Unable to fetch product string
 wTotalLength: 34
 bNumInterfaces: 1
 bConfigurationValue: 1
 iConfiguration: 0
 bmAttributes: 80h
 MaxPower: 250
 bInterfaceNumber: 0
 bAlternateSetting: 0
 bNumEndpoints: 1
 bInterfaceClass: 3
 bInterfaceSubClass: 0
 bInterfaceProtocol: 0
 iInterface: 0
 bEndpointAddress: 81h
 bmAttributes: 03h
 wMaxPacketSize: 8
 bInterval: 10
 bRefresh: 0
 bSynchAddress: 0
 *
 *
 */

int discoverUSB(void);
void setDevice(struct usb_device * dev);


#endif /* MISSILLELAUNCHER_H_ */
