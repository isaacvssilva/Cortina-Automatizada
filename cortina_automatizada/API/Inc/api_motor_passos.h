/*
 * =====================================================================================
 *
 *       Filename:  api_motor_passos.h
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

#ifndef API_MOTOR_PASSOS_H_
#define API_MOTOR_PASSOS_H_

/* Includes ------------------------------------------------------------------*/
#include "MKL25Z4.h"

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void abreCortina(void);
void fechaCortina(void);
void velocidade_ms(float tempo_ms);
int32_t comprimentoCortina(float cm);
#endif
/*****************************END OF FILE**************************************/
