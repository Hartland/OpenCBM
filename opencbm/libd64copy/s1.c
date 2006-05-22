/*
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 *  Copyright 1999 Michael Klein <michael(dot)klein(at)puffin(dot)lb(dot)shuttle(dot)de>
*/

#ifdef SAVE_RCSID
static char *rcsid =
    "@(#) $Id: s1.c,v 1.10 2006-05-22 08:34:19 wmsr Exp $";
#endif

#include "opencbm.h"
#include "d64copy_int.h"

#include <stdlib.h>

#include "arch.h"

static const unsigned char s1_drive_prog[] = {
#include "s1.inc"
};

static CBM_FILE fd_cbm;
static int two_sided;

static int s1_write_byte_nohs(CBM_FILE fd, unsigned char c)
{
    int b, i;
    for(i=7; ; i--) {
                                                                        SETSTATEDEBUG(debugLibD64BitCount=i);
        b=(c >> i) & 1;
                                                                        SETSTATEDEBUG((void)0);
        if(b) cbm_iec_set(fd, IEC_DATA); else cbm_iec_release(fd, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_release(fd, IEC_CLOCK);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT
        while(!cbm_iec_get(fd, IEC_CLOCK));
#else
        cbm_iec_wait(fd, IEC_CLOCK, 1);
#endif
                                                                        SETSTATEDEBUG((void)0);
        if(b) cbm_iec_release(fd, IEC_DATA); else cbm_iec_set(fd, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT
        while(cbm_iec_get(fd, IEC_CLOCK));
#else
        cbm_iec_wait(fd, IEC_CLOCK, 0);
#endif
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_release(fd, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_set(fd, IEC_CLOCK);
                                                                        SETSTATEDEBUG((void)0);

        if(i<=0) return 0;
                                                                        SETSTATEDEBUG((void)0);

#ifndef USE_CBM_IEC_WAIT
        while(!cbm_iec_get(fd, IEC_DATA));
#else
        cbm_iec_wait(fd, IEC_DATA, 1);
#endif
    }
                                                                        SETSTATEDEBUG((void)0);
}

static int s1_write_byte(CBM_FILE fd, unsigned char c)
{
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte_nohs(fd, c);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT
    while(!cbm_iec_get(fd, IEC_DATA));
#else
    cbm_iec_wait(fd, IEC_DATA, 1);
#endif
                                                                        SETSTATEDEBUG(debugLibD64BitCount=-1);
    return 0;
}

static int s1_read_byte(CBM_FILE fd, unsigned char *c)
{
    int b=0, i;
    *c = 0;
    for(i=7; i>=0; i--) {
                                                                        SETSTATEDEBUG(debugLibD64BitCount=i);
#ifndef USE_CBM_IEC_WAIT
        while(cbm_iec_get(fd, IEC_DATA));
#else        
        cbm_iec_wait(fd, IEC_DATA, 0);
#endif
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_release(fd, IEC_CLOCK);
                                                                        SETSTATEDEBUG((void)0);
        b = cbm_iec_get(fd, IEC_CLOCK);
                                                                        SETSTATEDEBUG((void)0);
        *c = (*c >> 1) | (b ? 0x80 : 0);
        cbm_iec_set(fd, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT
        while(b == cbm_iec_get(fd, IEC_CLOCK));
#else        
        cbm_iec_wait(fd, IEC_CLOCK, !b);
#endif
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_release(fd, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT
        while(!cbm_iec_get(fd, IEC_DATA));
#else        
        cbm_iec_wait(fd, IEC_DATA, 1);
#endif
                                                                        SETSTATEDEBUG((void)0);
        cbm_iec_set(fd, IEC_CLOCK);
    }
                                                                        SETSTATEDEBUG(debugLibD64BitCount=-1);
    return 0;
}

static int read_block(unsigned char tr, unsigned char se, unsigned char *block)
{
    int  i;
    unsigned char status;

                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, tr);
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, se);
                                                                        SETSTATEDEBUG((void)0);
#ifndef USE_CBM_IEC_WAIT    
    arch_usleep(20000);
#endif    
                                                                        SETSTATEDEBUG((void)0);
    s1_read_byte(fd_cbm, &status);
                                                                        SETSTATEDEBUG(debugLibD64ByteCount=0);
    for(i=0;i<256;i++)
    {
                                                                        SETSTATEDEBUG(debugLibD64ByteCount++);
        s1_read_byte(fd_cbm, &block[i]);
    }
                                                                        SETSTATEDEBUG(debugLibD64ByteCount=-1);
    cbm_iec_release(fd_cbm, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);

    return status;
}

static int write_block(unsigned char tr, unsigned char se, const unsigned char *blk, int size, int read_status)
{
    int  i;
    unsigned char status;

                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, tr);
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, se);
                                                                        SETSTATEDEBUG(debugLibD64ByteCount=0);
    for(i=0;i<size;i++)
    {
                                                                        SETSTATEDEBUG(debugLibD64ByteCount++);
        s1_write_byte(fd_cbm, blk[i]);
    }
                                                                        SETSTATEDEBUG(debugLibD64ByteCount=-1);
#ifndef USE_CBM_IEC_WAIT    
    if(size == BLOCKSIZE) {
                                                                        SETSTATEDEBUG((void)0);
        arch_usleep(20000);
    }
#endif    
                                                                        SETSTATEDEBUG((void)0);
    s1_read_byte(fd_cbm, &status);
                                                                        SETSTATEDEBUG((void)0);
    cbm_iec_release(fd_cbm, IEC_DATA);
                                                                        SETSTATEDEBUG((void)0);

    return status;
}

static int open_disk(CBM_FILE fd, d64copy_settings *settings,
                     const void *arg, int for_writing,
                     turbo_start start, d64copy_message_cb message_cb)
{
    unsigned char d = (unsigned char)(ULONG_PTR)arg;

    fd_cbm = fd;
    two_sided = settings->two_sided;

                                                                        SETSTATEDEBUG((void)0);
    cbm_upload(fd_cbm, d, 0x700, s1_drive_prog, sizeof(s1_drive_prog));
                                                                        SETSTATEDEBUG((void)0);
    start(fd, d);
                                                                        SETSTATEDEBUG((void)0);
    while(!cbm_iec_get(fd_cbm, IEC_DATA));
                                                                        SETSTATEDEBUG((void)0);
    return 0;
}

static void close_disk(void)
{
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, 0);
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte_nohs(fd_cbm, 0);
                                                                        SETSTATEDEBUG((void)0);
    arch_usleep(100);
                                                                        SETSTATEDEBUG(debugLibD64BitCount=-1);
}

