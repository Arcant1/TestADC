/*
 * dac.c
 *
 */


#include "sAPI.h"

/* P0.26 -> AOUT */
void dacInit(void)
{
	Chip_DAC_Init(LPC_DAC);  //inicializa DAC
#ifdef lpc4337_m4
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
#endif
}


