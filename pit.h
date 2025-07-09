/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: pit.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef PIT_H_
#define PIT_H_

/* Includes ******************************************************************/
#include "pit_lld.h"
#include "pit_lld_cfg.h"

/* Function prototypes *******************************************************/
void PIT_Init(void);
void PIT_ConfigureTimer(uint8_t timerChannel, uint32_t timerFrequency);
void PIT_StartTimer(uint8_t timerChannel);
void PIT_StopTimer(uint8_t timerChannel);

#endif /* PIT_H_ */
