/*
 * timer.c
 * Funcões para objeto timer_t
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 13/03/2013
 * Copyright: Cristóvão e David
 */

#include <Timer.h>
#include <LPC17xx.h>
#include <system_LPC17xx.h>

void timer_setup (timer_t *timer, uint32_t timer_num, uint32_t prescaler, uint32_t div) {

	LPC_TIM_TypeDef *l_timer;

	timer->timer = timer_num;
	timer->prescaler = prescaler;
	timer->div = div;

	// O timer não configura pinos para captura e comparação
	// apenas o timer para leitura e comparação
	switch (timer_num) {
		case LPC_TIM0_BASE:
			LPC_SC->PCONP |= (1 << 1);
			timer->clksel = (LPC_SC->PCLKSEL0 >> 2) & 0x03;
			break;

		case LPC_TIM1_BASE:
			LPC_SC->PCONP |= (1 << 2);
			timer->clksel = (LPC_SC->PCLKSEL0 >> 4) & 0x03;
			break;

		case LPC_TIM2_BASE:
			LPC_SC->PCONP |= (1 << 22);
			timer->clksel = (LPC_SC->PCLKSEL1 >> 12) & 0x03;
			break;

		case LPC_TIM3_BASE:
			LPC_SC->PCONP |= (1 << 23);
			timer->clksel = (LPC_SC->PCLKSEL1 >> 14) & 0x03;
			break;

		default:
			// TODO: Hardfault, talvez?
			break;
	}

	l_timer = (LPC_TIM_TypeDef *)timer_num;

	l_timer->CTCR = 0x00;		// Configura o timer/counter como timer
	timer_set_prescaler (timer, prescaler, div);
}

void timer_set_prescaler (timer_t *timer, uint32_t prescaler, uint32_t div) {
	LPC_TIM_TypeDef *l_timer;

	l_timer = (LPC_TIM_TypeDef *)timer->timer;
	l_timer->PR = prescaler;	// Configura o prescaler
	l_timer->PC = div;			// Condfigura o divisor
}

void timer_reset (const timer_t *timer) {
	LPC_TIM_TypeDef *l_timer;

	l_timer = (LPC_TIM_TypeDef *)timer->timer;
	l_timer->TCR |= (1 << 1);
	l_timer->TCR &= ~(1 << 1);
}

uint32_t timer_read (const timer_t *timer) {
	LPC_TIM_TypeDef *l_timer;

	l_timer = (LPC_TIM_TypeDef *)timer->timer;
	return l_timer->TC;
}