static int send_track_map(unsigned char tr, const char *trackmap, unsigned char count)
{
    int i;
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, tr);
                                                                        SETSTATEDEBUG((void)0);
    s1_write_byte(fd_cbm, count);
                                                                        SETSTATEDEBUG((void)0);
    for(i = 0; i < d64copy_sector_count(two_sided, tr); i++)
    {
                                                                        SETSTATEDEBUG((void)0);
        s1_write_byte(fd_cbm, (unsigned char) !NEED_SECTOR(trackmap[i]));
    }
                                                                        SETSTATEDEBUG((void)0);
    return 0;
}

static int read_gcr_block(unsigned char *se, unsigned char *gcrbuf)
{
    int i;
    unsigned char s;

                                                                        SETSTATEDEBUG((void)0);
    s1_read_byte(fd_cbm, &s);
                                                                        SETSTATEDEBUG((void)0);
    *se = s;
    s1_read_byte(fd_cbm,  &s);
                                                                        SETSTATEDEBUG((void)0);

    if(s) {
        return s;
    }

                                                                        SETSTATEDEBUG(debugLibD64ByteCount=0);
    for(i = 0; i < GCRBUFSIZE; i++) {
                                                                        SETSTATEDEBUG(debugLibD64ByteCount++);
        s1_read_byte(fd_cbm, &gcrbuf[i]);
    }
                                                                        SETSTATEDEBUG(debugLibD64ByteCount=-1);
    return 0;
}

DECLARE_TRANSFER_FUNCS_EX(s1_transfer, 1, 1);
