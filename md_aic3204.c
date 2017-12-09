#include <std.h>
#include <iom.h>
#include <gbl.h>

#include "common.h"
#include "md_aic3204.h"

#include "soc.h"

static void createDMASrcAddr(IOM_Packet * const packet);
static void createDMADstAddr(IOM_Packet * const packet);
static Bool hasTriggered(Uint32 addr);

I2S_Config I2S_PARAMS = {
	I2S_MONO_ENABLE,			/* new one channel */ 
	I2S_LOOPBACK_DISABLE,
	I2S_FSPOL_LOW,				/* left channel fs low */
	I2S_RISING_EDGE,
	I2S_DATADELAY_ONEBIT,
	I2S_DATAPACK_ENABLE,
	I2S_SIGNEXT_DISABLE,
	I2S_WORDLEN_16,				/* 16bit/sample */
	I2S_SLAVE,					/* AIC3204 drives I2S */
	I2S_DATAFORMAT_LJUST,		/* I2S format */
	I2S_FSDIV8,					/* not used */
	I2S_CLKDIV2,				/* not used */
	I2S_FSERROR_DISABLE,
	I2S_OUERROR_DISABLE
};

CSL_I2cSetup I2C_PARAMS = {
	CSL_I2C_ADDR_7BIT,
	CSL_I2C_BC_8BITS,
	CSL_I2C_LOOPBACK_DISABLE,
	CSL_I2C_FREEMODE_DISABLE,
	CSL_I2C_REPEATMODE_DISABLE,
	CSL_I2C_OWNADDR,
	0,							/* DSP frequency, to be defined during runtime */					
	CSL_I2C_BUS_FREQ			/* bit clock is 100kHz */
};

CSL_DMA_Config DMA_PARAMS_CODEC = {
	CSL_DMA_PING_PONG_DISABLE,
	CSL_DMA_AUTORELOAD_ENABLE,
	CSL_DMA_TXBURST_1WORD,
	CSL_DMA_EVENT_TRIGGER,
	CSL_DMA_EVT_I2S0_TX,
	CSL_DMA_INTERRUPT_DISABLE,
	CSL_DMA_WRITE,
	CSL_DMA_TRANSFER_IO_MEMORY,
	WORDS_PER_OUT_BUF/2*2*sizeof(PCM_SAMPLE_TYPE),	// transfer size for one chan [in bytes]
	0,												// srcAddr - to be defined later
	0												// dstAddr - to be defined later
};

const C5515_AIC3204_DEVPARAMS AIC3204_DEVPARAMS = {
	I2S_INSTANCE0,
	&I2S_PARAMS,
	CSL_I2C0,
	AIC3204_I2C_ADDR,
	&I2C_PARAMS,
	CSL_DMA_CHAN0,
	CSL_DMA_CHAN1,
	&DMA_PARAMS_CODEC
};
// config AIC3204
static Uint16 i2c_addr_data[] = {
     0, 0x00,		// Select page 0
     1, 0x01,      // Reset codec
     0, 0x01,      // Point to page 1
     1, 0x08,      // Disable crude AVDD generation from DVDD
     2, 0x01,      // Enable Analog Blocks, use LDO power
	 /* PLL and Clocks config and Power Up*/
     0, 0x00,      // Select page 0
    55, 0x05,	   // MFP4  MISO is INT2 output
    27, 0x4d,      // *BCLK and WCLK is set as o/p to AIC3204(Master),  Audio Interface = DSP (I2S),  Data Word length = 16 bits
    28, 0x01,	   // *Data offset setting, Data Offset = 1 BCLK's
     4, 0x03,      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
     6, 0x07,      // PLL setting: J=7
     7, 0x02,      // PLL setting: HI_BYTE(D) 15
     8, 0x30,      // PLL setting: LO_BYTE(D) dc
    30, 0x88,      // BCLK N Divider, For 32 bit clocks per frame in Master mode ONLY
     5, 0x91,      // PLL setting: Power up PLL, P=1 and R=1
    13, 0x00,      // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    14, 0x80,      // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    20, 0x80,      // AOSR for AOSR = 128 decimal or 0x0080
    11, 0x85,      // Power up NDAC and set NDAC value to 5
    12, 0x83,      // Power up MDAC and set MDAC value to 3
    18, 0x99,	   // *Power up NADC and set NDAC value to 25
    19, 0x83,	   // *Power up MADC and set MDAC value to 3
    /* DAC ROUTING and Power Up */
     0, 0x01,      // Select page 1
    12, 0x08,      // LDAC AFIR routed to HPL RR
    13, 0x08,      // RDAC AFIR routed to HPR RR
     0, 0x00,      // Select page 0
    64, 0x02,      // Left vol=right vol
				   // 0x80  + 63, 0x98 Right DAC Channel is powered down, the Right DAC Modulator output data is inverted
				   // version of Left DAC Modulator Output. Can be used when differential mono output is used
    65, 0x00,      // Left DAC gain to 0dB VOL;
    63, 0xd8,      // * 0xd8 Right DAC data is Left Channel Audio Interface Data - mono
     0, 0x01,      // Select page 1
    16, 0x3a,      // Unmute HPL , -6dB gain
    17, 0x3a,      // Unmute HPR , -6dB gain
     9, 0x30,      // Power up HPL,HPR 
     /* ADC ROUTING and Power Up */
     0, 0x01,      // *Select page 1
    52, 0x10,	   // *IN2_L to micPDA through 40 kohm	| 0x30=40kOhm, 0x10=10kOhm
    55, 0x00,	   // *IN2_R not routed to RADC_P
    54, 0x40,	   // *CM is routed to Left MICPGA via CM1L with 10K resistance
    57, 0x00,	   // *not routed
    59, 0x14,	   // *MIC_PGA_L unmute/vol +10dB
    60, 0x80,	   // *MIC_PGA_R mute
     0, 0x00,	   // *Select page 0
    81, 0x80,	   // *Power up Left ADC
    82, 0x08,	   // *Unmute Left and Right ADC
    
 65535, 65535,     // wait...
};

