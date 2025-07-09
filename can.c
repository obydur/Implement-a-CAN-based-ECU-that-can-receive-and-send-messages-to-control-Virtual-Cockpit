/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "can.h"

/*
 * @brief	CAN0 initialization function
 *
 * @param	void
 * @retval	void
 */
void CAN_Init(void){
	/* DO NOT TOUCH HERE! ****************************************************/
	can_lld_start(&CAND1, &can_config_cfg0);
	CAN_0.RXGMASK.R = CAN_MASK_REGISTER;
	/*************************************************************************/


	/* TO-DO: your task implementations **************************************/


	// EngineOn buffer (extended)
	CAN_0.BUF[8].MSG_CS.B.IDE = 1;       // IDE = 1 → Extended ID
	CAN_0.BUF[8].MSG_ID.B.STD_ID = 0;      // Not used in extended mode
	CAN_0.BUF[8].MSG_ID.B.EXT_ID = 0xDA0;  // 29-bit ID
	CAN_0.BUF[8].MSG_CS.B.RTR = 0;       // Data frame (not a remote request)
	CAN_0.BUF[8].CS.B.LENGTH = 1;    // Sending 1 byte of data (example)

	// Speed message (standard)
	CAN_0.BUF[9].MSG_CS.B.IDE = 0;
	CAN_0.BUF[9].MSG_ID.B.STD_ID = 0x5A0;
	CAN_0.BUF[9].MSG_CS.B.RTR = 0;
	CAN_0.BUF[9].CS.B.LENGTH = 1;
	CAN_0.BUF[9].CS.B.CODE = 0x8;

	// RPM message (standard)
	CAN_0.BUF[10].MSG_CS.B.IDE = 0;
	CAN_0.BUF[10].MSG_ID.B.STD_ID = 0x280;
	CAN_0.BUF[10].MSG_CS.B.RTR = 0;
	CAN_0.BUF[10].CS.B.LENGTH = 2;
	CAN_0.BUF[10].CS.B.CODE = 0x8;

	// Lights message (standard)
	CAN_0.BUF[11].MSG_CS.B.IDE = 0;
	CAN_0.BUF[11].MSG_ID.B.STD_ID = 0x470;
	CAN_0.BUF[11].MSG_CS.B.RTR = 0;
	CAN_0.BUF[11].CS.B.LENGTH = 1;
	CAN_0.BUF[11].CS.B.CODE = 0x8;
	/*************************************************************************/

	/*************************************************************************/
}


/*
 * @brief	CAN Fifo Receive Callback
 *
 * @param	CANDriver	*canp	CAN peripheral pointer
 * @param	CANRxFrame	crfp	CAN receive frame buffer
 * @retval	void
 */
void cfg0_Fifo_RX(CANDriver *canp, CANRxFrame crfp){
	if(	(canp == &CAND1) && (crfp.IDE == CAN_IDE_STD) &&
			__HW_CAN_FILTER(crfp.SID)){
		can_receive(crfp);
	}
}
