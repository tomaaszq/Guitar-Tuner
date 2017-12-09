#ifndef COMMON_H_
#define COMMON_H_

// always uncomment only one line!
#define DSP_FREQ_KHZ   (40000)		// uncomment for 40MHz CPU clock
//#define DSP_FREQ_KHZ (60000)		// uncomment for 60MHz CPU clock
//#define DSP_FREQ_KHZ (100000)		// uncomment for 100MHz CPU clock

#define OLED9616_I2C_ADDR (0x3C)
#define AIC3204_I2C_ADDR  (0x18)

#define NUM_OUT_BUFS      (3)
#define WORDS_PER_OUT_BUF (1152)
#define PCM_SAMPLE_TYPE Int16
#define FFT_LENGTH (8192)
#define	BUFS_FFT (2)

#define AIC3204_CMD_SET_VOLUME (1)
#define AIC3204_CMD_SET_SRATE  (2)

#define REDLED (0x0001)
#define GRNLED (0x0002)
#define BLULED (0x4000)
#define YELLED (0x8000)

#define RED_ON *(ioport volatile unsigned *)0x1C0B &= ~REDLED;
#define RED_OFF *(ioport volatile unsigned *)0x1C0B |= REDLED;
#define GREEN_ON *(ioport volatile unsigned *)0x1C0B &= ~GRNLED;
#define GREEN_OFF *(ioport volatile unsigned *)0x1C0B |= GRNLED;
#define BLUE_ON *(ioport volatile unsigned *)0x1C0A &= ~BLULED;
#define BLUE_OFF *(ioport volatile unsigned *)0x1C0A |= BLULED;
#define YELLOW_ON *(ioport volatile unsigned *)0x1C0A &= ~YELLED;
#define YELLOW_OFF *(ioport volatile unsigned *)0x1C0A |= YELLED;

#define FFT_FLAG ( 0 ) /* HWAFFT to perform FFT */
#define IFFT_FLAG ( 1 ) /* HWAFFT to perform IFFT */
#define SCALE_FLAG ( 0 ) /* HWAFFT to scale butterfly output */
#define NOSCALE_FLAG ( 1 ) /* HWAFFT not to scale butterfly output */
#define OUT_SEL_DATA ( 0 ) /* Indicates HWAFFT output located in input data vector */
#define OUT_SEL_SCRATCH ( 1 ) /* Indicates HWAFFT output located in scratch vector */

#endif /*COMMON_H_*/
