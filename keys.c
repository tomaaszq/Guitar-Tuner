#include <std.h>
#include <sio.h>
#include <tsk.h>

#include "common.h"

#include <soc.h>
#include <csl_sar.h>

CSL_SarHandleObj SarObj;
CSL_SarHandleObj *hSar;

#define SW1   0x2A8  // Switch 1 value
#define SW2   0x1FC  // Switch 2 value
#define SW12  0x195  // Switch 1 + 2 value
#define NoKey 0x3FE

//extern SIO_Handle hStreamOut;

void init_Keys(void)
{
	CSL_SarChSetup param; 
	int chanNo;
	
	SAR_chanOpen(&SarObj,CSL_SAR_CHAN_3);
	hSar = &SarObj;
	SAR_chanInit(hSar);

    param.OpMode = CSL_SAR_POLLING;
    param.MultiCh = CSL_SAR_DISCHARGE_ARRAY;
    param.RefVoltage = CSL_SAR_REF_VIN;
    param.SysClkDiv = 0x31 ;
    /* Configuration for SAR module */
    SAR_chanSetup(hSar, &param);
	SAR_A2DMeasParamSet(hSar, CSL_KEYPAD_MEAS, &chanNo);
	SAR_chanCycSet(hSar, CSL_SAR_SINGLE_CONVERSION);
	SAR_startConversion(hSar);
}

 

int handleKeys(void)
{
	//static Int16 vol = 0x0000;	// the volume value the AIC3204 was initialized during startup (0dB)
	Uint16 adc_value;
	CSL_Status status;
	int key_stat = 0;
	//SAR_stopConversion(hSar);	
	SAR_startConversion(hSar);
	while(SAR_getStatus(hSar, &status) != CSL_SAR_DATA_AVAILABLE);
	SAR_readData(hSar, &adc_value);
	adc_value &= 0x3FF;
    if((adc_value < SW1 + 12) && (adc_value > SW1 - 12)) {
    	key_stat = 1;
    	/*if (vol > (Int16)0xFF81) {
    		vol--;
    		SIO_ctrl(hStreamOut, AIC3204_CMD_SET_VOLUME, &vol);
    	}*/
    }
    if((adc_value < SW2 + 12) && (adc_value > SW2 - 12)) {
    	key_stat = 2;
    	/*if (vol < (Int16)0x0030) {
    		vol++;
    		SIO_ctrl(hStreamOut, AIC3204_CMD_SET_VOLUME, &vol);
    	}*/
    }
    if((adc_value < SW12 + 12) && (adc_value > SW12 - 12)) {
    	key_stat = 3;
        adc_value = SW12;
    }
    if((adc_value < NoKey + 12) && (adc_value > NoKey - 12)) {
    	key_stat = 0;
        adc_value = NoKey;
    }
   // SAR_startConversion(hSar);
    return key_stat;
}


