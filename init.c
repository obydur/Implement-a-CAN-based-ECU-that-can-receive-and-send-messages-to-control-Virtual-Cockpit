/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: init.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef INIT_C_
#define INIT_C_

/* Includes ******************************************************************/
#include "init.h"


/* Global variables **********************************************************/
uint32_t systemBlink = 0;

/*
 * @brief	MCU peripherals initialization function
 *
 * @param	void
 * @retval	void
 */
void peripheralsInit(void){
	/* board components initialization */
	componentsInit();

	/* enable IRQs */
	irqIsrEnable();

	/* peripherals initialization */
	SIU_Init();
	PIT_Init();
	ADC0_Init();
	ADC1_Init();
	CAN_Init();
}


/*
 * @brief	System internal function calls and blink
 *
 * @param	void
 * @retval	void
 */
void systemFunction(void){
	ADC0_StartConversion();
	ADC1_StartConversion();

	if(systemBlink < 24){
		systemBlink++;
	}
	else{
		SIU.GPDO[45].R = ~SIU.GPDO[45].R;
		systemBlink = 0;
	}
}

#endif /* INIT_C_ */
