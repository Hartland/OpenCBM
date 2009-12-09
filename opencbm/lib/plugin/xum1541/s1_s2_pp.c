/*
 *  xum1541 plugin interface, derived from the xu1541 file of the same name
 *
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 *
 *  Copyright 2009 Nate Lawson <nate@root.org>
 *  Copyright 1999-2001 Michael Klein <michael(dot)klein(at)puffin(dot)lb(dot)shuttle(dot)de>
 *  Copyright 2001-2005,2007 Spiro Trikaliotis
 *
*/

/*! ************************************************************** 
** \file lib/plugin/xu1541/s1_s2_pp.c \n
** \author Till Harbaum, Spiro Trikaliotis \n
** \version $Id: s1_s2_pp.c,v 1.1 2009-12-09 05:39:00 natelawson Exp $ \n
** \n
** \brief Shared library / DLL for accessing the driver: Code for accessing fast protocols of xu1541
**
****************************************************************/

#ifdef WIN32
#include <windows.h>
#include <windowsx.h>

/*! Mark: We are in user-space (for debug.h) */
#define DBG_USERMODE

/*! Mark: We are building the DLL */
// #define DBG_DLL

/*! The name of the executable */
#define DBG_PROGNAME "OPENCBM-XUM1541.DLL"

/*! This file is "like" debug.c, that is, define some variables */
// #define DBG_IS_DEBUG_C

#include "debug.h"
#endif

#include <stdlib.h>

//! mark: We are building the DLL */
#define OPENCBM_PLUGIN
//#include "i_opencbm.h"
#include "archlib.h"

#include "xum1541.h"


/*-------------------------------------------------------------------*/
/*--------- OPENCBM ARCH FUNCTIONS ----------------------------------*/

/*! \brief Read data with serial1 protocol

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer which will hold the read bytes.

  \param size
    The size of the data buffer the read bytes will be written to.
*/
void CBMAPIDECL
cbmarch_s1_read_n(CBM_FILE HandleDevice, unsigned char *data, unsigned int size)
{
	xu1541_special_read(XUM1541_S1, data, size); 
}

/*! \brief Write data with serial1 protocol

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer to be written

  \param size
    The size of the data buffer to be written
*/
void CBMAPIDECL
cbmarch_s1_write_n(CBM_FILE HandleDevice, const unsigned char *data, unsigned int size)
{
	xu1541_special_write(XUM1541_S1, data, size); 
}

/*! \brief Read data with serial2 protocol

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer which will hold the read bytes.

  \param size
    The size of the data buffer the read bytes will be written to.
*/
void CBMAPIDECL
cbmarch_s2_read_n(CBM_FILE HandleDevice, unsigned char *data, unsigned int size)
{
	xu1541_special_read(XUM1541_S2, data, size); 
}

/*! \brief Write data with serial2 protocol

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer to be written

  \param size
    The size of the data buffer to be written
*/
void CBMAPIDECL
cbmarch_s2_write_n(CBM_FILE HandleDevice, const unsigned char *data, unsigned int size)
{
	xu1541_special_write(XUM1541_S2, data, size); 
}

/*! \brief Read data with parallel protocol (d64copy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer which will hold the read bytes.

  \param size
    The size of the data buffer the read bytes will be written to.
*/
void CBMAPIDECL
cbmarch_pp_dc_read_n(CBM_FILE HandleDevice, unsigned char *data, unsigned int size)
{
	xu1541_special_read(XUM1541_PP, data, size); 
}

/*! \brief Write data with parallel protocol (d64copy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer to be written

  \param size
    The size of the data buffer to be written
*/
void CBMAPIDECL
cbmarch_pp_dc_write_n(CBM_FILE HandleDevice, const unsigned char *data, unsigned int size)
{
	xu1541_special_write(XUM1541_PP, data, size); 
}

/*! \brief Read data with parallel protocol (cbmcopy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer which will hold the read bytes.

  \param size
    The size of the data buffer the read bytes will be written to.
*/
void CBMAPIDECL
cbmarch_pp_cc_read_n(CBM_FILE HandleDevice, unsigned char *data, unsigned int size)
{
	xu1541_special_read(XUM1541_P2, data, size); 
}

/*! \brief Write data with parallel protocol (cbmcopy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer to be written

  \param size
    The size of the data buffer to be written
*/
void CBMAPIDECL
cbmarch_pp_cc_write_n(CBM_FILE HandleDevice, const unsigned char *data, unsigned int size)
{
	xu1541_special_write(XUM1541_P2, data, size); 
}

/*! \brief Read data with burst nibbler protocol (cbmcopy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer which will hold the read bytes.

  \param size
    The size of the data buffer the read bytes will be written to.
*/
void CBMAPIDECL
cbmarch_nib_read_n(CBM_FILE HandleDevice, unsigned char *data, unsigned int size)
{
	xu1541_special_read(XUM1541_NIB, data, size); 
}

/*! \brief Write data with burst nibbler protocol (cbmcopy)

  \param HandleDevice
    A CBM_FILE which contains the file handle of the driver.

  \param data
    Pointer to the data buffer to be written

  \param size
    The size of the data buffer to be written
*/
void CBMAPIDECL
cbmarch_nib_write_n(CBM_FILE HandleDevice, const unsigned char *data, unsigned int size)
{
	xu1541_special_write(XUM1541_NIB, data, size); 
}