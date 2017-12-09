/********************************************************************
* Copyright (C) 2003-2008 Texas Instruments Incorporated.
* All Rights Reserved
*********************************************************************
* file: cslr_dma.h
*
* Brief: This file contains the Register Description for dma
*
*********************************************************************/
#ifndef _CSLR_DMA_H_
#define _CSLR_DMA_H_

#include <cslr.h>

#include <tistdtypes.h>
#include <csl_general.h>


/* Minimum unit = 2 bytes */

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint16 DMACH0SSAL;
    volatile Uint16 DMACH0SSAU;
    volatile Uint16 DMACH0DSAL;
    volatile Uint16 DMACH0DSAU;
    volatile Uint16 DMACH0TCR1;
    volatile Uint16 DMACH0TCR2;
    volatile Uint16 RSVD0[26];
    volatile Uint16 DMACH1SSAL;
    volatile Uint16 DMACH1SSAU;
    volatile Uint16 DMACH1DSAL;
    volatile Uint16 DMACH1DSAU;
    volatile Uint16 DMACH1TCR1;
    volatile Uint16 DMACH1TCR2;
    volatile Uint16 RSVD1[26];
    volatile Uint16 DMACH2SSAL;
    volatile Uint16 DMACH2SSAU;
    volatile Uint16 DMACH2DSAL;
    volatile Uint16 DMACH2DSAU;
    volatile Uint16 DMACH2TCR1;
    volatile Uint16 DMACH2TCR2;
    volatile Uint16 RSVD2[26];
    volatile Uint16 DMACH3SSAL;
    volatile Uint16 DMACH3SSAU;
    volatile Uint16 DMACH3DSAL;
    volatile Uint16 DMACH3DSAU;
    volatile Uint16 DMACH3TCR1;
    volatile Uint16 DMACH3TCR2;
} CSL_DmaRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* DMACH0SSAL */

#define CSL_DMA_DMACH0SSAL_SSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH0SSAL_SSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH0SSAL_SSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0SSAL_RESETVAL      (0x0000u)

/* DMACH0SSAU */

#define CSL_DMA_DMACH0SSAU_SSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH0SSAU_SSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH0SSAU_SSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0SSAU_RESETVAL      (0x0000u)

/* DMACH0DSAL */

#define CSL_DMA_DMACH0DSAL_DSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH0DSAL_DSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH0DSAL_DSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0DSAL_RESETVAL      (0x0000u)

/* DMACH0DSAU */

#define CSL_DMA_DMACH0DSAU_DSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH0DSAU_DSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH0DSAU_DSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0DSAU_RESETVAL      (0x0000u)

/* DMACH0TCR1 */

#define CSL_DMA_DMACH0TCR1_LENGTH_MASK   (0xFFFFu)
#define CSL_DMA_DMACH0TCR1_LENGTH_SHIFT  (0x0000u)
#define CSL_DMA_DMACH0TCR1_LENGTH_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0TCR1_RESETVAL      (0x0000u)

/* DMACH0TCR2 */

#define CSL_DMA_DMACH0TCR2_EN_MASK       (0x8000u)
#define CSL_DMA_DMACH0TCR2_EN_SHIFT      (0x000Fu)
#define CSL_DMA_DMACH0TCR2_EN_RESETVAL   (0x0000u)
/*----EN Tokens----*/
#define CSL_DMA_DMACH0TCR2_EN_ENABLE     (0x0000u)
#define CSL_DMA_DMACH0TCR2_EN_DISABLE    (0x0001u)

#define CSL_DMA_DMACH0TCR2_STATUS_MASK   (0x4000u)
#define CSL_DMA_DMACH0TCR2_STATUS_SHIFT  (0x000Eu)
#define CSL_DMA_DMACH0TCR2_STATUS_RESETVAL (0x0000u)
/*----STATUS Tokens----*/
#define CSL_DMA_DMACH0TCR2_STATUS_DONE   (0x0000u)
#define CSL_DMA_DMACH0TCR2_STATUS_ACTIVE (0x0001u)

#define CSL_DMA_DMACH0TCR2_INTEN_MASK    (0x2000u)
#define CSL_DMA_DMACH0TCR2_INTEN_SHIFT   (0x000Du)
#define CSL_DMA_DMACH0TCR2_INTEN_RESETVAL (0x0000u)
/*----INTEN Tokens----*/
#define CSL_DMA_DMACH0TCR2_INTEN_DISABLE (0x0000u)
#define CSL_DMA_DMACH0TCR2_INTEN_ENABLE  (0x0001u)

