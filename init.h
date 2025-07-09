/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: init.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef INIT_H_
#define INIT_H_

/* Includes ******************************************************************/
#include "components.h"
#include "siu.h"
#include "pit.h"
#include "adc.h"
#include "can.h"

/* Function prototypes *******************************************************/
void peripheralsInit(void);
void systemFunction(void);

#define	__HW_CAN_FILTER(x)	((x & CAN_MASK_REGISTER) == (CAN_ACCEPTANCE_REGISTER & CAN_MASK_REGISTER))

#endif /* INIT_H_ */
