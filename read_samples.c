#include <std.h>
#include <stdio.h>
#include <stdlib.h>
#include <tistdtypes.h>
#include <sio.h>
#include <tsk.h>
#include "common.h"
#include "hann.h"

// Define subtract_flag of CPLX_Add() Function
#define ADD 		0
#define SUBTRACT 	1

extern Int16 RcvL[BUFS_FFT][FFT_LENGTH];
extern int Tx_status;
extern int Rx_status;
Int16* Rcv;
int idx;
size_t ih;
int tmp_loop;
extern SIO_Handle hStreamIn;
Ptr inBufferRcv;

extern Int32 data_buf[FFT_LENGTH];
extern Int32 scratch_buf[FFT_LENGTH];
extern Int32 twiddle[FFT_LENGTH/2];
extern Int16 hann[4096];
extern Int16 tmpx[FFT_LENGTH/2];

// Function Prototypes:
Int32 CPLX_Mul(Int32 op1, Int32 op2);
Int32 CPLX_Add(Int32 op1, Int32 op2, Uint16 subtract_flag);
void Radix2FFT(Int32 *In, Int32 *Out, Int32 *Twiddle, Uint16 Len, Uint16 twidStepSize);
Int16 CPLX_Mod(Int32 op1);

Int32 re_hann;
Int16 re_hann16;
Int32* data_buf_ptr;
Int16* tmpx_ptr;

Int32 *data;
Int32 *data_br;
Uint16 fft_flag;
Uint16 scale_flag;
Int32 *twiddle_ptr;
Uint16 out_sel;
Int32 *result;
int num_sampl;
Int16 paczka[64];
int ile_paczek;
Int16 w_paczce;
Int16 poczatek_paczki;
Int32 suma_wazona;
Int32 suma_prazkow;
Int16 max_prazek;
Int32 chwilowy_prazek;
Int32 amplituda_harmonicznej[64];
Int32 max1,max2,max3;
Int16 n_max1,n_max2,n_max3;
Int16 S_max;
Int16 prazki_podstawowe[6];
Int16 tmpa,tmpb,tmpc;
Int16 znak[6];
Int16 krotnosc[6];
//Int16 roznica1,roznica2;

