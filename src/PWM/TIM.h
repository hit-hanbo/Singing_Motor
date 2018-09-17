/*
 * TIM.h
 *
 *  Created on: 2018Äê9ÔÂ17ÈÕ
 *      Author: squar
 */

#ifndef TIM_H_
#define TIM_H_

void TIM1_Init(uint32_t PSC);
void TIM1_PWM_Start(void);
void TIM1_Set_PWM_Freq(uint32_t freq);
void TIM1_Set_PWM_Duty(uint8_t Duty_Percent);


#endif /* TIM_H_ */
