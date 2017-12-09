/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *  
 */
/* "@(#) XDAS 2.51.00 10-12-04 (xdas-e11)" */
/*
 *  ======== alg_control.c ========
 *  ALG_control implementation.  This is common to all implementations
 *  of the ALG module.
 */
#include <std.h>
#include <alg.h>
#include <ialg.h>

/*
 *  ======== ALG_control ========
 */
Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *statusPtr)
{
    if (alg && alg->fxns->algControl) {
        return (alg->fxns->algControl(alg, cmd, statusPtr));
    }

    return (IALG_EFAIL);
}
