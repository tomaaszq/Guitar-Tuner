#include <csl_dma.h>
#include <csl_intc.h>

extern void interrupt_DMA01(void);
extern void interrupt_DMA02(void);

void isr_DMA(void)
{
	int ifrValue;
	ifrValue = CSL_SYSCTRL_REGS->DMAIFR;
	
	if (ifrValue & 0x0001) {	// *DMACTRL0CHAN0 - Tx mono
		interrupt_DMA01();
	}
	if (ifrValue & 0x0002) {	// *DMACTRL0CHAN1 - Rx mono
		interrupt_DMA02();
	}

	CSL_SYSCTRL_REGS->DMAIFR = ifrValue;
	IRQ_clear(DMA_EVENT);
}
