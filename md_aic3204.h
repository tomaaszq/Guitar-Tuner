#ifndef MD_AIC3204_H_
#define MD_AIC3204_H_

#include <soc.h>
#include <csl_i2s.h>
#include <csl_i2c.h>
#include <csl_dma.h>
#include <csl_intc.h>

#define CSL_I2C_BUS_FREQ (100)    	// kHz
#define CSL_I2C_OWNADDR  (0)		// not used

typedef struct {
	I2S_Instance i2sInstance;
	I2S_Config* i2sCfg;
	Uint16 i2cInstance;
	Uint16 i2cSlaveAddr;
	CSL_I2cSetup* i2cCfg;
	CSL_DMAChanNum dmaNumLeftChan;
	CSL_DMAChanNum dmaNumRightChan;
	CSL_DMA_Config* dmaCfg;
} C5515_AIC3204_DEVPARAMS;

#endif /*MD_AIC3204_H_*/
