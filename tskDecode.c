#include <std.h>
#include <stdio.h>
#include <stdlib.h>
#include <tistdtypes.h>
#include <sio.h>
#include <tsk.h>
#include "common.h"
#include <assert.h>

#include "ff.h"
#include <decode.h>
#include <mp3_tni.h>
#include <iso646.h>

#define INPBUF_SZ (1024)	// minimum cluster size is INP_BUFSZ [bytes]

extern char* Tx_fnptr;
extern int Tx_status;
extern int Rx_status;

int DECODE_decode(DECODE_Handle handle, Int * in, Int *out, int inwords, 
                                                  IDECODE_OutArgs* outargs);
void DECODE_getStatus(DECODE_Handle handle, DECODE_Status *status);
void DECODE_reset(DECODE_Handle handle);

extern int handleKeys(void);
extern int DisplayString(char *str);

extern PCM_SAMPLE_TYPE audBufs[NUM_OUT_BUFS][WORDS_PER_OUT_BUF];

Int inBuffer[INPBUF_SZ];
Int* inBuffStart;
//Int outBuffer_tmp[1152];
//Int* outBuffer_ptrtmp;
FIL mp3File;
FILINFO fno;
extern DIR dirObj;
extern SIO_Handle hStreamOut;
Ptr outBuffer;
int numFrames = 0;

void tskDecode()
{
	int addr_is_odd, addr_was_odd;
	UINT br;
	int numUsedWords;
	long framesDecoded;
	IDECODE_Handle handle;
	IDECODE_Params decParams = MP3_PARAMS;

	IDECODE_OutArgs outArgs;
	PCM_SAMPLE_TYPE* pAudBufs;
	int numValidWords;
	int idx;
	
	FRESULT res;
while (1) {		
if ((Tx_status >0)&&(Rx_status ==0)) {
//	YELLOW_ON
	//Tx_status_output = 0;
	decParams.size = sizeof(IDECODE_Params);
	outArgs.size   = sizeof(IDECODE_OutArgs);

	decParams.pcmFormat = IAUDIO_BLOCK;


	/* Create an instance of the algorithm */
	handle = DECODE_create(&MP3_TNI_IMP3, &decParams);
	if (handle == NULL) {
		abort();
	}

		DECODE_reset(handle);
		
		res = f_open(&mp3File, Tx_fnptr, FA_OPEN_EXISTING | FA_READ);
		if (res == FR_OK) {	

		// fill input buffer with mp3 data from sdcard
		// read in two halves to allow smaller cluster sizes
		res = f_read(&mp3File, (BYTE*)inBuffer, INPBUF_SZ/2*2, &br);
		numValidWords = br>>1;
		res = f_read(&mp3File, (BYTE*)(inBuffer+INPBUF_SZ/2), INPBUF_SZ/2*2, &br);
		numValidWords += br>>1;
		if (res != FR_OK) {
			abort();
		}
		
		// clear buffers
		pAudBufs = &audBufs[0][0];
		for (idx=0; idx<NUM_OUT_BUFS*WORDS_PER_OUT_BUF; idx++) {
			*pAudBufs++ = 0;
		}
		// issue buffers
		for (idx=0; idx<NUM_OUT_BUFS; idx++) {									// issue all buffer at once
			SIO_issue(hStreamOut, &audBufs[idx][0], WORDS_PER_OUT_BUF, NULL);	// buffers have to be issued before they can be reclaimed
		}
	
		numUsedWords  = 0;		
		addr_is_odd = 0;	// DMA asks for even 16bit dest base address; make sure this always happens
		framesDecoded = 0;
		while(1) {
			int err;
			int i;
			int halfsamples;

//			PCM_SAMPLE_TYPE* outBuffer_;
//			outBuffer_ = ((PCM_SAMPLE_TYPE*) outBuffer);
			
//			while (not SIO_ready(hStreamOut)){
//				RED_ON
//			}
			
			SIO_reclaim(hStreamOut, &outBuffer, NULL);	// get an empty audio buffer, blocking until buffer a/v

			//BLUE_ON
			err = DECODE_decode(handle, (Int*)&inBuffer[addr_is_odd], (Int*)outBuffer, numValidWords, &outArgs);

			halfsamples=(outArgs.numSamples*outArgs.numChannels/2);
			for(i=0; i<halfsamples; i++) {
			((Int*) outBuffer)[i] = (((Int*) outBuffer)[i])/2+(((Int*) outBuffer)[i+halfsamples])/2;
			((Int*) outBuffer)[i+halfsamples] = 0;
			}
			
			framesDecoded++;
			if (err != 0) {
				;
			}
			//BLUE_OFF
//			if (framesDecoded > 500) {
//				YELLOW_ON }
				
			numValidWords -= outArgs.wordsConsumed;
			numUsedWords  += outArgs.wordsConsumed;

			if (framesDecoded == 1) {
				SIO_ctrl(hStreamOut, AIC3204_CMD_SET_SRATE, &outArgs.sampleRate);	// adjust sampling rate		
				//DisplayString("E3          "); //fno.fname);											// update Display
			}				
			SIO_issue(hStreamOut, outBuffer, outArgs.numSamples*outArgs.numChannels, NULL);

			// copy unsued words to begin of 'inBuffer'
			addr_was_odd = addr_is_odd;
			addr_is_odd = numValidWords & 1;
			memcpy(&inBuffer[addr_is_odd], &inBuffer[addr_was_odd] + outArgs.wordsConsumed, numValidWords);
			
			// refill input buffer if equal or more of 'inBuffer' is free
			if (numUsedWords >= INPBUF_SZ/2) {		
				res = f_read(&mp3File, (BYTE*)(&inBuffer[addr_is_odd]+numValidWords), INPBUF_SZ/2*2, &br);
				numValidWords += (br>>1);
				numUsedWords  -= (br>>1);
			}	
			if (numValidWords < 8) {				
		       	break;
			}
	//		handleKeys();						// check the keys
		}
		for (idx=0; idx<NUM_OUT_BUFS; idx++) {
			SIO_reclaim(hStreamOut, &outBuffer, NULL);		// get all buffers back
		}
	}
	DECODE_delete(handle);
	//YELLOW_ON
	Tx_status=0;
	//Tx_status_output=1;
	
}
TSK_yield();
}
}