#define CSL_DMA_DMACH0TCR2_AUTORLD_MASK  (0x1000u)
#define CSL_DMA_DMACH0TCR2_AUTORLD_SHIFT (0x000Cu)
#define CSL_DMA_DMACH0TCR2_AUTORLD_RESETVAL (0x0000u)
/*----AUTORLD Tokens----*/
#define CSL_DMA_DMACH0TCR2_AUTORLD_DISABLE (0x0000u)
#define CSL_DMA_DMACH0TCR2_AUTORLD_ENABLE (0x0001u)


#define CSL_DMA_DMACH0TCR2_DSTAMODE_MASK (0x0300u)
#define CSL_DMA_DMACH0TCR2_DSTAMODE_SHIFT (0x0008u)
#define CSL_DMA_DMACH0TCR2_DSTAMODE_RESETVAL (0x0000u)
/*----DSTAMODE Tokens----*/
#define CSL_DMA_DMACH0TCR2_DSTAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH0TCR2_DSTAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH0TCR2_DSTAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH0TCR2_DSTAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH0TCR2_SRCAMODE_MASK (0x00C0u)
#define CSL_DMA_DMACH0TCR2_SRCAMODE_SHIFT (0x0006u)
#define CSL_DMA_DMACH0TCR2_SRCAMODE_RESETVAL (0x0000u)
/*----SRCAMODE Tokens----*/
#define CSL_DMA_DMACH0TCR2_SRCAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH0TCR2_SRCAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH0TCR2_SRCAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH0TCR2_SRCAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH0TCR2_BURSTMODE_MASK (0x0038u)
#define CSL_DMA_DMACH0TCR2_BURSTMODE_SHIFT (0x0003u)
#define CSL_DMA_DMACH0TCR2_BURSTMODE_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0TCR2_SYNCMODE_MASK (0x0004u)
#define CSL_DMA_DMACH0TCR2_SYNCMODE_SHIFT (0x0002u)
#define CSL_DMA_DMACH0TCR2_SYNCMODE_RESETVAL (0x0000u)
/*----SYNCMODE Tokens----*/
#define CSL_DMA_DMACH0TCR2_SYNCMODE_NOSYNC (0x0000u)
#define CSL_DMA_DMACH0TCR2_SYNCMODE_SYNC (0x0001u)

#if ((defined(CHIP_5515)) || (defined(CHIP_5514)))

#define CSL_DMA_DMACH0TCR2_LTSTATUS_MASK (0x0002u)
#define CSL_DMA_DMACH0TCR2_LTSTATUS_SHIFT (0x0001u)
#define CSL_DMA_DMACH0TCR2_LTSTATUS_RESETVAL (0x0000u)

#define CSL_DMA_DMACH0TCR2_EPPMODE_MASK  (0x0001u)
#define CSL_DMA_DMACH0TCR2_EPPMODE_SHIFT (0x0000u)
#define CSL_DMA_DMACH0TCR2_EPPMODE_RESETVAL (0x0000u)

#endif

#define CSL_DMA_DMACH0TCR2_RESETVAL      (0x0000u)

/* DMACH1SSAL */

#define CSL_DMA_DMACH1SSAL_SSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH1SSAL_SSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH1SSAL_SSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1SSAL_RESETVAL      (0x0000u)

/* DMACH1SSAU */

#define CSL_DMA_DMACH1SSAU_SSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH1SSAU_SSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH1SSAU_SSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1SSAU_RESETVAL      (0x0000u)

/* DMACH1DSAL */

#define CSL_DMA_DMACH1DSAL_DSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH1DSAL_DSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH1DSAL_DSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1DSAL_RESETVAL      (0x0000u)

/* DMACH1DSAU */

#define CSL_DMA_DMACH1DSAU_DSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH1DSAU_DSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH1DSAU_DSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1DSAU_RESETVAL      (0x0000u)

/* DMACH1TCR1 */

#define CSL_DMA_DMACH1TCR1_LENGTH_MASK   (0xFFFFu)
#define CSL_DMA_DMACH1TCR1_LENGTH_SHIFT  (0x0000u)
#define CSL_DMA_DMACH1TCR1_LENGTH_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1TCR1_RESETVAL      (0x0000u)

/* DMACH1TCR2 */

