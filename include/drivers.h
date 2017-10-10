#ifndef DRIVERS_H
#define DRIVERS_H

#define driver_interface(D) <drivers/D.h>


// should be defined in config.h
#define ENABLE_VGA_DRIVER
#define ENABLE_SERIAL_DRIVER

#ifdef ENABLE_VGA_DRIVER
#include driver_interface(vga)
#endif

#ifdef ENABLE_SERIAL_DRIVER
#include driver_interface(serial)
#endif


#endif
