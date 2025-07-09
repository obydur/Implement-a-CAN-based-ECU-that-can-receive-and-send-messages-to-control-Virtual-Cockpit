/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-1
 *	File Name		: adc.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "adc.h"


/* Global variables **********************************************************/
static adcsample_t samplesPot[ADC0_GROUP_ADC0_CH5_POT_NUM_CHANNELS * \
							  ADC0_GROUP_ADC0_CH5_POT_BUF_DEPTH];
static adcsample_t samplesLdr[ADC1_GROUP_ADC1_CH3_LDR_NUM_CHANNELS * \
							  ADC1_GROUP_ADC1_CH3_LDR_BUF_DEPTH];

/*
 * @brief	ADC0 initialization function
 *
 * @param	void
 * @retval	void
 */
void ADC0_Init(void){
	adc_lld_start(&ADCD1, NULL);
}


/*
 * @brief	ADC1 initialization function
 *
 * @param	void
 * @retval	void
 */
void ADC1_Init(void){
	adc_lld_start(&ADCD2, NULL);
}


/*
 * @brief	ADC0 conversion start function
 *
 * @param	void
 * @retval	void
 */
void ADC0_StartConversion(void){
	adc_lld_start_conversion(&ADCD1, &adc0_group_ADC0_CH5_POT, samplesPot,
			ADC0_GROUP_ADC0_CH5_POT_BUF_DEPTH);
}


/*
 * @brief	ADC1 conversion start function
 *
 * @param	void
 * @retval	void
 */
void ADC1_StartConversion(void){
	adc_lld_start_conversion(&ADCD2, &adc1_group_ADC1_CH3_LDR, samplesLdr,
			ADC1_GROUP_ADC1_CH3_LDR_BUF_DEPTH);
}