void read_aic3204()
{
while(1) {	
if ((Rx_status == 1)&&(Tx_status ==0)) {
	
		// clear buffers
		Rcv = &RcvL[0][0];
		for (idx=0; idx<BUFS_FFT*FFT_LENGTH; idx++) {
			*Rcv++ = 0;
		}
		// issue buffers
		for (idx=0; idx<BUFS_FFT; idx++) {									// issue all buffer at once
			SIO_issue(hStreamIn, &RcvL[idx][0], FFT_LENGTH, NULL);	// buffers have to be issued before they can be reclaimed
		}
num_sampl = 0;
while(1) {
	if ((Tx_status == 0)&&(Rx_status == 1)) {
			
	SIO_reclaim(hStreamIn, &inBufferRcv, NULL);	// get an full audio buffer, blocking until buffer a/v

	tmp_loop = FFT_LENGTH/2;	
		//hann window in time domain
		data_buf_ptr = &data_buf[0];
		tmpx_ptr = &tmpx[0];
		for(ih=0;ih<tmp_loop;++ih) {
			re_hann= (Int32)((Int16*)inBufferRcv)[ih]*hann[ih];
			re_hann16 = (Int16)(re_hann >> 15);
			*data_buf_ptr++ =(((Int32)re_hann16 & 0x0000FFFF)<< 16);
			//*tmpx_ptr++ = re_hann16;
		}
		for(ih=0;ih<tmp_loop;++ih) {
			re_hann= (Int32)((Int16*)inBufferRcv)[tmp_loop+ih]*hann[(tmp_loop-1) - ih];
			re_hann16 = (Int16)(re_hann >> 15);
			*data_buf_ptr++ =(((Int32)re_hann16 & 0x0000FFFF)<< 16);
			//*tmpx_ptr++ = re_hann16;
		}
		//puts("readsamples_wew");
		// Bit-reverse input data for in-place DIT FFT calculation				
		data_br=scratch_buf;		
		data = data_buf;
		hwafft_br(data, data_br, FFT_LENGTH); 
		// 1024-pt FFT on the FFT Hardware Accelerator
		fft_flag = FFT_FLAG;
		scale_flag = SCALE_FLAG;
		
		for(ih=0;ih<8;ih++) {
			data = &scratch_buf[ih*FFT_LENGTH/8];
			data_br = &data_buf[ih*FFT_LENGTH/8];
			out_sel = hwafft_1024pts(data,data_br,fft_flag,scale_flag);
		}
		twiddle_ptr = & twiddle[0];
		
		for(ih=0;ih<4;ih++) {
			data = &data_buf[ih*FFT_LENGTH/4];
			data_br = &scratch_buf[ih*FFT_LENGTH/4];
			Radix2FFT(data, data_br, twiddle_ptr, 1024, 4);
		}
		for(ih=0;ih<2;ih++) {
			data = &scratch_buf[ih*FFT_LENGTH/2];
			data_br = &data_buf[ih*FFT_LENGTH/2];
			Radix2FFT(data, data_br, twiddle_ptr, 2048, 2);
		}
		data = &data_buf[0];
		data_br = &scratch_buf[0];
		Radix2FFT(data, data_br, twiddle_ptr, 4096, 1);
		
		for(ih=0;ih<tmp_loop;++ih) {
		tmpx[ih] = 	CPLX_Mod(scratch_buf[ih]);
		}
		ile_paczek = 0;
		w_paczce = 0;
		suma_wazona = 0;
		suma_prazkow = 0;
		
		for(ih=0;ih<tmp_loop;++ih) {	
				
		if (tmpx[ih] >0) {
			if (w_paczce == 0)	{
				poczatek_paczki = ih;
				}
			w_paczce++;
			suma_wazona =  suma_wazona+(Int32)tmpx[ih]*w_paczce;
			suma_prazkow = suma_prazkow + tmpx[ih];
		} else {
			if (w_paczce > 0){
				max_prazek=0;
				chwilowy_prazek=suma_prazkow;
				while(suma_wazona-chwilowy_prazek>=0) {
					max_prazek++;
					chwilowy_prazek=chwilowy_prazek+suma_prazkow;	
				}
				
				paczka[ile_paczek]=poczatek_paczki+max_prazek-1;
				amplituda_harmonicznej[ile_paczek]=suma_prazkow;
				ile_paczek++;
				if(ile_paczek>63){
					ile_paczek = 63;
				}
				w_paczce = 0;
				suma_wazona = 0;
				suma_prazkow = 0;				
			}
		}
		
		}
		if(ile_paczek==0) {
		 	S_max=0;
		}
		else if(ile_paczek==1) {
			S_max=paczka[0];
		}
		else if(ile_paczek==2) {
			if(paczka[1]>paczka[0])
				S_max=paczka[1]-paczka[0];
			else
				S_max=paczka[0]-paczka[1];
		}
		else {
			max1=amplituda_harmonicznej[0];
			n_max1=0;
			for(ih=0;ih<ile_paczek;ih++) {
					if(max1<amplituda_harmonicznej[ih]) {
						max1=amplituda_harmonicznej[ih];
						n_max1=ih;
					}
			}
			amplituda_harmonicznej[n_max1]=0;
			max2=amplituda_harmonicznej[0];
			n_max2=0;
			for(ih=0;ih<ile_paczek;ih++) {
					if(max2<amplituda_harmonicznej[ih]) {
						max2=amplituda_harmonicznej[ih];
						n_max2=ih;
					}
			}
			amplituda_harmonicznej[n_max2]=0;
			max3=amplituda_harmonicznej[0];
			n_max3=0;
			for(ih=0;ih<ile_paczek;ih++) {
					if(max3<amplituda_harmonicznej[ih]) {
						max3=amplituda_harmonicznej[ih];
						n_max3=ih;
					}
			}
		}
		//paczka[n_max1]+paczka[n_max2]+paczka[n_max3];
		
		if(paczka[n_max1]>paczka[n_max2])
			S_max=paczka[n_max1]-paczka[n_max2];
		else
			S_max=paczka[n_max2]-paczka[n_max1];
		
		prazki_podstawowe[0]=76;
		prazki_podstawowe[1]=102; 
		prazki_podstawowe[2]=137;
		prazki_podstawowe[3]=182;
		prazki_podstawowe[4]=229;
		prazki_podstawowe[5]=307;
		
		
		for(ih=0;ih<6;ih++) {
			tmpa=1;
			while(prazki_podstawowe[ih]*tmpa<S_max) {
			
				tmpa++;
				
			}
														 //S_max - dzwiek znaleziony - ten ktory gramy
			tmpb=S_max-(prazki_podstawowe[ih]*(tmpa-1)); //prazek referencyjny powyzej dzwieku ktory gramy
			tmpc=(prazki_podstawowe[ih]*tmpa)-S_max; 	 //prazek referencyjny ponizej dzwieku ktory gramy
			if(tmpb<tmpc) { 							 // teraz prazki_podstawowe nie ma zwiazku juz z tym co wczesniej
				prazki_podstawowe[ih]=tmpb;
				znak[ih]=1; 							 // 0 to minus, 
			}
			else {
				prazki_podstawowe[ih]=tmpc;
				znak[ih]=0; 							 // 0 to minus, 1 to plus	
			}
			krotnosc[ih]=tmpa;
		}
		//n_max to teraz bedzie minimum
		tmpa=prazki_podstawowe[0]*krotnosc[0];
		tmpb=0; //to teraz jest nr elementu tablicy prazki_podstawowe
		for(ih=0;ih<6;ih++) {
			if(prazki_podstawowe[ih]*krotnosc[ih]<tmpa) {
				tmpa=prazki_podstawowe[ih]*krotnosc[ih];	
				tmpb=ih;
			}	
		}
		if(tmpb==0 && S_max>0)
			DisplayString("     E6     ");
		else if(tmpb==1)
			DisplayString("     A5     ");
		else if(tmpb==2)
			DisplayString("     D4     ");
		else if(tmpb==3)
			DisplayString("     G3     ");
		else if(tmpb==4)
			DisplayString("     H2     ");
		else if(tmpb==5)
			DisplayString("     E1     ");
			
		if(S_max<1) {
			DisplayString("   ZAGRAJ   ");
			RED_OFF
			BLUE_OFF
			GREEN_OFF
			YELLOW_OFF
		}
			
			
		if(tmpa>1) {
			if(znak[tmpb]==0) {		// dzwiek ktory gramy jest za niski w porownaniu do referencyjnego
				BLUE_OFF;
				YELLOW_OFF;
				RED_ON;
			}
			else {					// dzwiek ktory gramy jest za wysoki w porownaniu do referencyjnego
				BLUE_ON;
				YELLOW_OFF;
				RED_OFF	
			}
		}
		else {						// dzwiek ktory gramy jest w granicy tolerancji +/- 1,077Hz
			if(S_max>1) {
				BLUE_OFF;
				YELLOW_ON;
				RED_OFF;	
			}	
		}
		
				
		num_sampl++ ;
		if (num_sampl > 2){
		//BLUE_ON
		}
	SIO_issue(hStreamIn, inBufferRcv, FFT_LENGTH, NULL);

	
	} else {//if if Rx=1 i Tx =0
	break;
		}
	//puts("readsamples_zewnatrz");

			} // while
		// reclaim buffers
		for (idx=0; idx<BUFS_FFT; idx++) {					
			SIO_reclaim(hStreamIn, &inBufferRcv, NULL);	
		}
		Rx_status = 0;					
		} // if Rx=1 i Tx =0
		TSK_yield();
	} //while
}

