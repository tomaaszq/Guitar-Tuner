	#include <std.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <tistdtypes.h>
	#include <sio.h>
	#include <tsk.h>
	#include <string.h>
	#include "ff.h"
	#include "common.h"
	
	extern int handleKeys(void);
	extern DIR dirObj;
	extern char* Tx_fnptr;
	extern int Tx_status;
	extern int Rx_status;
	extern SIO_Handle hStreamOut;
	extern SIO_Handle hStreamIn;
	FRESULT resc;
	FILINFO fnoc;
	
	TCHAR zapowiedz_glowna[13]="ZG2.mp3";
	TCHAR wybrana_struna[13]="wstr4.mp3";
	TCHAR aby_zagrac[13]="odt4.mp3";
	TCHAR automatyczny_stroik[13]="Auto4.mp3";
	TCHAR struny_text[6][13] = {"TextE14.mp3","TextH24.mp3","TextG34.mp3","TextD44.mp3","TextA54.mp3","TextE64.mp3"};
	TCHAR struny[6][13] = {"E1_24.mp3","H2_24.mp3","G3_24.mp3","D4_24.mp3","A5_24.mp3","E6_24.mp3"};
	TCHAR nazwy_strun[6][12] = {"     E1     ","     H2     ","     G3     ","     D4     ","     A5     ","     E6     "};
	int step=0;
	int pojedyncze_odt = 0;
	int struna = 0;
	static Int16 vol = 0x0000;
	int getKey();
	
	void menu_ctrl()
	{
	int tt;
	while (1) {
	if (Tx_status == 0){
	
		//resc = f_readdir(&dirObj, &fnoc);
			//if (resc == FR_OK) {
			
			if(step==0) {
				strcpy(Tx_fnptr, zapowiedz_glowna);
				Tx_status = 1;
				DisplayString("ZAPOWIEDZ GL");
				TSK_yield();
			}
			
			if(pojedyncze_odt==0) {
				tt = getKey();
					if (tt==1 && step==0) {
						step=1;
					}
					else if((tt==1 && step==2)||(tt==1 && step==3)) {
						strcpy(Tx_fnptr, struny[struna]);
						Tx_status = 1;
						step=3;
						DisplayString(nazwy_strun[struna]);
						TSK_yield();
					}
					else if((tt==2 && step==2)||(tt==2 && step==3)) {
						if(struna>4) {
							struna=0;	
						}
						else {
							struna++;	
						}
						
						step=1;
					}
					else if (tt==2) {
						//prawa strona
						Rx_status = 1;
						step = 9;
						// I2S na 8820
						vol=0x0010;
						SIO_ctrl(hStreamOut, AIC3204_CMD_SET_VOLUME, &vol);						
						GREEN_OFF
						BLUE_OFF
						RED_OFF
						YELLOW_OFF	
					}
					else if (tt==3) {
						if (step == 9) {
						Rx_status = 2;
						// I2S na 44100
						vol=0x0000;
						SIO_ctrl(hStreamOut, AIC3204_CMD_SET_VOLUME, &vol);	
						while (Rx_status>0){					
						TSK_yield();
						}
						step=0;
						struna=0;
						pojedyncze_odt=0;						
						} else {
						step=0;
						struna=0;
						pojedyncze_odt=0;
						TSK_yield();
						//wroc do zapowiedzi glownej
						}	
					}
			}
			
			
			
			if(step==1) {
				pojedyncze_odt++;
				switch (pojedyncze_odt){
				case 1:
				strcpy(Tx_fnptr, wybrana_struna);
				DisplayString("   STRUNA   ");
				Tx_status = 1;
				break;
				case 2:
				strcpy(Tx_fnptr, struny_text[struna]);
				DisplayString(nazwy_strun[struna]);
				Tx_status = 1;
				break;
				case 3:
				strcpy(Tx_fnptr, aby_zagrac);
				DisplayString("1-ODT NAST-2");
				Tx_status = 1;
				break;
				case 4:
				pojedyncze_odt = 0;
				step=2;
				break;
				}
			TSK_yield();	
			}
				//tmp++;
				
			//}
	}
	TSK_yield();
	}
	}
	
	int getKey()
	{
	int hk,gk;
	int licznik = 0;
	hk = handleKeys();
		while (handleKeys()== 0) {
		TSK_yield();	
		}
	gk = handleKeys();
		while (handleKeys()== gk) {
			licznik++;
			if (licznik > 20000){
				while(handleKeys()==gk) {
					TSK_yield();	
				}
				gk = 3;
				break;
			}
			TSK_yield();	
		}	
		return 	gk;
	}
