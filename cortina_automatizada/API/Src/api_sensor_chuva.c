/*
 * =====================================================================================
 *
 *       Filename:  api_sensor_chuva.c
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
#include "api_sensor_chuva.h"

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void sensorChuvaConfig(void){

	PORTA->PCR[13] &= ~PORT_PCR_MUX_MASK;  // Limpa os bits de configuração do MUX
	PORTA->PCR[13] |= PORT_PCR_MUX(1);     // Configura o MUX para GPIO (Mux 1)
	GPIOA->PDDR &= ~(1 << 13);            // Configura o pino como entrada

    /*configuracoes para usar o pino com interrrupcao*/
	PORTA->PCR[13] &= ~PORT_PCR_IRQC_MASK; /* clear interrupt selection */
    PORTA->PCR[13] |= PORT_PCR_IRQC(10); /* enable falling edge interrupt */
}