/************************************************************************************************* 
 * cplx_prod = CPLX_Mul(op1, op2):
 * Computes complex multiplication
 * Re{cplx_prod} = Re{op1}*Re{op2} - Im{op1}*Im{op2}
 * Im(cplx_prod) = Re{op1}*Im{op2} + Im{op1}*Re{op2}
 * cplx_prod = Re{cplx_prod},Im(cplx_prod) stored in one double word [16-bit Re, 16-bit Im]
 *************************************************************************************************/
Int32 CPLX_Mul(Int32 op1, Int32 op2)
{
	Int16 op1_r, op1_i, op2_r, op2_i;
	Int32 op1_op2_r, op1_op2_i;
	Int16 op1_op2_r16, op1_op2_i16;
	Int32 cplx_prod;

	// Mask data for real and imag data = (real:imag)
	op1_r = op1 >> 16;
	op1_i = op1 & 0x0000FFFF;
	op2_r = op2 >> 16;
	op2_i = op2 & 0x0000FFFF;

	op1_op2_i	= (Int32)op1_r*op2_i + (Int32)op1_i*op2_r;
	op1_op2_r	= (Int32)op1_r*op2_r - (Int32)op1_i*op2_i;
	
	op1_op2_i16 = (Int16)(op1_op2_i >> 15);
	op1_op2_r16 = (Int16)(op1_op2_r >> 15);

	cplx_prod = (((Int32)op1_op2_r16 & 0x0000FFFF)<< 16);
	cplx_prod = cplx_prod | ((Int32)op1_op2_i16 & 0x0000FFFF);

	return cplx_prod;
}

