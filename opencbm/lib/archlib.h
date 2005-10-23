#ifndef ARCHLIB_H
#define ARCHLIB_H

#include "opencbm.h"

extern const char * cbmarch_get_driver_name(int PortNumber);
extern int  cbmarch_driver_open(CBM_FILE *HandleDevice, int PortNumber);
extern void cbmarch_driver_close(CBM_FILE HandleDevice);
extern int  cbmarch_raw_write(CBM_FILE HandleDevice, const void *Buffer, size_t Count);
extern int  cbmarch_raw_read(CBM_FILE HandleDevice, void *Buffer, size_t Count);
extern int  cbmarch_listen(CBM_FILE HandleDevice, __u_char DeviceAddress, __u_char SecondaryAddress);
extern int  cbmarch_talk(CBM_FILE HandleDevice, __u_char DeviceAddress, __u_char SecondaryAddress);
extern int  cbmarch_open(CBM_FILE HandleDevice, __u_char DeviceAddress, __u_char SecondaryAddress);
extern int  cbmarch_unlisten(CBM_FILE HandleDevice);
extern int  cbmarch_untalk(CBM_FILE HandleDevice);
extern int  cbmarch_close(CBM_FILE HandleDevice, __u_char DeviceAddress, __u_char SecondaryAddress);
extern int  cbmarch_unlisten(CBM_FILE HandleDevice);
extern int  cbmarch_untalk(CBM_FILE HandleDevice);
extern int  cbmarch_get_eoi(CBM_FILE HandleDevice);
extern int  cbmarch_clear_eoi(CBM_FILE HandleDevice);
extern int  cbmarch_reset(CBM_FILE HandleDevice);
extern __u_char cbmarch_pp_read(CBM_FILE HandleDevice);
extern void cbmarch_pp_write(CBM_FILE HandleDevice, __u_char Byte);
extern int  cbmarch_iec_poll(CBM_FILE HandleDevice);
extern void cbmarch_iec_set(CBM_FILE HandleDevice, int Line);
extern void cbmarch_iec_release(CBM_FILE HandleDevice, int Line);
extern void cbmarch_iec_setrelease(CBM_FILE HandleDevice, int Mask, int Line);
extern int  cbmarch_iec_wait(CBM_FILE HandleDevice, int Line, int State);

extern __u_char cbmarch_mnib_par_read(CBM_FILE HandleDevice);
extern void cbmarch_mnib_par_write(CBM_FILE HandleDevice, __u_char Value);
extern int  cbmarch_mnib_read_track(CBM_FILE HandleDevice, __u_char *Buffer, unsigned int Length, __u_char Mode);
extern int  cbmarch_mnib_write_track(CBM_FILE HandleDevice, __u_char *Buffer, unsigned int Length, __u_char Mode);

#endif // #ifndef ARCHLIB_H