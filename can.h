/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.h
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

#ifndef CAN_H_
#define CAN_H_

/* Includes ******************************************************************/
#include "init.h"
#include "can_lld.h"
#include "can_lld_cfg.h"


/* TO-DO: your task implementations ******************************************/

/* Macro definitions *********************************************************/
#define	CAN_MASK_REGISTER			0x000
#define	CAN_ACCEPTANCE_REGISTER		0x7FF


/*****************************************************************************/


/* Function prototypes *******************************************************/
void CAN_Init(void);
void cfg0_Fifo_RX(CANDriver *canp, CANRxFrame crfp);
void can_receive(CANRxFrame crfp);

#endif /* CAN_H_ */
