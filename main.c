#include <std.h>
#include <sio.h>
#include <gbl.h>
#include <stdio.h>
#include "common.h"
#include "md_aic3204.h"
#include "oled.h"
#include "keys.h"
#include <ff.h>
#include "twiddle_I.h"
#include "twiddle_R.h"

#include <soc.h>
#include <csl_mmcsd.h>
#include <csl_sar.h>
#include <csl_pll.h>

void genSinus(Int16* buf);

#pragma DATA_ALIGN(audBufs, 4);	// align buffer Tx for DMA
PCM_SAMPLE_TYPE audBufs[NUM_OUT_BUFS][WORDS_PER_OUT_BUF];

#pragma DATA_SECTION(RcvL, "samples_section")
#pragma DATA_ALIGN(RcvL, 4);	// align buffer Rx for DMA
Int16 RcvL[BUFS_FFT][FFT_LENGTH];

#pragma DATA_SECTION(scratch_buf, "scratch_section")
#pragma DATA_ALIGN(scratch_buf,FFT_LENGTH*2);	// align buffer for FFT
Int32 scratch_buf[FFT_LENGTH];

#pragma DATA_SECTION(data_buf, "data_section")
#pragma DATA_ALIGN(data_buf,FFT_LENGTH*2);	// align buffer for FFT
Int32 data_buf[FFT_LENGTH];

#pragma DATA_SECTION(twiddle, "twiddle_section")
Int32 twiddle[FFT_LENGTH/2];

#pragma DATA_SECTION(tmpx, "tmp_section")
Int16 tmpx[FFT_LENGTH/2];

char Tx_fname[13];
const char* Tx_fnptr = Tx_fname;
int Tx_status = 0;
int Rx_status = 0;
BYTE buffer[512];
extern int initSDCard(void);
extern void initHumanIF(void);
Int32 twiddle_output;
int tw;

static int init_PLL(void);

SIO_Handle hStreamOut;
SIO_Handle hStreamIn;
FATFS FatFs;
DIR dirObj;
	

void main(void)
{
	FRESULT res;
//	int xx;
	int ih;
	SIO_Attrs aud_attrs = {
		NUM_OUT_BUFS,		// nbufs
		0,					// segid
		2,					// align
		FALSE,				// flush
		SIO_ISSUERECLAIM,	// model
		SYS_FOREVER,		// timeout
		NULL};				// callback

	IRQ_globalEnable();				// enable interrupt globally
	
	hStreamIn = SIO_create("/audioDAC" , SIO_INPUT, FFT_LENGTH*2, &aud_attrs);
	
	hStreamOut = SIO_create("/audioDAC" , SIO_OUTPUT, WORDS_PER_OUT_BUF*sizeof(PCM_SAMPLE_TYPE), &aud_attrs);
	
//xx=WORDS_PER_OUT_BUF*sizeof(PCM_SAMPLE_TYPE);
puts("ff");
//puts(xx);
	if (initSDCard() != 0) {
		RED_ON								// red LED on means we got problems accessing SD card
	}
	f_mount(0, &FatFs);						// mount file system
	
	res = f_opendir(&dirObj, "0:/");		// open root dir
	if (res != FR_OK) {						// green LED on means we got problems with the FS
		
	}
	init_Keys();							// self-explaining
	init_OLED();							// self-explaining
	
	for(ih=0;ih<FFT_LENGTH;++ih) {
		data_buf[ih] =0;
	}
		for(ih=0;ih<FFT_LENGTH/2;++ih) {
		twiddle[ih] =0;
	}
	
	for(tw=0;tw<1024;tw++) {
		twiddle_output = (((Int32)twiddle_R[tw] & 0x0000FFFF)<< 16);
		twiddle_output = twiddle_output | ((Int32)twiddle_I[tw] & 0x0000FFFF);	
		twiddle[tw]=twiddle_output;
		//tmpx[tw] = twiddle_R[tw];
		//tmpx[tw] = twiddle_I[tw];
	}
	for(tw=0;tw<1024;tw++) {
		twiddle_output = (((Int32)(-twiddle_I[1023-tw]) & 0x0000FFFF)<< 16);
		twiddle_output = twiddle_output | ((Int32)(-twiddle_R[1023-tw]) & 0x0000FFFF);	
		twiddle[1024+tw]=twiddle_output;
		//tmpx[1024+tw]= -twiddle_I[1023-tw];
		//tmpx[1024+tw]= -twiddle_R[1023-tw];
	}
	for(tw=0;tw<1024;tw++) {
		twiddle_output = (((Int32)(twiddle_I[tw]) & 0x0000FFFF)<< 16);
		twiddle_output = twiddle_output | ((Int32)(-twiddle_R[tw]) & 0x0000FFFF);	
		twiddle[2048+tw]=twiddle_output;
		//tmpx[2048+tw]= twiddle_I[tw];
		//tmpx[2048+tw]= -twiddle_R[tw];
	}
	for(tw=0;tw<1024;tw++) {
		twiddle_output = (((Int32)(-twiddle_R[1023-tw]) & 0x0000FFFF)<< 16);
		twiddle_output = twiddle_output | ((Int32)(twiddle_I[1023-tw]) & 0x0000FFFF);	
		twiddle[3072+tw]=twiddle_output;
		//tmpx[3072+tw]= -twiddle_R[1023-tw];
		//tmpx[3072+tw]= twiddle_I[1023-tw];
	}

	
	
	GREEN_ON
	
	// when program counter falls out of the main() function RTOS DSP/BIOS takes control
}