#define CSL_DMA_DMACH1TCR2_EN_MASK       (0x8000u)
#define CSL_DMA_DMACH1TCR2_EN_SHIFT      (0x000Fu)
#define CSL_DMA_DMACH1TCR2_EN_RESETVAL   (0x0000u)
/*----EN Tokens----*/
#define CSL_DMA_DMACH1TCR2_EN_ENABLE     (0x0000u)
#define CSL_DMA_DMACH1TCR2_EN_DISABLE    (0x0001u)

#define CSL_DMA_DMACH1TCR2_STATUS_MASK   (0x4000u)
#define CSL_DMA_DMACH1TCR2_STATUS_SHIFT  (0x000Eu)
#define CSL_DMA_DMACH1TCR2_STATUS_RESETVAL (0x0000u)
/*----STATUS Tokens----*/
#define CSL_DMA_DMACH1TCR2_STATUS_DONE   (0x0000u)
#define CSL_DMA_DMACH1TCR2_STATUS_ACTIVE (0x0001u)

#define CSL_DMA_DMACH1TCR2_INTEN_MASK    (0x2000u)
#define CSL_DMA_DMACH1TCR2_INTEN_SHIFT   (0x000Du)
#define CSL_DMA_DMACH1TCR2_INTEN_RESETVAL (0x0000u)
/*----INTEN Tokens----*/
#define CSL_DMA_DMACH1TCR2_INTEN_DISABLE (0x0000u)
#define CSL_DMA_DMACH1TCR2_INTEN_ENABLE  (0x0001u)

#define CSL_DMA_DMACH1TCR2_AUTORLD_MASK  (0x1000u)
#define CSL_DMA_DMACH1TCR2_AUTORLD_SHIFT (0x000Cu)
#define CSL_DMA_DMACH1TCR2_AUTORLD_RESETVAL (0x0000u)
/*----AUTORLD Tokens----*/
#define CSL_DMA_DMACH1TCR2_AUTORLD_DISABLE (0x0000u)
#define CSL_DMA_DMACH1TCR2_AUTORLD_ENABLE (0x0001u)


#define CSL_DMA_DMACH1TCR2_DSTAMODE_MASK (0x0300u)
#define CSL_DMA_DMACH1TCR2_DSTAMODE_SHIFT (0x0008u)
#define CSL_DMA_DMACH1TCR2_DSTAMODE_RESETVAL (0x0000u)
/*----DSTAMODE Tokens----*/
#define CSL_DMA_DMACH1TCR2_DSTAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH1TCR2_DSTAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH1TCR2_DSTAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH1TCR2_DSTAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH1TCR2_SRCAMODE_MASK (0x00C0u)
#define CSL_DMA_DMACH1TCR2_SRCAMODE_SHIFT (0x0006u)
#define CSL_DMA_DMACH1TCR2_SRCAMODE_RESETVAL (0x0000u)
/*----SRCAMODE Tokens----*/
#define CSL_DMA_DMACH1TCR2_SRCAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH1TCR2_SRCAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH1TCR2_SRCAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH1TCR2_SRCAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH1TCR2_BURSTMODE_MASK (0x0038u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_SHIFT (0x0003u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_RESETVAL (0x0000u)
/*----BURSTMODE Tokens----*/
#define CSL_DMA_DMACH1TCR2_BURSTMODE_1DWORD (0x0000u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_2DWORDS (0x0001u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_4DWORDS (0x0002u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_8DWORDS (0x0003u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_16DWORDS (0x0004u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_RSV5 (0x0005u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_RSV6 (0x0006u)
#define CSL_DMA_DMACH1TCR2_BURSTMODE_RSV7 (0x0007u)

#define CSL_DMA_DMACH1TCR2_SYNCMODE_MASK (0x0004u)
#define CSL_DMA_DMACH1TCR2_SYNCMODE_SHIFT (0x0002u)
#define CSL_DMA_DMACH1TCR2_SYNCMODE_RESETVAL (0x0000u)
/*----SYNCMODE Tokens----*/
#define CSL_DMA_DMACH1TCR2_SYNCMODE_NOSYNC (0x0000u)
#define CSL_DMA_DMACH1TCR2_SYNCMODE_SYNC (0x0001u)

#if ((defined(CHIP_5515)) || (defined(CHIP_5514)))

#define CSL_DMA_DMACH1TCR2_LTSTATUS_MASK (0x0002u)
#define CSL_DMA_DMACH1TCR2_LTSTATUS_SHIFT (0x0001u)
#define CSL_DMA_DMACH1TCR2_LTSTATUS_RESETVAL (0x0000u)

