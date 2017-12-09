/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2008
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_general.h
 *
 *  @brief CSL general header file
 *
 *  This file contains the general CSL macros or definitions that are required
 *  to enable few functionalities specific to the chip revision. This file is
 *  included in all the cslr files. All the CSL applications should include
 *  this file.
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 07-Jan-2009 Created
 * ============================================================================
 */


#ifndef _CSL_GENERAL_H_
#define _CSL_GENERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* CAUTION: DEFINE EITHER THE MACRO 'CHIP_5505' OR 'CHIP_5515'. DO NOT DEFINE
            BOTH MACROS. */

/** This macro is used to enable the source code specific to chip versions
    TMS320VC5505 and TMS320VC5504 */
//#define CHIP_5505

#ifndef CHIP_5505

/** This macro is used to enable the source code specific to chip versions
    TMS320VC5515 and TMS320VC5514 */
#define CHIP_5515

#endif


#ifdef __cplusplus
}
#endif

#endif    // _CSL_GENERAL_H_

