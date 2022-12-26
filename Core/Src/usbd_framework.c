#include "usbd_framework.h"

void usbd_initialize(void)
{
    initialize_usb_pins();
    initialize_core();
}