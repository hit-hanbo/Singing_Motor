/*
 * TIM.c
 *
 *  Created on: 2018Äê9ÔÂ17ÈÕ
 *      Author: squar
 */
#include "stm32f4xx.h"
#include "TIM.h"
#define SYSCLK 160000000

void TIM1_Init(uint32_t PSC)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;    // ENABLE TIM1 Timer
	TIM1->PSC     = PSC;                   // Pre Scale Value
	TIM1->CR1     = 0x00000084;            // ENABLE ARR, ENABLE Update IRQ
	TIM1->CCMR1   |= (1 << 3);             // CC1 Preload ENABLE
	TIM1->CCMR1   |= (0x03 << 5);          // CC1 = PWM2
	TIM1->CCER    |= (1 << 2);          // CC1N High Available
	TIM1->CCER    &= ~(1 << 1);            // CC1 LOW Available
	TIM1->BDTR    |= (0x03 << 14) | (0x03 << 10);
                                           // Auto Output, Master Output, OSSR, OSSI ENABLE
	TIM1->BDTR    |= (0x03 << 6);          // Dead Area Step 1us
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOEEN;  // ENABLE GPIOE Clock
	GPIOE->MODER  |= (1 << 19);
	GPIOE->MODER  &= ~(1 << 18);           // GPIOE9 - AF Output
	GPIOE->OTYPER &= ~(1 << 9);            // GPIOE9 - PP
	GPIOE->PUPDR  |= (1 << 19);
	GPIOE->PUPDR  &= ~(1 << 18);           // GPIOE9 - Pull-Down
	GPIOE->OSPEEDR|= (0x03 << 18);         // GPIOE9 - High Speed
	GPIOE->AFR[1] |= (1 << 4);
	GPIOE->AFR[1] &= ~(0x07 << 5);         // GPIOE9 - AF1 <--> TIM1
	RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN;  // ENABLE GPIOA Clock
	GPIOA->MODER  |= (1 << 15);
	GPIOA->MODER  &= ~(1 << 14);           // GPIOA7 - AF Output
	GPIOA->OTYPER &= ~(1 << 7);            // GPIOA7 - PP
	GPIOA->PUPDR  |= (1 << 15);
	GPIOA->PUPDR  &= ~(1 << 14);           // GPIOA7 - Pull-Down
	GPIOA->OSPEEDR|= (0x03 << 14);         // GPIOA7 - High Speed
	GPIOA->AFR[0] |= (1 << 28);
	GPIOA->AFR[0] &= ~(0x07 << 29);        // GPIOA7 - AF1 <--> TIM1
}

void TIM1_PWM_Start(void)
{
	TIM1->CR1     |= TIM_CR1_CEN;          // ENABLE TIM1
	TIM1->CCER    |= 0x01;                 // ENABLE CC1
}

void TIM1_Set_PWM_Freq(uint32_t freq)
{
	uint32_t ARR, PSC;
	PSC = TIM1->PSC;
	ARR = (uint32_t) SYSCLK / (PSC + 1) / freq;
	TIM1->ARR = ARR;
}
void TIM1_Set_PWM_Duty(uint8_t Duty_Percent)
{
	uint32_t CCR, ARR;
	ARR = TIM1->ARR;
	CCR = (uint32_t) (Duty_Percent * ARR / 100);
	TIM1->CCR1 = CCR;
}