// called at the very beginning of execution
void sysInit()
{
	*(ioport volatile unsigned *)0x0001 = 0x000E;	// ICR 
	asm(" nop_16");
	asm(" nop_16");
	asm(" nop_16");
	asm(" nop_16");
	asm(" nop_16");
	asm(" nop_16");
	asm(" idle");
    
	*(ioport volatile unsigned *)0x1C02 = 0x0000;	// PCGCR1 - you can switch off unused peripherals to save power
	*(ioport volatile unsigned *)0x1C03 = 0x0000;	// PCGCR2 - you can switch off unused peripherals to save power

	*(ioport volatile unsigned *)0x1C04 = 0x0020;	// PSRCR
	*(ioport volatile unsigned *)0x1C05 = 0x00B3;	// PRCR - reset peripherals
	*(ioport volatile unsigned *)0x1C00 = 0x6100;	// EBSR - PPMODE:6, MMC/SD1, I2S0

	init_PLL();										// configure PLL
	
	MMC_init();										// self-explaining
	DMA_init();										// self-explaining
	SAR_init();										// self-explaining
//	*(ioport volatile unsigned *)0x1C24 = 0x0;		// CLKOUT pin driven by DSP clk
//	asm(" BCLR CLKOFF");							// let clock come through - for debug purpose
	
	// make GPIO's ready to drive the 4 colored LEDs
	*(ioport volatile unsigned *)0x1C06 = 0xC000;	// gpio dir
	*(ioport volatile unsigned *)0x1C07 = 0x0003;	// gpio dir
	*(ioport volatile unsigned *)0x1C0A = 0xC000;	// LED off
	*(ioport volatile unsigned *)0x1C0B = 0x0003;	// LED off
}

static int init_PLL()
{
	PLL_Obj pllObj;
	PLL_Handle hPll;
#if DSP_FREQ_KHZ == 40000
	PLL_Config pllCfg = {0x8988, 0x8000, 0x0806, 0x0201};
#elif DSP_FREQ_KHZ == 60000
	PLL_Config pllCfg = {0x8724, 0x8000, 0x0806, 0x0000};
#elif DSP_FREQ_KHZ == 100000
	PLL_Config pllCfg = {0x8BE8, 0x8000, 0x0806, 0x0000};
#endif
    CSL_Status status;
	
    status = PLL_init(&pllObj, CSL_PLL_INST_0);
    if(status != CSL_SOK) {
       return status;
    }
	hPll = (PLL_Handle)(&pllObj);
	PLL_reset(hPll);
	
	status = PLL_config (hPll, &pllCfg);
    if(status != CSL_SOK) {
       return status;
    }
    status = PLL_bypass(hPll);
    if(status != CSL_SOK) {
       return status;
    }
	status = PLL_enable(hPll);
    if(status != CSL_SOK) {
       return status;
    }
    GBL_setFrequency(DSP_FREQ_KHZ);		// make sure MMC/SD and I2C work with correct frequency always
	return CSL_SOK;
}