#define CSL_DMA_DMACH1TCR2_EPPMODE_MASK  (0x0001u)
#define CSL_DMA_DMACH1TCR2_EPPMODE_SHIFT (0x0000u)
#define CSL_DMA_DMACH1TCR2_EPPMODE_RESETVAL (0x0000u)

#endif

#define CSL_DMA_DMACH1TCR2_RESETVAL      (0x0000u)

/* DMACH2SSAL */

#define CSL_DMA_DMACH2SSAL_SSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH2SSAL_SSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH2SSAL_SSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2SSAL_RESETVAL      (0x0000u)

/* DMACH2SSAU */

#define CSL_DMA_DMACH2SSAU_SSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH2SSAU_SSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH2SSAU_SSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2SSAU_RESETVAL      (0x0000u)

/* DMACH2DSAL */

#define CSL_DMA_DMACH2DSAL_DSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH2DSAL_DSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH2DSAL_DSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2DSAL_RESETVAL      (0x0000u)

/* DMACH2DSAU */

#define CSL_DMA_DMACH2DSAU_DSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH2DSAU_DSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH2DSAU_DSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2DSAU_RESETVAL      (0x0000u)

/* DMACH2TCR1 */

#define CSL_DMA_DMACH2TCR1_LENGTH_MASK   (0xFFFFu)
#define CSL_DMA_DMACH2TCR1_LENGTH_SHIFT  (0x0000u)
#define CSL_DMA_DMACH2TCR1_LENGTH_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2TCR1_RESETVAL      (0x0000u)

/* DMACH2TCR2 */

#define CSL_DMA_DMACH2TCR2_EN_MASK       (0x8000u)
#define CSL_DMA_DMACH2TCR2_EN_SHIFT      (0x000Fu)
#define CSL_DMA_DMACH2TCR2_EN_RESETVAL   (0x0000u)
/*----EN Tokens----*/
#define CSL_DMA_DMACH2TCR2_EN_ENABLE     (0x0000u)
#define CSL_DMA_DMACH2TCR2_EN_DISABLE    (0x0001u)

#define CSL_DMA_DMACH2TCR2_STATUS_MASK   (0x4000u)
#define CSL_DMA_DMACH2TCR2_STATUS_SHIFT  (0x000Eu)
#define CSL_DMA_DMACH2TCR2_STATUS_RESETVAL (0x0000u)
/*----STATUS Tokens----*/
#define CSL_DMA_DMACH2TCR2_STATUS_DONE   (0x0000u)
#define CSL_DMA_DMACH2TCR2_STATUS_ACTIVE (0x0001u)

#define CSL_DMA_DMACH2TCR2_INTEN_MASK    (0x2000u)
#define CSL_DMA_DMACH2TCR2_INTEN_SHIFT   (0x000Du)
#define CSL_DMA_DMACH2TCR2_INTEN_RESETVAL (0x0000u)
/*----INTEN Tokens----*/
#define CSL_DMA_DMACH2TCR2_INTEN_DISABLE (0x0000u)
#define CSL_DMA_DMACH2TCR2_INTEN_ENABLE  (0x0001u)

#define CSL_DMA_DMACH2TCR2_AUTORLD_MASK  (0x1000u)
#define CSL_DMA_DMACH2TCR2_AUTORLD_SHIFT (0x000Cu)
#define CSL_DMA_DMACH2TCR2_AUTORLD_RESETVAL (0x0000u)
/*----AUTORLD Tokens----*/
#define CSL_DMA_DMACH2TCR2_AUTORLD_DISABLE (0x0000u)
#define CSL_DMA_DMACH2TCR2_AUTORLD_ENABLE (0x0001u)


