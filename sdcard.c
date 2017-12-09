#include "common.h"

#include <std.h>
#include <gbl.h>

#include <soc.h>
#include <csl_dma.h>
#include <csl_mmcsd.h>
#include <csl_intc.h>

#define CSL_SD_CLOCK_MAX_KHZ      (20000u)

static Uint16 computeClkRate(Uint32 memMaxClk);

static CSL_DMA_Handle hDmaRdSdCard;
static CSL_DMA_Handle hDmaWrSdCard;
static CSL_DMA_ChannelObj dmaChanRdObj;
static CSL_DMA_ChannelObj dmaChanWrObj;
CSL_MmcsdHandle hSdCard;
static CSL_MMCControllerObj pMmcsdContObj;
static CSL_MMCCardObj sdCardObj;
static CSL_MMCCardIdObj sdCardIdObj;
static CSL_MMCCardCsdObj sdCardCsdObj; 
static CSL_CardType cardType;

int initSDCard(void)
{
	CSL_Status status;
	Uint16 rca;
	Uint16 actCard;
	Uint16 clockDiv;

	hDmaRdSdCard = DMA_open(CSL_DMA_CHAN2, &dmaChanRdObj, &status);
	if (status != CSL_SOK) {
		return -1;
	}
	hDmaWrSdCard = DMA_open(CSL_DMA_CHAN3, &dmaChanWrObj, &status);
	if (status != CSL_SOK) {
		return -1;
	}

	hSdCard = MMC_open(&pMmcsdContObj, CSL_MMCSD1_INST,	CSL_MMCSD_OPMODE_DMA, &status);
	if (status != CSL_SOK) {
		return -1;
	}
	(void)MMC_setDmaHandle(hSdCard, hDmaWrSdCard, hDmaRdSdCard);
	
	status = MMC_sendGoIdle(hSdCard);
	if (status != CSL_SOK) {
		return -1;
	}
	status = MMC_selectCard(hSdCard, &sdCardObj);
	if (status != CSL_SOK) {
		return -1;
	}
	if(sdCardObj.cardType == CSL_SD_CARD) {
		cardType = CSL_SD_CARD;

		/* Set the init clock */
	    status = MMC_sendOpCond(hSdCard, 70);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Set the SD Relative Card Address */
		status = SD_sendRca(hSdCard, &sdCardObj, &rca);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Send the SD card identification Data */
		status = SD_sendAllCID(hSdCard, &sdCardIdObj);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Read the SD Card Specific Data */
		status = SD_getCardCsd(hSdCard, &sdCardCsdObj);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Get the clock divider value for the current CPU frequency */
		clockDiv = computeClkRate(CSL_SD_CLOCK_MAX_KHZ);
		/* Set the card type in internal data structures */
		status = MMC_setCardType(&sdCardObj, cardType);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Set the card pointer in internal data structures */
		status = MMC_setCardPtr(hSdCard, &sdCardObj);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Get the number of cards */
		status = MMC_getNumberOfCards(hSdCard, &actCard);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Set clock for read-write access */
		status = MMC_sendOpCond(hSdCard, clockDiv);
		if (status != CSL_SOK) {
			return -1;
		}
		/* Set Endian mode for read and write operations */
  		status = MMC_setEndianMode(hSdCard, CSL_MMCSD_ENDIAN_LITTLE, CSL_MMCSD_ENDIAN_LITTLE);
		if (status != CSL_SOK) {
			return -1;
		}
	} else {
		return -1;
	}
	return 0;
}

static Uint16 computeClkRate(Uint32 memMaxClk)
{
	Uint32    sysClock;
	Uint32    remainder;
	Uint16    clkRate;

	clkRate = 0;

	/* Get the clock value at which CPU is running */
	sysClock = GBL_getFrequency();

	if (sysClock > memMaxClk) {
		clkRate   = sysClock / memMaxClk;
		remainder = sysClock % memMaxClk;
        // If the remainder is not equal to 0, increment clock rate to make
        // sure that memory clock value is less than the value of 'memMaxClk'.
		if (remainder != 0)	{
			clkRate++;
		}
        // memory clock divider '(2 * (CLKRT + 1)' will always
        // be an even number. Increment the clock rate in case of
        // clock rate is not an even number.
		if (clkRate%2 != 0) {
			clkRate++;
		}
		// AT this point 'clkRate' holds the value of (2 * (CLKRT + 1).
		// Get the value of CLKRT.
		clkRate = clkRate/2-1;
		// If the clock rate is more than the maximum allowed clock rate
		// set the value of clock rate to maximum value.
		// This case will become true only when the value of
		// 'memMaxClk' is less than the minimum possible
		// memory clock that can be generated at a particular CPU clock.
		if (clkRate > CSL_MMC_MAX_CLOCK_RATE) {
			clkRate = CSL_MMC_MAX_CLOCK_RATE;
		}
	}
	return clkRate;
}

