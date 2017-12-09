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

#pragma CODE_SECTION (DECODE_init, ".text:init")
#pragma CODE_SECTION (DECODE_exit, ".text:exit")

#include <std.h>
#include <alg.h>
#include <decode.h>

#include <time.h>
#ifdef PROFILER_ENABLE
#include "profiler.h"
#endif

/*
 *  ======== DECODE_apply ========
 *  Apply a DECODE function to the input array and place results in the
 *  output array.
 */
int DECODE_decode(DECODE_Handle handle, Int * in, Int *out, int inwords, 
                                                  IDECODE_OutArgs* outargs)
{
    /* activate instance object 
    ALG_activate((ALG_Handle)handle);*/
    int temp;
     
    
    temp = handle->fxns->decode(handle, in, out, inwords, outargs);    
       

    /* deactivate instance object 
    ALG_deactivate((ALG_Handle)handle);*/
    return temp;
}

//get decoder status
void DECODE_getStatus(DECODE_Handle handle, DECODE_Status *status)
{
    handle->fxns->getStatus(handle,status);
}

//reset decoder--> call this function before calling decoder for each streams
void DECODE_reset(DECODE_Handle handle)
{
 handle->fxns->reset(handle);
}

/*
 *  ======== DECODE_exit ========
 *  Module finalization
 */
Void DECODE_exit()
{
}

/*
 *  ======== DECODE_init ========
 *  Module initialization
 */
Void DECODE_init()
{
}

/*
 *  ======== DECODE_algMoved ========
 * 
 */

Void DECODE_algMoved(IALG_Handle handle, const IALG_MemRec memTab[],
                                 IALG_Handle p, const IALG_Params *params)
{
 
 handle->fxns->algMoved(handle, memTab, p, params);
   
}
