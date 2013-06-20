/*
 * counter.c
 *
 *  Created on: 15/06/2013
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include <counter.h>
#include <stm32f4xx.h>

static void __configure_pa15 (void) {

	RCC->AHB1ENR |= (1 << 0);	// Ativa o clock do GPIOA

	GPIOA->MODER &= ~(0b11 << 30);
	GPIOA->MODER |= (0b10 << 30);	// Configura como função alternativa

	GPIOA->OTYPER &= ~(1 << 15);		// Configura como push-pull

	GPIOA->OSPEEDR |= (0b11 << 30);	// Configura como 100MHz

	GPIOA->PUPDR &= ~(0b11 << 12);	// Desativa o pull-up

	GPIOA->AFR[1] &= ~(0b1111 << 28);
	GPIOA->AFR[1] |= (0b0001 << 28);	// Configura como TIM2_CH1

}

static void __configure_tim2 (uint32_t div) {

	RCC->APB1ENR |= (1 << 0);	// Ativa o clock do TIM2
	TIM2->CR1 = (1 << 0) 	|	// Ativa o TIM2
				(0 << 4)	|	// TIM2 como upcounter
				(0b00 << 8);	// TIM2 com divisor = 1

	TIM2->SMCR = (0b111 << 0)	|	// Slave Mode Selection = external clock mode
				(0b111 << 4);		// Trigger selection = external trigger input (ETRF)

	TIM2->PSC = div - 1;

	TIM2->ARR = 0xFFFFFFFF;		// Conta o máximo que puder
}

void counter_setup (counter_t *counter, void * timer, uint32_t div) {
	counter->counter = timer;
	counter->div = div;

	switch ((uint32_t)timer) {
	case TIM2_BASE:
		__configure_pa15();
		__configure_tim2(div);
		break;

	default:
		break;
	}
}

uint32_t counter_read (const counter_t *counter) {
	return ((TIM_TypeDef *)counter->counter)->CNT;
}

void counter_reset (const counter_t *counter) {
	((TIM_TypeDef *)counter->counter)->CNT = 0;
}
