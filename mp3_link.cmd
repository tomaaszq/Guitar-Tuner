
SECTIONS
{   
    
    MP3_TNI_MAD_TEXT    > SARAM
    MP3_TNI_MAD_CONST   > DARAM
        
    MP3_TNI_DCT_TEXT    > SARAM
    MP3_TNI_DCT_CONST   > DARAM
    
    MP3_TNI_MDCT_TEXT   > SARAM
    MP3_TNI_MDCT_CONST  > DARAM
     
    MP3_TNI_HUFF_TEXT	> SARAM
    MP3_TNI_HUFF_CONST	> DARAM
        
   .MP3text  
       {
       -lmp3_tni_rev3.l55l(.text)
       }                        > SARAM
   
   .MP3const  
       {
       -lmp3_tni_rev3.l55l(.const)
    }                           > DARAM
    
    scratch_section:	 > DARAM2
    data_section:		 > DARAM2

    samples_section:	 > SARAM 
	twiddle_section: 	 > SARAM
	hann_section:		 > SARAM
	twiddleR_section:	 > SARAM
	twiddleI_section:	 > SARAM
	tmp_section:		 > SARAM
}

/* HWAFFT Routines ROM Addresses */
/* (PG 2.0) */
_hwafft_br = 0x00ff6cd6;
_hwafft_1024pts = 0x00ff7a56;