/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"


/* Global variables **********************************************************/
typedef enum { IDLE, ENGINE_ON } ECU_State;
ECU_State state = IDLE;
bool blink=1 ;

/* Helper Functions **********************************************************/
void LED_Rx_Toggle(void) {
    SIU.GPDO[PCR_LED_Rx].R = 1;  // Toggle LED Rx
}

void LED_Tx_Toggle(void) {
    SIU.GPDO[PCR_LED_Tx].R = 1;  // Toggle LED Tx
}

void LED_U1_Toggle(void) {
    SIU.GPDO[PCR_LED_U1].R = 1;  // Toggle left indicator
}

void LED_U3_Toggle(void) {
    SIU.GPDO[PCR_LED_U3].R = 1;  // Toggle right indicator
}

void LED_P_Set(void) {
    SIU.GPDO[PCR_LED_P].R = 1;
}

void LED_P_Clear(void) {
    SIU.GPDO[PCR_LED_P].R = 0;
}


void can_send_engine_on(void){
    uint8_t engine = 0x01;
	/* TO-DO: your task implementations **************************************/
	CAN_0.BUF[8].DATA.B[0] = engine;
	CAN_0.BUF[8].CS.B.CODE = 0xC;
	LED_Tx_Toggle();

	/*************************************************************************/
}

void can_send_speed(void){
	/* TO-DO: your task implementations **************************************/

	uint16_t pot = POT;
	uint16_t speed = (pot * 240) / 4095;
	CAN_0.BUF[9].DATA.B[0] = speed;
	CAN_0.BUF[9].CS.B.CODE = 0xC;

}

void can_send_rpm(void){
	/* TO-DO: your task implementations **************************************/
	static int rpm = 8000;
	static int rpm_dir = -250;
	rpm += rpm_dir;
	if (rpm <= 0 || rpm >= 8000) rpm_dir = -rpm_dir;

	CAN_0.BUF[10].DATA.B[0] = rpm & 0xFF;         // Low byte
	CAN_0.BUF[10].DATA.B[1] = (rpm >> 8) & 0xFF;   // High byte
	CAN_0.BUF[10].CS.B.CODE = 0xC;


}

void can_send_lights(void){
	/* TO-DO: your task implementations **************************************/
	uint8_t sw1 = SIU.GPDI[PCR_SW1].R;
	uint8_t sw2 = SIU.GPDI[PCR_SW2].R;

	uint8_t lights = 0x00;
	if(blink){
	if (!sw1 && sw2) {
		lights = 0x01;
		SIU.GPDO[PCR_LED_U1].R = 1;
	} else if (sw1 && !sw2) {
		lights = 0x02;
		SIU.GPDO[PCR_LED_U3].R = 1;
	} else if (sw1 && sw2) {
		lights = 0x03;
		SIU.GPDO[PCR_LED_U1].R = 1;
		SIU.GPDO[PCR_LED_U3].R = 1;
	}}else{
		SIU.GPDO[PCR_LED_U1].R = 0;
		SIU.GPDO[PCR_LED_U3].R = 0;
	}

	CAN_0.BUF[11].DATA.B[0] = lights;
	CAN_0.BUF[11].CS.B.CODE = 0xC;

	// LED_Tx_Toggle(); // Feedback that we're transmitting

	// LED_U3 =! LED_U3;
}

void can_send(void){
	//
}


/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization */
	peripheralsInit();


	/* TO-DO: your task implementations **************************************/

	/* Configure and start timer channels */
	/* PIT timer channel 1, period = 1000 ms 1*/
    PIT_ConfigureTimer(1, 100);
    PIT_ConfigureTimer(2, 1000);
	//PIT_ConfigureTimer(2, 500);  // 500ms interval

	/*************************************************************************/


	/* main program */
	while(1){
		/* System function */
		systemFunction();

		/* TO-DO: your task implementations **********************************/

		if (state == ENGINE_ON) {

			PIT_StartTimer(1);  // sends CAN msgs
		} else {
			PIT_StopTimer(1);
		}


		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	CAN receive interrupt
 *
 * @param   CANDriver   canp	The CAN controller which received a message
 * @param	CANRxFrame	crfp	The message which was received
 * @retval	void
 */
void can_receive(CANRxFrame crfp) {
    LED_Rx_Toggle();  // Blink when any message received

    if (crfp.SID == 0x11 && state == IDLE) {
        state = ENGINE_ON;
        LED_P_Set(); // Turn LED_P ON
    } else if (crfp.SID == 0x10 && state == ENGINE_ON) {
        state = IDLE;
        LED_P_Clear(); // Turn LED_P OFF
    }
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void){
	/* TO-DO: your task implementations **************************************/

	// EngineOn Message
	can_send_engine_on();

	// SPEED from POT
	can_send_speed();

	// RPM oscillation
    can_send_rpm();

	// Lights message
    can_send_lights();

}


/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void){
	/* TO-DO: your task implementations **************************************/
	// Lights message
    blink = !blink;
}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){
	/* TO-DO: your task implementations **************************************/


}
