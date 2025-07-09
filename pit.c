/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: pit.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "pit.h"

/*
 * @brief	PIT timer initialization function
 *
 * @param	void
 * @retval	void
 */
void PIT_Init(void){
	pit_lld_start(&PITD, pit_config);
}


/*
 * @brief	PIT timer configuration function
 *
 * @param	uint8_t		timerChannel		PIT channel number (1-3)
 * @param	uint32_t	timerFrequency		Timer Freqency in Hz
 * @retval	void
 */
void PIT_ConfigureTimer(uint8_t timerChannel, uint32_t timerFrequency){
	pit_lld_channel_set_freq(&PITD, timerChannel, (1000 / timerFrequency));
}


/*
 * @brief	PIT timer start function
 *
 * @param	uint8_t		timerChannel		PIT channel number (1-3)
 * @retval	void
 */
void PIT_StartTimer(uint8_t timerChannel){
	pit_lld_channel_start(&PITD, timerChannel);
}


/*
 * @brief	PIT timer stop function
 *
 * @param	uint8_t		timerChannel		PIT channel number (1-3)
 * @retval	void
 */
void PIT_StopTimer(uint8_t timerChannel){
	pit_lld_channel_stop(&PITD, timerChannel);
}
