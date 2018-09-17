#include "stm32f4xx.h"
#include "PWM/TIM.h"

void NVIC_Init_Priority_Group(void);
void SysTick_Init(void);



int main(void)
{
	SysTick_Init();
	NVIC_Init_Priority_Group();
	TIM1_Init(159);
	TIM1_Set_PWM_Freq(1000);
	TIM1_Set_PWM_Duty(60);
	TIM1_PWM_Start();
	for(;;);
}

// Init Systick Timer
void SysTick_Init(void)
{
	SysTick->LOAD  = 42000000;       //  SysTick Freq = 1KHz
    SysTick->CTRL |= 0x00000003;     //  SysTick ENABLE IRQ, CLK = SYS_CLK / 8
}

// Init NVIC
void NVIC_Init_Priority_Group(void)
{
	uint32_t tmp_AIRCR = 0x00000000;
	tmp_AIRCR |= 0xfa050000;          //  Set AIRCR_KEY
	tmp_AIRCR |= (1 << 8) | (1 << 10);
	tmp_AIRCR &= ~(1 << 9);           //  Set xx.yy
	SCB->AIRCR = tmp_AIRCR;           //  Set AIRCR
}

void SysTick_Handler(void)
{
	/*
	 * Place Holder For SysTick Handler
	 */
}