static Int mdBindDev(Ptr *devp, Int devid, Ptr devParams);
static Int mdControlChan(Ptr chanp, Uns cmd, Ptr arg);
static Int mdCreateChan(Ptr *chanp, Ptr devp, String name, Int mode,
                		Ptr chanParams, IOM_TiomCallback cbFxn, Ptr cbArg);
static Int mdSubmitChan(Ptr chanp, IOM_Packet * const packet);


IOM_Fxns AIC3204_FXNS = {
	mdBindDev,					// called during init of program
	IOM_UNBINDDEVNOTIMPL,
	mdControlChan,				// control of the codec through I2C
	mdCreateChan,				// called by SIO_create()
	IOM_DELETECHANNOTIMPL,
	mdSubmitChan				// called by SIO_issue()
};

typedef struct ChanObj {
	Bool inuse;					// TRUE => channel is open
	Int mode;					// IIOM_OUTPUT only
	IOM_Packet *dataPacket; 	// active I/O packet
	IOM_Packet *pendPacket;		// pending I/O packet
	QUE_Obj pendList; 			// list of packets for I/O
	IOM_TiomCallback cbFxn; 	// to notify client
	Ptr cbArg;
} ChanObj, *ChanHandle;

#define NUMCHANS 2 /* INPUT and OUTPUT */
static ChanObj chans[NUMCHANS] = {{ FALSE, IOM_OUTPUT, NULL, NULL, NULL, NULL},
						{ FALSE, IOM_INPUT, NULL, NULL, NULL, NULL}};

static CSL_I2sHandle hI2s;
static CSL_DMA_Handle hDmaLChanTx;
static CSL_DMA_Handle hDmaLChanRx;
static CSL_DMA_ChannelObj dmaChanObjLeftTx;
static CSL_DMA_ChannelObj dmaChanObjLeftRx;

