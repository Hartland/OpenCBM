/*
 * Name: p2.c
 * Project: xu1541
 * Author: Till Harbaum
 * Tabsize: 4
 * Copyright: (c) 2007 by Till Harbaum <till@harbaum.org>
 * License: GPL
 * This Revision: $Id: p2.c,v 1.2 2009-12-11 20:28:17 natelawson Exp $
 *
 * $Log $
 * Revision 1.3  2008/10/09 18:55:45  strik
 * Removed spaces and tabs before LF.
 *
 * Revision 1.2  2007/03/15 17:40:51  harbaum
 * Plenty of changes incl. first async support
 *
 * Revision 1.1  2007/02/18 19:47:32  harbaum
 * Bootloader and p2 protocol
 */

/* This file contains the "parallel2" helper functions for opencbm */
/* changes in the protocol must be reflected here. The parallel2 protocol */
/* is the parallel protocol used by libcbmcopy */

#include "xum1541.h"

void
p2_write_byte(uint8_t c)
{

    xu1541_pp_write(c);

    iec_release(IO_CLK);
    while (iec_get(IO_DATA));

    iec_set(IO_CLK);
    while (!iec_get(IO_DATA));
}

uint8_t
p2_read_byte(void)
{
    uint8_t c;

    iec_release(IO_CLK);
    while (iec_get(IO_DATA));

    c = xu1541_pp_read();

    iec_set(IO_CLK);
    while (!iec_get(IO_DATA));

    return c;
}