/*************************************************************************************************
 * cplx_sum = CPLX_Add(op1, op2, subtract_flag):
 * Computes complex addition/subtraction with divide by 2 scaling afterwards 
 * Re{cplx_sum} = Re{op1} +- Re{op2}
 * Im(cplx_sum) = Im{op1} +- Im{op2}
 * cplx_sum = Re{cplx_sum},Im(cplx_sum) stored in one double word [16-bit Re, 16-bit Im]
 * subtract_flag = 0: ADD, subtract_flag = 1: SUBTRACT
 *************************************************************************************************/
Int32 CPLX_Add(Int32 op1, Int32 op2, Uint16 subtract_flag)	
{
	Int16 op1_r, op1_i, op2_r, op2_i;
	Int32 op1_op2_r32, op1_op2_i32;
	Int16 op1_op2_r16, op1_op2_i16;
	Int32 cplx_sum;
	
	// Mask/shift data to extract Re and Im data = [Re,Im]
	op1_r = op1 >> 16;
	op1_i = op1 & 0x0000FFFF;
	op2_r = op2 >> 16;
	op2_i = op2 & 0x0000FFFF;

	// If subtract_flag, Subtract op2 from op1 by negating op2 and adding it to op1
	if(subtract_flag == 1)
	{
		op2_r = -1*op2_r;
		op2_i = -1*op2_i;		
	}
	
	// Perform addition and scale the sum by 1/2
	op1_op2_r32 = ((Int32)op1_r + op2_r)>>1;		
	op1_op2_i32 = ((Int32)op1_i + op2_i)>>1;		
	
	// Repack Re and Im results into one double word
	op1_op2_r16 = (Int16)(op1_op2_r32 & 0x0000FFFF);
	op1_op2_i16 = (Int16)(op1_op2_i32 & 0x0000FFFF);
	
	cplx_sum = (((Int32)op1_op2_r16 & 0x0000FFFF)<< 16);
	cplx_sum = cplx_sum | ((Int32)op1_op2_i16 & 0x0000FFFF);
	
	return cplx_sum;
}

	// twidStepSize = 4 dla kroku 11, 2 dla 12 i 1 dla 13,
	// Len: krok 11 = 1024, 12 = 2048, 13 = 4096

void Radix2FFT(Int32 *In, Int32 *Out, Int32 *Twiddle, Uint16 Len, Uint16 twidStepSize)
{
	Int32 twiddle_data_odd;
	Uint16 k = 0;

	for(k=0; k<Len; k++)
	{
		// X(k) 	= 1/2*(X_even[k] + Twiddle[k]*X_odd(k))
		// X(k+N/2) = 1/2*(X_even[k] - Twiddle[k]*X_odd(k))
		
		// Twiddle[k]*X_odd(k):
		twiddle_data_odd = CPLX_Mul(Twiddle[k * twidStepSize], In[k + Len]); 
		
		// X(k):
		Out[k] = CPLX_Add(In[k], twiddle_data_odd, ADD);
		
		// X(k+N/2):
		Out[k+Len] = CPLX_Add(In[k], twiddle_data_odd, SUBTRACT);
	}
}
 
Int16 CPLX_Mod(Int32 op1)
{
	Int16 op1_r, op1_i;
	Int32 op1_op;
	Int16 op1_16;

	// Mask data for real and imag data = (real:imag)
	op1_r = op1 >> 16;
	op1_i = op1 & 0x0000FFFF;

	op1_op	= (Int32)op1_r*op1_r + (Int32)op1_i*op1_i;	
	op1_16 = (Int16)(op1_op >> 15);

	return op1_16;
}