static Int mdBindDev(Ptr *devp, Int devid, Ptr devParams)
{
	C5515_AIC3204_DEVPARAMS* params = (C5515_AIC3204_DEVPARAMS*)devParams; 
	CSL_Status status;
	int i;
	
    if (devParams == NULL || devp == NULL) {
        return IOM_EBADARGS;
    }
	// open/init I2S
	hI2s = I2S_open(params->i2sInstance, DMA_INTERRUPT, I2S_CHAN_MONO); //* Mono
	if (hI2s == NULL) {
		return IOM_EALLOC;
	}
	status = I2S_setup(hI2s, params->i2sCfg);
	if (status != CSL_SOK) {
		return IOM_EBADIO;
	}
	// open/init I2C
	status = I2C_init(params->i2cInstance);
	if (status != CSL_SOK) {
		return status;
	}
	params->i2cCfg->sysInputClk = GBL_getFrequency()/1000;
	status = I2C_setup(params->i2cCfg);
	if (status != CSL_SOK) {
		return IOM_EBADIO;
	}
	// configure AIC3204
	for (i=0; i<sizeof(i2c_addr_data); i+=2) {
		volatile Uint32 cnt;
		
		if (i2c_addr_data[i] < 65535) {
			status = I2C_write(&i2c_addr_data[i], 2, params->i2cSlaveAddr, TRUE, (CSL_I2C_START | CSL_I2C_STOP), CSL_I2C_MAX_TIMEOUT);
			if (status != CSL_SOK) {
				return status;
			}
			for (cnt=0; cnt<65535 ;cnt++);
		} else {
    		for (cnt=0; cnt<i2c_addr_data[i+1] ;cnt++);
    		for (cnt=0; cnt<i2c_addr_data[i+1] ;cnt++);
		}		
	}
	// open/init DMA channel from memory to I2S for left audio channel
	hDmaLChanTx = DMA_open(CSL_DMA_CHAN0, &dmaChanObjLeftTx, &status);
	if (status != CSL_SOK) {
		return status;
	}
	params->dmaCfg->destAddr = (Uint32)0x2808;	
	params->dmaCfg->dmaInt = CSL_DMA_INTERRUPT_ENABLE;
	status = DMA_config(hDmaLChanTx, params->dmaCfg);
	if (status != CSL_SOK) {
		return status;
	}
	// open/init DMA channel from I2S to memory for left audio channel
	hDmaLChanRx = DMA_open(CSL_DMA_CHAN1, &dmaChanObjLeftRx, &status);
	if (status != CSL_SOK) {
		return status;
	}	 
	params->dmaCfg->dmaEvt = CSL_DMA_EVT_I2S0_RX;
	params->dmaCfg->chanDir = CSL_DMA_READ;
	params->dmaCfg->dmaInt = CSL_DMA_INTERRUPT_ENABLE;
	params->dmaCfg->dataLen = FFT_LENGTH*2;
	params->dmaCfg->srcAddr = (Uint32)0x2828;
	status = DMA_config(hDmaLChanRx, params->dmaCfg);
	if (status != CSL_SOK) {
		return status;
	}
	*devp = &chans;
	return IOM_COMPLETED;
}

 
static Int mdControlChan(Ptr chanp, Uns cmd, Ptr arg) 
{
	static Int32 current_fs = 44100;
	CSL_Status status;
	volatile int delay;
	
	if (cmd == AIC3204_CMD_SET_VOLUME) {			// set volume
		Uint16 data[2];
		
		data[0] = 33; //65
		data[1] = *(Uint16*)arg;
		status = I2C_write(data, 2, AIC3204_DEVPARAMS.i2cSlaveAddr, TRUE, (CSL_I2C_START) | (CSL_I2C_STOP), CSL_I2C_MAX_TIMEOUT);
		delay=4096;
		while(delay--);
		
	} else if (cmd == AIC3204_CMD_SET_SRATE) {		// change sampling frequency (adjust PLL in AIC3204)
		if (*(Int32*)arg == current_fs) {
			return IOM_COMPLETED;
		} else {
			int idx;
			// add all missing sampling rates: 32k, 24k, 22.05k, 16k, 12k, 11.025k, 8k
			// for 44.1k <> 48k switch only NDAC, MDAC & J changes
			// values sued from AIC3204 data sheet pg. 84 (lit# SLOS602A)
			Uint16 pll_regval[2][6] = {{0x0b, 0x85, 0x83, 0x0d, 0x00, 0x80},   //*44.1kHz
					  		           {0x0b, 0x87, 0x82, 0x0d, 0x00, 0x7e}};  //*48kHz
			if (*(Int32*)arg == 44100) {
				idx = 0;
			} else if (*(Int32*)arg == 48000) {
				idx = 1;
			} else {
				return IOM_COMPLETED;
			}
			status = I2C_write(&pll_regval[idx][0], 3, AIC3204_DEVPARAMS.i2cSlaveAddr, TRUE, (CSL_I2C_START) | (CSL_I2C_STOP), CSL_I2C_MAX_TIMEOUT);
			delay=4096;
			while(delay--);
			status = I2C_write(&pll_regval[idx][3], 3, AIC3204_DEVPARAMS.i2cSlaveAddr, TRUE, (CSL_I2C_START) | (CSL_I2C_STOP), CSL_I2C_MAX_TIMEOUT);
			delay=4096;
			while(delay--);
			current_fs = *(Int32*)arg;
		}
	}
	if (status != CSL_SOK) {
		return status;
	} 
	return IOM_COMPLETED;
}

