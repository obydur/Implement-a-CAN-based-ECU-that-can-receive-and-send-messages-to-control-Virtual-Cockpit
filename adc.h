/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-1
 *	File Name		: adc.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef ADC_H_
#define ADC_H_

/* Includes ******************************************************************/
#include "adc_lld_cfg.h"

/* Function prototypes *******************************************************/
void ADC0_Init(void);
void ADC1_Init(void);
void ADC0_StartConversion(void);
void ADC1_StartConversion(void);

#endif /* ADC_H_ */
