/*
 * =====================================================================================
 *
 *       Filename:  api_sensor_luminosidade.h
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  17/06/2023 23:38:32
 *       Revision:  none
 *       Compiler:  -
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

/* Includes ------------------------------------------------------------------*/
#include "api_sensor_luminosidade.h"

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void sensorLuminosidadeConfig(void){

	/* fazendo a mutiplexacao e configurando s pino PTB1 como entrada*/
	PORTB->PCR[1] &= ~PORT_PCR_MUX_MASK;  // Limpa os bits de configuração do MUX
	PORTB->PCR[1] |= PORT_PCR_MUX(1);     // Configura o MUX para GPIO (Mux 1)
	GPIOB->PDDR &= ~(1U << 1);            // Configura o pino como entrada
}
