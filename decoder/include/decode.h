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

#ifndef _DECODE_H_
#define _DECODE_H_

#include <alg.h>
#include <ialg.h>
#include <idecode.h>

/*
 *  ======== DECODE_Handle ========
 *  DECODE algorithm instance handle
 */
typedef struct IDECODE_Obj  *DECODE_Handle;

/*
 *  ======== DECODE_Params ========
 *  DECODE algorithm instance creation parameters
 */
typedef struct IDECODE_Params  DECODE_Params;

/*
 *  ======== DECODE_PARAMS ========
 *  Default instance parameters
 */
#define MP3_PARAMS IMP3_PARAMS


/*
 *  ======== DECODE_Status ========
 *  getStatus return parametrs
 */
typedef struct IDECODE_Status  DECODE_Status;


/*
 *  ======== DECODE_create ========
 *  Create an instance of a DECODE object.
 */
static inline DECODE_Handle DECODE_create(const IDECODE_Fxns *fxns, const DECODE_Params *prms)
{
    return ((DECODE_Handle)ALG_create((IALG_Fxns *)fxns, NULL, (IALG_Params *)prms));
}

/*
 *  ======== DECODE_delete ========
 *  Delete a DECODE instance object
 */
static inline Void DECODE_delete(DECODE_Handle handle)
{
    ALG_delete((ALG_Handle)handle);
}



#endif  /* _DECODE_H */

