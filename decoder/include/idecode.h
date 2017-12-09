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

#ifndef _IDECODE_H_
#define _IDECODE_H_

#include <ialg.h>

/*MP3 decoder specific errors */
#define     MP3_TNI_NO_ERROR            0 // no error
#define     MP3_TNI_SYNC_NOT_FOUND      1 // sync not found
#define     MP3_TNI_ERR_NOT_LAYER3      2 // Bitstream not layer3
#define     MP3_TNI_ERR_FREE_FORMAT     3 // Free format stream error
#define     MP3_TNI_ERR_MAIN_NEGATIVE   4 // Main Data being pointer negative
#define     MP3_TNI_WARN_BAD_PCM_DATA   5
#define     MP3_TNI_WARN_CHANGE_CH      6
#define     MP3_TNI_WARN_CHANGE_SF      7

typedef enum{
    IAUDIO_BLOCK = 0,
    IAUDIO_INTERLEAVED
}IAUDIO_PcmFormat;

/*
 *  ======== IDECODE_Obj ========
 *  This structure must be the first field of all DECODE instance objects.
 */
typedef struct IDECODE_Obj {
    struct IDECODE_Fxns *fxns;
} IDECODE_Obj;

/*
 *  ======== IDECODE_Handle ========
 *  This handle is used to reference all DECODE instance objects.
 */
typedef struct IDECODE_Obj  *IDECODE_Handle;


/*
 *  ======== IDECODE_Params ========
 *  This structure defines the creation parameters for all DECODE instance
 *  objects.
 */
typedef struct  IDECODE_Params {
    Int size;       /* Size of this structure */
    Int pcmFormat;  /* BLOCK or INTERLEAVED */
} IDECODE_Params;

extern const IDECODE_Params IMP3_PARAMS;    /* default params */

/*
 *  ======== IDECODE_Status ========
 *  This structure defines the parameters that can be changed at runtime
 *  (read/write), and the instance status parameters (read-only).
 */
typedef struct IDECODE_Status{
    Int     size;       /* Size of this structure */
    Bool    isValid;    /* are next fields valid?  */
    Uns     numSamples; /* Frame length in number of samples  */
    LgInt   bitRate;    /* Bitstream bit rate in bits per second  */
    LgInt   sampleRate; /* Bitstream sample rate in Hz  */
    Int     numChannels;    /* 1 or 2  */
    Int     outputPCMWidth; /* 16 always */
    Int     pcmFormat;      /* BLOCK or INTERLEAVED */

}IDECODE_Status;

/*
 *  ======== IDECODE_OutArgs ========
 *  This structure defines the arguments that are updated by the decoder.
 */

typedef struct IDECODE_OutArgs{
    Int     size;       /* Size of this structure */
    LgInt   wordsConsumed;  /* Words Consumed */
    Uns     numSamples;    /* Number of output PCM samples */
    LgInt   sampleRate; /* Bitstream sample rate in Hz  */
    Int     numChannels;    /* 1 or 2  */
    Int     outputPCMWidth; /* 16 always */
    Int     pcmFormat;      /* BLOCK or INTERLEAVED */

}IDECODE_OutArgs;


/*
 *  ======== IDECODE_Cmd ========
 *  This structure defines the control commands for the DECODE module.
 */
typedef  IALG_Cmd IDECODE_Cmd;

/*
 *  ======== IDECODE_Fxns ========
 *  This structure defines all of the operations on DECODE objects.
 */
typedef struct IDECODE_Fxns{
    IALG_Fxns ialg; /* IDECODE extends IALG */
    Int     (*decode)(IDECODE_Handle handle, Int *in, Int *out, 
                            Int numInputWords,IDECODE_OutArgs* outArgs);
    Void    (*getStatus)(IDECODE_Handle handle, IDECODE_Status *status);
    Void    (*reset)(IDECODE_Handle handle);

}IDECODE_Fxns;


#endif  /* _IDECODE_H */