static Int mdCreateChan(Ptr *chanp, Ptr devp, String name, Int mode,
                		Ptr chanParams, IOM_TiomCallback cbFxn, Ptr cbArg)
{
	ChanHandle chans = (ChanHandle)devp;
	ChanHandle chan;
	if (mode == IOM_INPUT) {
	chan = &chans[1]; /* input only channel */
	}
	else if (mode == IOM_OUTPUT) {
	chan = &chans[0]; /* output only channel */
	}
	else {
	/* bi-directional channels not supported */
	return (IOM_EBADMODE);
	}
	
	if (ATM_setu((Uns*)&chan->inuse, TRUE)) {	// channel already open
		return IOM_EBADIO;
	}
	QUE_new(&chan->pendList);
	chan->dataPacket = NULL;
	chan->pendPacket = NULL;
	chan->cbFxn = cbFxn;
	chan->cbArg = cbArg;
	if (mode == IOM_OUTPUT) {
	IRQ_enable(DMA_EVENT);
	}
	*chanp = chan;
		
	return IOM_COMPLETED;
}

static Int mdSubmitChan(Ptr chanp, IOM_Packet * const packet)
{
	//ChanHandle chans = (ChanHandle)chanp;
	ChanHandle chan = (ChanHandle)chanp;
/*	if (mode == IOM_INPUT) {
	chan = &chans[1];  input only channel 
	}
	else if (mode == IOM_OUTPUT) {
	chan = &chans[0];  output only channel
	}*/	
	if (packet->cmd == IOM_FLUSH || packet->cmd == IOM_ABORT) {
		packet->status = IOM_COMPLETED;
		return IOM_COMPLETED;
	}

	if (chan->mode == IOM_OUTPUT) {	
		if (chan->dataPacket == NULL) {			// no audio transfer	
			chan->dataPacket = packet;
			createDMASrcAddr(packet);
			DMA_start(hDmaLChanTx);
			I2S_transEnable(hI2s, TRUE);
			// make sure first data has transfered so source address can be overwritten by pending transfer
			while(!hasTriggered((Uint32)&((PCM_SAMPLE_TYPE*)packet->addr)[packet->size/2]));
		} else if (chan->pendPacket == NULL) {	// audio transfer running, no job pending
			chan->pendPacket = packet;
			createDMASrcAddr(packet);
		} else {								// audio transfer running, job pending
			QUE_put(&chan->pendList, packet);
		}
	}
	else if (chan->mode == IOM_INPUT) {
		if (chan->dataPacket == NULL) {			// no audio transfer	
			chan->dataPacket = packet;
			createDMADstAddr(packet);
			DMA_start(hDmaLChanRx);
			I2S_transEnable(hI2s, TRUE);
			// make sure first data has transfered so source address can be overwritten by pending transfer
			//while(!hasTriggered((Uint32)&((PCM_SAMPLE_TYPE*)packet->addr)[packet->size/2]));
		} else if (chan->pendPacket == NULL) {	// audio transfer running, no job pending
			chan->pendPacket = packet;
			createDMADstAddr(packet);
		} else {								// audio transfer running, job pending
			QUE_put(&chan->pendList, packet);
		}		
	}
	return IOM_PENDING;
}

void interrupt_DMA01(void)
{
	IOM_Packet* tmpPacket;
	chans[0].dataPacket->status = IOM_COMPLETED;
	tmpPacket = chans[0].dataPacket;
	chans[0].dataPacket = chans[0].pendPacket;
	if (chans[0].dataPacket == NULL) {
		//I2S_transEnable(hI2s, FALSE); //do analizy
		DMA_stop(hDmaLChanTx);
		//DMA_stop(hDmaRChan);
	} else {
		chans[0].pendPacket = QUE_get(&chans[0].pendList);
		if (chans[0].pendPacket == (IOM_Packet*)&chans[0].pendList) {
			chans[0].pendPacket = NULL;
		} else {
			createDMASrcAddr(chans[0].pendPacket);
		}
	}
	(*chans[0].cbFxn)(chans[0].cbArg, tmpPacket);
}


