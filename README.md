# Guitar Tuner on DSP
Guitar tuner built with TMS320C5515 - my Engineer's Thesis at Wroclaw University of Science and Technology.

## Description
Engineer's Thesis was based on Guitar Tuner project built with TMS320C5515. 
To build the device I had to get knowledge about topics like Digital signal processing or programming DSP under BIOS control. 
Project was finished, and all assumptions was achieved. 
Guitar Tuner was extend of hearing trimming option, so that user can improve his hearing skills.
Program is based on MP3Dec free mp3 player program taken from: 
  L. Lotzenburger, „MP3 One-Two-Three,” Elektor Magazine, p. 30, March 2011. Online: https://www.elektor.com/march-2011-edition-pdf-download

Tuner has two options - automatic tuning based on FFT algorithm, and hearing tuning where you can play recorded strings and saved on microSD card in mp3 format.

## Most important components and hardware elements:
* Spectrum Digital TMS320C5515
* AIC3204 - analog/digital converter
* C5515 processor
* OLED Display
* Bios v5.42 - Texas Instruments
* TSK Module - tasking
* Chip Support Library (CSL) 
* DMA - Direct Memory Access
* I2S, I2C interfaces
* Interrupts
* MP3Dec - mp3 player free software
* User Interface - voice interface (output) and two buttons (input)
* FFT Algorithm
* Analog input route - microphone amplifier built with two OPA350 
* Analog output route - simple bluetooth speaker Creative MUVO Mini
