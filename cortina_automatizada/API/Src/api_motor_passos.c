/*
 * =====================================================================================
 *
 *       Filename:  api_motor_passos.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  17/06/2023 21:06:41
 *       Revision:  none
 *       Compiler:  -
 *
 *         Author:  Isaac Vinicius, isaacvinicius2121@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

/* Includes ------------------------------------------------------------------*/
#include "api_motor_passos.h"

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/

int direcao = 0;

int32_t comprimentoCortina(float cm){
	/*1 cm = 343 interacoes*/
	 int32_t interacoes = (int32_t)(cm * 344.0);
	 return interacoes;
}

void velocidade_ms(float tempo_ms){
	/*Calculando o número de ciclos para o delay*/
	uint32_t ciclos_por_delay = (tempo_ms*1000) / 122;

	/*configurando valor do registrador de contagem para obter o tempo*/
	TPM0->MOD = ciclos_por_delay - 1;

	while((TPM0->SC & TPM_SC_TOF_MASK) == 0) { } /* wait until the TOF is set */
	TPM0->SC |= TPM_SC_TOF_MASK;/* clear TOF */
}

void abreCortina(void){
	/* fazendo a mutiplexacao e configurando os pino PDT0, PDT1, PDT2 e PDT3 como saida para o motor de passos*/
	PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK; 	 // Limpa os bits de configuração do MUX
	PORTD->PCR[0] |= PORT_PCR_MUX(1);		// Configura o MUX para GPIO (Mux 1)
	GPIOD->PDDR |= (1U << 0);				// Configura o pino como saida

	PORTD->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[1] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 1);

	PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 2);

	PORTD->PCR[3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 3);


	const char steps[ ] = {0x9, 0x3, 0x6, 0xC};
	int32_t rotacao = comprimentoCortina(23.5);
	int i = 0;

	for(int j = 0; j < rotacao; ++j){
		if (direcao){
			PTD->PDOR = (steps[i++ & 3]);

		}else{
			PTD->PDOR = (steps[i-- & 3]);
		}
		velocidade_ms(1.6666666666667);
	}
}
void fechaCortina(void){
	/* fazendo a mutiplexacao e configurando os pino PD0, PD1, PD2 e PD3 como saida para o motor de passos*/
	PORTD->PCR[0] &= ~PORT_PCR_MUX_MASK; 	 // Limpa os bits de configuração do MUX
	PORTD->PCR[0] |= PORT_PCR_MUX(1);		// Configura o MUX para GPIO (Mux 1)
	GPIOD->PDDR |= (1U << 0);				// Configura o pino como saida

	PORTD->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[1] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 1);

	PORTD->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[2] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 2);

	PORTD->PCR[3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[3] |= PORT_PCR_MUX(1);
	GPIOD->PDDR |= (1U << 3);

	const char steps[ ] = {0x9, 0x3, 0x6, 0xC};
	int32_t rotacao = comprimentoCortina(23.5);
	int i = 0;

	for(int j = 0; j < rotacao; ++j){
		if (direcao){
			PTD->PDOR = (steps[i++ & 3]);

		}else{
			PTD->PDOR = (steps[i-- & 3]);
		}
		velocidade_ms(1.6666666666667);
	}
}
