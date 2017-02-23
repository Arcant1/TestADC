/*
 * adc.c
 *
 */

#include "sAPI.h"
#include "fir_q31.h"
#include "main.h"

extern fir_q31_t filtro1; //se trae las variables de filtro de fir31
extern fir_q31_t filtro2;
extern fir_q31_t filtro3;
extern fir_q31_t filtro4;
extern fir_q31_t filtro5;
extern fir_q31_t filtro6;
extern fir_q31_t filtro7;
extern fir_q31_t filtro8;



int adcFlag=0;



/* P0.23 -> AD0 */
void adcInit(void)  	  //inicializacion adc 
{
	ADC_CLOCK_SETUP_T adc;  

	Chip_ADC_Init(LPC_ADC0, &adc);		// se carga incializa el adc a frecuencia de muestro de 48000
	Chip_ADC_SetSampleRate(LPC_ADC0, &adc, 22000);

	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);   // habilita canal 1 del adc
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE); //ACA setea la interrupción
	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);

	NVIC_EnableIRQ(ADC0_IRQn);			// habilita interrupcion
}


void ADC0_IRQHandler(void)
{
	static uint16_t data;
	static uint32_t cont;

	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, &data);  //lee valor del adc y lo guarda en data



	cont++;
	if (cont == 4) {
		cont = 0;
		fir_q31_put(&filtro1, data);  // carga valor del filtro con el del leido en el adc
		fir_q31_put(&filtro2, data);
		fir_q31_put(&filtro3, data);
		fir_q31_put(&filtro4, data);
		fir_q31_put(&filtro5, data);  // carga valor del filtro con el del leido en el adc
		fir_q31_put(&filtro6, data);
		fir_q31_put(&filtro7, data);
		fir_q31_put(&filtro8, data);


	}

	adcFlag=1;
}
