#include "bulk.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MY_VID 0x1209
#define DEV_RX

#if defined DEV_RX
#define MY_PID 0x8887
#elif defined DEV_TX
#define MY_PID 0x8888
#else
#error RX or TX???
#endif

// Device configuration and interface id.
#define MY_CONFIG  1
#define MY_INTF    0

// Device endpoint(s)
#define EP_IN   0x82
#define EP_OUT  0x01


usb_dev_handle* open_dev(void);

static int transfer_bulk_async(usb_dev_handle* dev,
    int ep,
    char* bytes,
    int size,
    int timeout);


usb_dev_handle* dev = NULL; /* the device handle */


bool Usb_Init()
{
    struct usb_bus* bus;
    struct usb_device* dev_test;
    char str[128];

    usb_init();         // initialize the library
    usb_find_busses();  // find all busses
    usb_find_devices(); // find all connected devices

    for (bus = usb_get_busses(); bus; bus = bus->next)
    {
        for (dev_test = bus->devices; dev_test; dev_test = dev_test->next)
        {
            if (dev_test->descriptor.idVendor == MY_VID &&
                dev_test->descriptor.idProduct == MY_PID)
            {
                dev = usb_open(dev_test);

                if (dev)
                {
                    if (usb_set_configuration(dev, MY_CONFIG) < 0) goto next_dev;

                    usb_get_string_simple(dev, 4, str, sizeof(str));   // CFG STRING DESCR

                    if (strcmp(str, "CFG_Normal")) goto next_dev;

                    if (usb_claim_interface(dev, 0) < 0) goto next_dev;

                    char gUSBSerial[64];
                    usb_get_string_simple(dev, dev_test->descriptor.iSerialNumber, gUSBSerial, sizeof(gUSBSerial));   // SERIAL STRING

                    return true;

                next_dev:
                    usb_close(dev);
                    continue;
                }
            }
        }
    }

    return false;
}


unsigned usb_out_incr;
extern volatile int gLED;



int Usb_Rd(void* buf, unsigned len)
{
    return usb_bulk_read(dev, EP_IN, (char*)buf, len, 1000);
}