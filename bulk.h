#pragma once
#ifndef BULK_H
#define BULK_H

#include "libusb\lusb0_usb.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stdint.h>

	bool Usb_Init();
	//void UsbDeInit(void);
	int Usb_Rd(void* buf, unsigned len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // BULK_H