void interrupt_DMA02(void)
{
	IOM_Packet* tmpPacket;
	chans[1].dataPacket->status = IOM_COMPLETED;
	tmpPacket = chans[1].dataPacket;
	chans[1].dataPacket = chans[1].pendPacket;
	if (chans[1].dataPacket == NULL) {
		//I2S_transEnable(hI2s, FALSE); do analizy
		DMA_stop(hDmaLChanRx);
		//DMA_stop(hDmaRChan);
	} else {
		chans[1].pendPacket = QUE_get(&chans[1].pendList);
		if (chans[1].pendPacket == (IOM_Packet*)&chans[1].pendList) {
			chans[1].pendPacket = NULL;
		} else {
			createDMADstAddr(chans[1].pendPacket);
		}
	}
	(*chans[1].cbFxn)(chans[1].cbArg, tmpPacket);
}
// wait until first word of right channel is transfered to I2S
// this means dma parameter has been copied and cannot be overwritten by a new transfer job
static Bool hasTriggered(Uint32 addr)
{
	Uint32 regValue, baseAddr;
    if ((addr >= CSL_DMA_DARAM_START_ADDR) && (addr <= CSL_DMA_DARAM_END_ADDR)) {
		baseAddr = (addr << CSL_DMA_ADDR_SHIFT) + CSL_DMA_DARAM_ADDR_OFFSET;
	} else if ((addr >= CSL_DMA_SARAM_START_ADDR) && (addr <= CSL_DMA_SARAM_END_ADDR)) {
		baseAddr = (addr << CSL_DMA_ADDR_SHIFT) + CSL_DMA_SARAM_ADDR_OFFSET;
    } else {
    	baseAddr = addr;
    }
	//regValue = CSL_FEXT(hDmaRChan->dmaRegs->DMACH1SSAL, DMA_DMACH1SSAL_SSAL);
	//regValue |= (Uint32)CSL_FEXT(hDmaRChan->dmaRegs->DMACH1SSAU, DMA_DMACH1SSAU_SSAU) << CSL_DMA_UINT16_NUMBER_BITS;
	regValue = CSL_FEXT(hDmaLChanTx->dmaRegs->DMACH0SSAL, DMA_DMACH0SSAL_SSAL); // *Lchan - mono
	regValue |= (Uint32)CSL_FEXT(hDmaLChanTx->dmaRegs->DMACH0SSAU, DMA_DMACH0SSAU_SSAU) << CSL_DMA_UINT16_NUMBER_BITS; // *Lchan - mono
    return baseAddr != regValue;
}

// some calculation for source address needed, do it in separate function
static void createDMASrcAddr(IOM_Packet * const packet)
{
	Uint32 dmaAddrL;
	Uint32 addrL = (Uint32)packet->addr;
	//Uint32 addrR = (Uint32)&((PCM_SAMPLE_TYPE*)packet->addr)[packet->size/2];
	
    if ((addrL >= CSL_DMA_DARAM_START_ADDR) && (addrL <= CSL_DMA_DARAM_END_ADDR)) {
		dmaAddrL = (addrL << CSL_DMA_ADDR_SHIFT) + CSL_DMA_DARAM_ADDR_OFFSET;
		//dmaAddrR = (addrR << CSL_DMA_ADDR_SHIFT) + CSL_DMA_DARAM_ADDR_OFFSET;
	} else if ((addrL >= CSL_DMA_SARAM_START_ADDR) && (addrL <= CSL_DMA_SARAM_END_ADDR)) {
		dmaAddrL = (addrL << CSL_DMA_ADDR_SHIFT) + CSL_DMA_SARAM_ADDR_OFFSET;
		//dmaAddrR = (addrR << CSL_DMA_ADDR_SHIFT) + CSL_DMA_SARAM_ADDR_OFFSET;
    } else {
    	dmaAddrL = addrL;
    	//dmaAddrR = addrR;
    }
    CSL_FINS(hDmaLChanTx->dmaRegs->DMACH0SSAL, DMA_DMACH0SSAL_SSAL, (dmaAddrL & CSL_DMA_UINT16_MASK));
	CSL_FINS(hDmaLChanTx->dmaRegs->DMACH0SSAU, DMA_DMACH0SSAU_SSAU, (Uint16)(dmaAddrL >> CSL_DMA_UINT16_NUMBER_BITS));

} 

static void createDMADstAddr(IOM_Packet * const packet)
{
	Uint32 dmaAddrL;
	Uint32 addrL = (Uint32)packet->addr;
	
    if ((addrL >= CSL_DMA_DARAM_START_ADDR) && (addrL <= CSL_DMA_DARAM_END_ADDR)) {
		dmaAddrL = (addrL << CSL_DMA_ADDR_SHIFT) + CSL_DMA_DARAM_ADDR_OFFSET;

	} else if ((addrL >= CSL_DMA_SARAM_START_ADDR) && (addrL <= CSL_DMA_SARAM_END_ADDR)) {
		dmaAddrL = (addrL << CSL_DMA_ADDR_SHIFT) + CSL_DMA_SARAM_ADDR_OFFSET;

    } else {
    	dmaAddrL = addrL;
    }
    CSL_FINS(hDmaLChanRx->dmaRegs->DMACH1DSAL, DMA_DMACH1DSAL_DSAL, (dmaAddrL & CSL_DMA_UINT16_MASK));
	CSL_FINS(hDmaLChanRx->dmaRegs->DMACH1DSAU, DMA_DMACH1DSAU_DSAU, (Uint16)(dmaAddrL >> CSL_DMA_UINT16_NUMBER_BITS));
} 
                			  	

