/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    cortina_automatizada.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "api_motor_passos.h"
#include "api_sensor_luminosidade.h"
#include "api_sensor_chuva.h"
#include "api_buzzer.h"

/* TODO: insert other definitions and declarations here. */
extern int direcao;

void PORTx_config(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
}

void TPM_config(void){
	/*habilitando clock do modulo Timer/PWM TPM0, TPM1 e 2*/
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK;

	/* Seleciona a fonte de relógio para o contador TPM */
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); /*MCGIRCLK (32.768 kHz)*/

	/*configurando o prescaler select (divisao por 4)*/
	TPM0->SC |= TPM_SC_PS(2);
	TPM1->SC |= TPM_SC_PS(2);
	TPM2->SC |= TPM_SC_PS(2);

	/* habilitando o contador */
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM1->SC |= TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CMOD(1);

	/*habilitando flag de interrupcao clear TOF*/
	TPM0->SC |= TPM_SC_TOF_MASK; // Limpa a flag TOF
	TPM1->SC |= TPM_SC_TOF_MASK; // Limpa a flag TOF
	TPM2->SC |= TPM_SC_TOF_MASK; // Limpa a flag TOF
	TPM0->SC |= TPM_SC_TOIE_MASK; // Habilita a interrupção TOF
	TPM1->SC |= TPM_SC_TOIE_MASK; // Habilita a interrupção TOF
	TPM2->SC |= TPM_SC_TOIE_MASK; // Habilita a interrupção TOF
}

void delay_ms(float tempo_ms){
	/*Calculando o número de ciclos para o delay*/
	uint32_t ciclos_por_delay = (tempo_ms*1000) / 122;

	/*configurando valor do registrador de contagem para obter o tempo*/
	TPM1->MOD = ciclos_por_delay - 1;

	while((TPM1->SC & TPM_SC_TOF_MASK) == 0) { } /* wait until the TOF is set */
	TPM1->SC |= TPM_SC_TOF_MASK;/* clear TOF */
}

void pwm_delay_ms(float duty_cycle, double periodo) {
	 /* verificando se o valor do duty cycle esta no intervalo valido (0 a 100) */
	if(duty_cycle > 100){
		duty_cycle = 100;
	}else if(duty_cycle < 0){
		duty_cycle = 0;
	}

	double ciclos_por_delay = (periodo*1000) / 122;

	/*configurando valor do registrador de contagem para obter o tempo*/
	TPM2->MOD = ciclos_por_delay - 1;

    /*gerando sinal PWM com dutyCycle informado em porcentagem*/
	double duty_cycles = (ciclos_por_delay * duty_cycle) / 100;
    TPM2->CONTROLS[0].CnV =  duty_cycles;
}

void LPTMR0_Init(void) {
	/* habilitando o clock para Low Power Timer */
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;

    /* habilitando o clock de 1khz e bypass */
    LPTMR0->PSR |= LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;

    /* T = (1 / 1KHz) = 1ms */
    /* CMR = 5s / 1ms = 5000 seg */
    LPTMR0->CMR = 5000;

    /*habilitando interrupcoes */
    LPTMR0->CSR |= LPTMR_CSR_TIE_MASK | LPTMR_CSR_TEN_MASK;

    /*habilitando interrupcoes no NVIC para o LPTMR*/
    NVIC_EnableIRQ(LPTMR0_IRQn);
}

// Tratador de interrupção do LPTimer
void LPTimer_IRQHandler(void){

	/*limpando flag*/
	LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;

	/*fazendo a leitura do nivel logico do pino referente ao LDR*/
	uint32_t statusLDR = (GPIOB->PDIR >> 1) & 0x01;
	static uint32_t ultimoStatusLDR = 0;

	if (statusLDR != ultimoStatusLDR){
		if (statusLDR) {
			printf("Está escuro, fechar cortina.\n");
			fechaCortina();
			direcao = 0;
		} else {
			printf("Está claro, abrir cortina.\n");
			abreCortina();
			direcao = 1;
		}
		 ultimoStatusLDR = statusLDR;
	}
}



void PORTA_IRQHandler(void){
	buzzerConfig();
	for(int i = 0; i < 5; i++){
		pwm_delay_ms(50, 0.6667);
		delay_ms(500);
		pwm_delay_ms(50, 0.4);
		delay_ms(500);
		pwm_delay_ms(50, 0.6667);
		delay_ms(500);
	}
	Desativabuzzer();
    PORTA->ISFR = (1 << 13); /* clear interrupt flag */
}

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    __disable_irq(); /* disable all IRQs */
    PORTx_config(); /*configurando clock para o modulo PORTx */
    sensorChuvaConfig();
    sensorLuminosidadeConfig();
    TPM_config();
    LPTMR0_Init();
    NVIC_EnableIRQ(PORTA_IRQn); /* enable INT30 (bit 30 of ISER[0]) */
    __enable_irq(); /* global enable IRQs */

	while(1){}
}