#define CSL_DMA_DMACH2TCR2_DSTAMODE_MASK (0x0300u)
#define CSL_DMA_DMACH2TCR2_DSTAMODE_SHIFT (0x0008u)
#define CSL_DMA_DMACH2TCR2_DSTAMODE_RESETVAL (0x0000u)
/*----DSTAMODE Tokens----*/
#define CSL_DMA_DMACH2TCR2_DSTAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH2TCR2_DSTAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH2TCR2_DSTAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH2TCR2_DSTAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH2TCR2_SRCAMODE_MASK (0x00C0u)
#define CSL_DMA_DMACH2TCR2_SRCAMODE_SHIFT (0x0006u)
#define CSL_DMA_DMACH2TCR2_SRCAMODE_RESETVAL (0x0000u)
/*----SRCAMODE Tokens----*/
#define CSL_DMA_DMACH2TCR2_SRCAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH2TCR2_SRCAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH2TCR2_SRCAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH2TCR2_SRCAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH2TCR2_BURSTMODE_MASK (0x0038u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_SHIFT (0x0003u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_RESETVAL (0x0000u)
/*----BURSTMODE Tokens----*/
#define CSL_DMA_DMACH2TCR2_BURSTMODE_1DWORD (0x0000u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_2DWORDS (0x0001u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_4DWORDS (0x0002u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_8DWORDS (0x0003u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_16DWORDS (0x0004u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_RSV5 (0x0005u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_RSV6 (0x0006u)
#define CSL_DMA_DMACH2TCR2_BURSTMODE_RSV7 (0x0007u)

#define CSL_DMA_DMACH2TCR2_SYNCMODE_MASK (0x0004u)
#define CSL_DMA_DMACH2TCR2_SYNCMODE_SHIFT (0x0002u)
#define CSL_DMA_DMACH2TCR2_SYNCMODE_RESETVAL (0x0000u)
/*----SYNCMODE Tokens----*/
#define CSL_DMA_DMACH2TCR2_SYNCMODE_NOSYNC (0x0000u)
#define CSL_DMA_DMACH2TCR2_SYNCMODE_SYNC (0x0001u)

#if ((defined(CHIP_5515)) || (defined(CHIP_5514)))

#define CSL_DMA_DMACH2TCR2_LTSTATUS_MASK (0x0002u)
#define CSL_DMA_DMACH2TCR2_LTSTATUS_SHIFT (0x0001u)
#define CSL_DMA_DMACH2TCR2_LTSTATUS_RESETVAL (0x0000u)

#define CSL_DMA_DMACH2TCR2_EPPMODE_MASK  (0x0001u)
#define CSL_DMA_DMACH2TCR2_EPPMODE_SHIFT (0x0000u)
#define CSL_DMA_DMACH2TCR2_EPPMODE_RESETVAL (0x0000u)

#endif

#define CSL_DMA_DMACH2TCR2_RESETVAL      (0x0000u)

/* DMACH3SSAL */

#define CSL_DMA_DMACH3SSAL_SSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH3SSAL_SSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH3SSAL_SSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3SSAL_RESETVAL      (0x0000u)

/* DMACH3SSAU */

#define CSL_DMA_DMACH3SSAU_SSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH3SSAU_SSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH3SSAU_SSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3SSAU_RESETVAL      (0x0000u)

/* DMACH3DSAL */

#define CSL_DMA_DMACH3DSAL_DSAL_MASK     (0xFFFFu)
#define CSL_DMA_DMACH3DSAL_DSAL_SHIFT    (0x0000u)
#define CSL_DMA_DMACH3DSAL_DSAL_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3DSAL_RESETVAL      (0x0000u)

/* DMACH3DSAU */

#define CSL_DMA_DMACH3DSAU_DSAU_MASK     (0xFFFFu)
#define CSL_DMA_DMACH3DSAU_DSAU_SHIFT    (0x0000u)
#define CSL_DMA_DMACH3DSAU_DSAU_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3DSAU_RESETVAL      (0x0000u)

/* DMACH3TCR1 */

#define CSL_DMA_DMACH3TCR1_LENGTH_MASK   (0xFFFFu)
#define CSL_DMA_DMACH3TCR1_LENGTH_SHIFT  (0x0000u)
#define CSL_DMA_DMACH3TCR1_LENGTH_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3TCR1_RESETVAL      (0x0000u)

/* DMACH3TCR2 */

#define CSL_DMA_DMACH3TCR2_EN_MASK       (0x8000u)
#define CSL_DMA_DMACH3TCR2_EN_SHIFT      (0x000Fu)
#define CSL_DMA_DMACH3TCR2_EN_RESETVAL   (0x0000u)
/*----EN Tokens----*/
#define CSL_DMA_DMACH3TCR2_EN_ENABLE     (0x0000u)
#define CSL_DMA_DMACH3TCR2_EN_DISABLE    (0x0001u)

#define CSL_DMA_DMACH3TCR2_STATUS_MASK   (0x4000u)
#define CSL_DMA_DMACH3TCR2_STATUS_SHIFT  (0x000Eu)
#define CSL_DMA_DMACH3TCR2_STATUS_RESETVAL (0x0000u)
/*----STATUS Tokens----*/
#define CSL_DMA_DMACH3TCR2_STATUS_DONE   (0x0000u)
#define CSL_DMA_DMACH3TCR2_STATUS_ACTIVE (0x0001u)

