/*
 * =====================================================================================
 *
 *       Filename:  api_buzzer.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  17/06/2023 22:40:41
 *       Revision:  none
 *       Compiler:  -
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

/* Includes ------------------------------------------------------------------*/
#include "api_buzzer.h"

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void buzzerConfig(void){
	/*Pino multiplexidado com PWM TPM2_CH0*/
	PORTB->PCR[2] |= PORT_PCR_MUX(3);

	/* Desativando o PWM no modulo TPM*/
	TPM2->CONTROLS[0].CnSC = (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2);

	/* Ativando o PWM no modulo TPM*/
	TPM2->CONTROLS[0].CnSC = (1 << 5) | (0 << 4) | (1 << 3) | (0 << 2);
}

void Desativabuzzer(void){
	TPM2->CONTROLS[0].CnSC = (1 << 5) | (0 << 4) | (1 << 3) | (0 << 2);
}
