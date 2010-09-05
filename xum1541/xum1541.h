/*
 * xum1541 firmware defines
 * Copyright (c) 2009-2010 Nate Lawson <nate@root.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef _XUM1541_H
#define _XUM1541_H

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <LUFA/Version.h>
#include <LUFA/Drivers/USB/USB.h>

#include "xum1541_types.h"      // Version and protocol definitions

// All supported models. Add new ones below.
#define USBKEY                  0
#define BUMBLEB                 1
#define ZOOMFLOPPY              2
#define OLIMEX                  3

#if MODEL == USBKEY
#include "cpu-usbkey.h"
#include "board-usbkey.h"
#elif MODEL == BUMBLEB
#include "cpu-bumbleb.h"
#include "board-zoomfloppy.h"
#elif MODEL == OLIMEX
#include "cpu-zoomfloppy.h"
#include "board-zoomfloppy.h"
#elif MODEL == ZOOMFLOPPY
#include "cpu-zoomfloppy.h"
#include "board-zoomfloppy.h"
#endif

#ifdef DEBUG
#include <stdio.h>
#define DBG_ERROR   0
#define DBG_INFO    1
#define DBG_ALL     DBG_ERROR
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DBG_ALL
#endif
#define DEBUGF(level, format, args...)      \
    do {                                    \
        if (DEBUG_LEVEL >= level)           \
            printf_P(PSTR(format), ##args); \
    } while (0)
#else
#define DEBUGF(level, format, args...)
#endif

// USB parameters for descriptor configuration
#define XUM_DATA_DIR_NONE       0x0f
#if defined (__AVR_AT90USB1287__)
#define XUM_ENDPOINT_BULK_SIZE  64
#else
#define XUM_ENDPOINT_BULK_SIZE  32
#endif

// Status levels to notify the user (e.g. LEDS)
#define STATUS_INIT             0
#define STATUS_CONNECTING       1
#define STATUS_READY            2
#define STATUS_ACTIVE           3
#define STATUS_ERROR            4

extern volatile uint8_t eoi;
extern volatile bool doDeviceReset;

// USB IO functions and command handlers
int8_t usbHandleControl(uint8_t cmd, uint8_t *replyBuf);
int8_t usbHandleBulk(uint8_t *request, uint8_t *status);
bool TimerWorker(void);
void SetAbortState(void);
void USB_ResetConfig(void);
bool USB_ReadBlock(uint8_t *buf, uint8_t len);
bool USB_WriteBlock(uint8_t *buf, uint8_t len);
uint8_t AbortOnReset(void);
void usbInitIo(uint16_t len, uint8_t dir);
void usbIoDone(void);
int8_t usbSendByte(uint8_t data);
int8_t usbRecvByte(uint8_t *data);

// IEC functions
#define XUM_WRITE_TALK          (1 << 0)
#define XUM_WRITE_ATN           (1 << 1)
#define IEC_DELAY  (0.5)        // 500 ns for IEC lines to change state
void cbm_init(void);
void cbm_reset(void);
bool xu1541_wait(uint8_t line, uint8_t state);
uint8_t xu1541_poll(void);
void xu1541_setrelease(uint8_t set, uint8_t release);

/*
 * Special protocol handlers:
 * cbm - default CBM serial
 * s1 - serial
 * s2 - serial
 * p2 - parallel
 * pp - parallel
 * nib - nibbler parallel
 */
uint16_t cbm_raw_read(uint16_t len);
uint16_t cbm_raw_write(uint16_t len, uint8_t flags);
uint8_t s1_read_byte(void);
void s1_write_byte(uint8_t c);
uint8_t s2_read_byte(void);
void s2_write_byte(uint8_t c);
uint8_t p2_read_byte(void);
void p2_write_byte(uint8_t c);
void pp_read_2_bytes(uint8_t *c);
void pp_write_2_bytes(uint8_t *c);
uint8_t nib_parburst_read(void);
int8_t nib_read_handshaked(uint8_t *c, uint8_t toggle);
void nib_parburst_write(uint8_t data);
int8_t nib_write_handshaked(uint8_t data, uint8_t toggle);

#endif // _XUM1541_H