#define CSL_DMA_DMACH3TCR2_INTEN_MASK    (0x2000u)
#define CSL_DMA_DMACH3TCR2_INTEN_SHIFT   (0x000Du)
#define CSL_DMA_DMACH3TCR2_INTEN_RESETVAL (0x0000u)
/*----INTEN Tokens----*/
#define CSL_DMA_DMACH3TCR2_INTEN_DISABLE (0x0000u)
#define CSL_DMA_DMACH3TCR2_INTEN_ENABLE  (0x0001u)

#define CSL_DMA_DMACH3TCR2_AUTORLD_MASK  (0x1000u)
#define CSL_DMA_DMACH3TCR2_AUTORLD_SHIFT (0x000Cu)
#define CSL_DMA_DMACH3TCR2_AUTORLD_RESETVAL (0x0000u)
/*----AUTORLD Tokens----*/
#define CSL_DMA_DMACH3TCR2_AUTORLD_DISABLE (0x0000u)
#define CSL_DMA_DMACH3TCR2_AUTORLD_ENABLE (0x0001u)


#define CSL_DMA_DMACH3TCR2_DSTAMODE_MASK (0x0300u)
#define CSL_DMA_DMACH3TCR2_DSTAMODE_SHIFT (0x0008u)
#define CSL_DMA_DMACH3TCR2_DSTAMODE_RESETVAL (0x0000u)
/*----DSTAMODE Tokens----*/
#define CSL_DMA_DMACH3TCR2_DSTAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH3TCR2_DSTAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH3TCR2_DSTAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH3TCR2_DSTAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH3TCR2_SRCAMODE_MASK (0x00C0u)
#define CSL_DMA_DMACH3TCR2_SRCAMODE_SHIFT (0x0006u)
#define CSL_DMA_DMACH3TCR2_SRCAMODE_RESETVAL (0x0000u)
/*----SRCAMODE Tokens----*/
#define CSL_DMA_DMACH3TCR2_SRCAMODE_INCR (0x0000u)
#define CSL_DMA_DMACH3TCR2_SRCAMODE_RSV1 (0x0001u)
#define CSL_DMA_DMACH3TCR2_SRCAMODE_CONST (0x0002u)
#define CSL_DMA_DMACH3TCR2_SRCAMODE_RSV3 (0x0003u)

#define CSL_DMA_DMACH3TCR2_BURSTMODE_MASK (0x0038u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_SHIFT (0x0003u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_RESETVAL (0x0000u)
/*----BURSTMODE Tokens----*/
#define CSL_DMA_DMACH3TCR2_BURSTMODE_1DWORD (0x0000u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_2DWORDS (0x0001u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_4DWORDS (0x0002u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_8DWORDS (0x0003u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_16DWORDS (0x0004u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_RSV5 (0x0005u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_RSV6 (0x0006u)
#define CSL_DMA_DMACH3TCR2_BURSTMODE_RSV7 (0x0007u)

#define CSL_DMA_DMACH3TCR2_SYNCMODE_MASK (0x0004u)
#define CSL_DMA_DMACH3TCR2_SYNCMODE_SHIFT (0x0002u)
#define CSL_DMA_DMACH3TCR2_SYNCMODE_RESETVAL (0x0000u)
/*----SYNCMODE Tokens----*/
#define CSL_DMA_DMACH3TCR2_SYNCMODE_NOSYNC (0x0000u)
#define CSL_DMA_DMACH3TCR2_SYNCMODE_SYNC (0x0001u)

#if ((defined(CHIP_5515)) || (defined(CHIP_5514)))

#define CSL_DMA_DMACH3TCR2_LTSTATUS_MASK (0x0002u)
#define CSL_DMA_DMACH3TCR2_LTSTATUS_SHIFT (0x0001u)
#define CSL_DMA_DMACH3TCR2_LTSTATUS_RESETVAL (0x0000u)

#define CSL_DMA_DMACH3TCR2_EPPMODE_MASK  (0x0001u)
#define CSL_DMA_DMACH3TCR2_EPPMODE_SHIFT (0x0000u)
#define CSL_DMA_DMACH3TCR2_EPPMODE_RESETVAL (0x0000u)

#endif

#define CSL_DMA_DMACH3TCR2_RESETVAL      (0x0000u)

#endif
