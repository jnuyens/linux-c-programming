/*
 * missileLauncher.c
 *
 *  Created on: Dec 10, 2015
 *      Author: student
 */
#include "missilleLauncher.h"

static struct usb_device s_missileLauncher = { };

void setDevice(struct usb_device * dev) {
	s_missileLauncher = *dev;
}

int testSendData(void) {
	usb_dev_handle *dev_handle; //a device handle
	struct usb_device * deviceOfUsb = &s_missileLauncher; //a libusb session
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n------------------------------------\n");
	dev_handle = usb_open(deviceOfUsb);
	if (dev_handle == NULL)
		printf("Cannot open device \n");
	else
		printf("Device Opened \n");

	unsigned char data[] = {0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00 }; //data to write

	int actual; //used to find out how many bytes were written
	char name[200];
	size_t size = 200;
	if (usb_get_driver_np(dev_handle, 0, name, size) == 0) { //find out if kernel driver is attached
		printf("Kernel Driver Active \n");
		if (usb_detach_kernel_driver_np(dev_handle, 0) == 0) //detach it
			printf("Kernel Driver Detached! \n");
	}

	int r = usb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
	if (r < 0) {
		printf("Cannot Claim Interface \n");
		printf("%s\n", strerror(errno));
		usb_close(dev_handle);
		return 1;
	}
	printf("Claimed Interface \n");

	//printf("Data-> %s \n", data); //just to see the data we want to write : abcd
	printf("Writing Data... \n");
	//0x21,0x09,0,0,[0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00]);
	r = 1;
	for (int i = 0; i < 100 && r > 0; i++) {
		r = usb_control_msg(dev_handle, 0x21, 0x09, 0, 0, data, 8, 5000); //my device's out endpoint was 2, found with trial- the device had 2 endpoints: 2 and 129
		if (r > 0) //we wrote the 4 bytes successfully
			printf("Writing Successful! \n");
		else
			printf("Write Error \n");
	}
	r = usb_release_interface(dev_handle, 0); //release the claimed interface
	if (r != 0) {
		printf("Cannot Release Interface \n");
		usb_close(dev_handle);
		return 1;
	}
	printf("Released Interface \n");

	usb_close(dev_handle); //close the device we opened

	return 0;
}
int main(void) {
	discoverUSB();
	testSendData();
	return 0;
}
