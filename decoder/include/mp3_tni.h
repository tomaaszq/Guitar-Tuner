/*****************************************************************************
*----------------------------------------------------------------------------*
*                     TEXAS INSTRUMENTS INC                                  *
*                     Multimedia Codecs Group                                *
*                                                                            *
*----------------------------------------------------------------------------*
*                                                                            *
* (C) Copyright 2009  Texas Instruments Inc.  All rights reserved.           *
*                                                                            *
* Exclusive property of the Multimedia Codecs Group, Texas Instruments Inc.  *
* Any handling, use, disclosure, reproduction, duplication, transmission     *
* or storage of any part of this work by any means is subject to restrictions*
* and prior written permission set forth.                                    *
*                                                                            *
* This copyright notice, restricted rights legend, or other proprietary      *
* markings must be reproduced without modification in any authorized copies  *
* of any part of this work. Removal or modification of any part of this      *
* notice is prohibited.                                                      *
*                                                                            *
*****************************************************************************/
/*
 *  ======== MP3_tni.h ========
 *  Interface header for the MP3_TNI module.
 */
#ifndef _MP3_TNI_H_
#define _MP3_TNI_H_

#include <ialg.h>
#include <idecode.h>

/*
 *  ======== MP3_TNI_exit ========
 *  Required module finalization function.
 */
extern Void MP3_TNI_exit(Void);

/*
 *  ======== MP3_TNI_init ========
 *  Required module initialization function.
 */
extern Void MP3_TNI_init(Void);

/*
 *  ======== MP3_TNI_IALG ========
 *  TI's implementation of MP3's IALG interface
 */

extern IALG_Fxns MP3_TNI_IALG;

/*
 *  ======== MP3_TNI_IMP3 ========
 *  TI's implementation of MP3's IMP3 interface
 */
extern const IDECODE_Fxns MP3_TNI_IMP3;

#endif /* _MP3_TNI_H_ */
