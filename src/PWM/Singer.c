/*
 * Singer.c
 *
 *  Created on: 2018Äê9ÔÂ17ÈÕ
 *      Author: squar
 */
#include "stm32f4xx.h"
#include "Singer.h"
#include "TIM.h"

// define C tune
#define N 10000

#define DOb 260
#define REb 294
#define MIb 330
#define FAb 350
#define SOb 392
#define LAb 440
#define SIb 494

#define DO 523
#define RE 587
#define MI 659
#define FA 698
#define SO 784
#define LA 880
#define SI 988

#define DOs 1046
#define REs 1175
#define MIs 1318
#define FAs 1397
#define SOs 1568
#define LAs 1760
#define SIs 1976

// define Time Value /us
#define FULL_DOb 3816
#define FULL_REb 3401
#define FULL_MIb 3030
#define FULL_FAb 2865
#define FULL_SOb 2551
#define FULL_LAb 2272
#define FULL_SIb 2048

#define FULL_DO 1908
#define FULL_RE 1700
#define FULL_MI 1515
#define FULL_FA 1432
#define FULL_SO 1276
#define FULL_LA 1136
#define FULL_SI 1012

#define FULL_DOs 956
#define FULL_REs 852
#define FULL_MIs 759
#define FULL_FAs 716
#define FULL_SOs 784
#define FULL_LAs 638
#define FULL_SIs 506

#define HALF_DOb 1908
#define HALF_REb 1700
#define HALF_MIb 1515
#define HALF_FAb 1432
#define HALF_SOb 1276
#define HALF_LAb 1136
#define HALF_SIb 1024

#define HALF_DO 956
#define HALF_RE 852
#define HALF_MI 759
#define HALF_FA 716
#define HALF_SO 784
#define HALF_LA 638
#define HALF_SI 506

#define HALF_DOs 478
#define HALF_REs 426
#define HALF_MIs 379
#define HALF_FAs 358
#define HALF_SOs 319
#define HALF_LAs 284
#define HALF_SIs 253

#define X 13

uint32_t notes[X][2]={
		{SO, HALF_SO},
		{MI, HALF_MI},
		{SO, HALF_SO},
		{MI, HALF_MI},
		{SO, HALF_SO},
		{MI, HALF_MI},
		{DO, 2 * FULL_DO},
		{RE, HALF_RE},
		{FA, HALF_FA},
		{MI, HALF_MI},
		{RE, HALF_RE},
		{SO, 2 * FULL_SO},
		{N, FULL_DO},
};
uint16_t i = 1;

void Sing_Start()
{
	TIM1_Set_PWM_Freq(notes[0][0]);
	TIM7_SetVal(notes[0][1]);
	TIM1_PWM_Start();
}

void TIM7_IRQHandler(void)
{
	TIM7->SR &= 0x0;
	TIM1_PWM_Stop();
	if(i == X - 1)
		i = 0;
	else
		i ++;
	TIM1_Set_PWM_Freq(notes[i][0]);
	TIM7_SetVal(notes[i][1]);
	TIM1_Set_PWM_Duty(50);
	TIM1_PWM_Start();
	TIM7_Start();
}
