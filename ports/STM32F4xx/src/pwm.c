/*
 * pwm.c
 * Funcões para objeto pwm_t
 * Author: David Alain do Nascimento
 * Version STM32F407xx 0.1
 * Date: 12/03/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <pwm.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

static void __configure_tim3 (uint32_t channel, uint32_t freq) {

	uint16_t tmp = 0;

	tmp = 	(0b00 << 8) |	// Clock division = 1 -> 84MHz
				(1 << 7) 	|	// TIMx_ARR com buffer
				(0b00 << 5) | 	// Center-aligned mode directio = definido pelo DIR
				(0 << 4)	|	// Upcounting
				(0 << 3);		// Counter continua contando no evento de Update

	TIM3->CR1 = tmp;

	RCC->APB1ENR |= (1 << 1);	// Ativa o clock do Timer 3
	TIM3->CR1 |= TIM_CR1_CEN;	// Ativa o timer
	/*
	 * OBS.: É necessário ativar o Timer antes de continuar a configurar
	 * os registradores. Não fazendo isso, as configurações são descartadas
	 * e uma vez que você ligar, nada irá funcionar como desejado
	 * */

	TIM3->PSC = 84 - 1;	// Coloca o prescaler para 84 pulsos -> 84MHz / 84 = 1MHz
	TIM3->ARR = 1000000 / freq;	// Coloca 1MHz / TIM3->ARR. freq = 1000 -> Período = 1KHz
	TIM3->EGR |= (1 << 0);	// Reinicializa o contador automaticamente

	RCC->AHB1ENR |= (1 << 2);	// Ativa o clock do GPIOC
	switch (channel) {
		default:
		case 1:	// PC6
			GPIOC->MODER &= ~(0b11 << 12);
			GPIOC->MODER |= (0b10 << 12);	// Configura como função alternativa

			GPIOC->OTYPER &= ~(1 << 6);		// Configura como push-pull

			GPIOC->OSPEEDR |= (0b11 << 12);	// Configura como 100MHz

			GPIOC->PUPDR &= ~(0b11 << 12);
			GPIOC->PUPDR |= (0b10 << 12);	// Ativa o pull-up

			GPIOC->AFR[0] &= ~(0b1111 << 24);
			GPIOC->AFR[0] |= (0b0010 << 24);	// Configura como TIM3_CH1

			TIM3->CCER &= ~(1 << 0);
			tmp = TIM3->CCMR1 & 0xFF00;
			tmp = 	(0b00 << 0)	|	// Canal CC1 configurado como saída
					(0 << 3)	|	// OC1 preload desabilitado
					(0b110 << 4);	// OC1M = PWM1
			TIM3->CCMR1 &= 0xFF00;
			TIM3->CCMR1 |= tmp;
			TIM3->CCER |= (1 << 0);
			break;

		case 2:	// PC7
			GPIOC->MODER &= ~(0b11 << 14);
			GPIOC->MODER |= (0b10 << 14);	// Configura como função alternativa

			GPIOC->OTYPER &= ~(1 << 7);		// Configura como push-pull

			GPIOC->OSPEEDR |= (0b11 << 14);	// Configura como 100MHz

			GPIOC->PUPDR &= ~(0b11 << 14);
			GPIOC->PUPDR |= (0b10 << 14);	// Ativa o pull-up

			GPIOC->AFR[0] &= ~(0b1111 << 28);
			GPIOC->AFR[0] |= (0b0010 << 28);	// Configura como TIM3_CH2

			TIM3->CCER &= ~(1 << 4);
			tmp = TIM3->CCMR1 & 0x00FF;
			tmp = 	(0b00 << 8)	|	// Canal CC2 configurado como saída
					(0 << 11)	|	// OC2 preload desabilitado
					(0b110 << 12);	// OC2M = PWM1
			TIM3->CCMR1 &= 0x00FF;
			TIM3->CCMR1 |= tmp;
			TIM3->CCER |= (1 << 4);
			break;

		case 3:	// PC8
			GPIOC->MODER &= ~(0b11 << 16);
			GPIOC->MODER |= (0b10 << 16);	// Configura como função alternativa

			GPIOC->OTYPER &= ~(1 << 8);		// Configura como push-pull

			GPIOC->OSPEEDR |= (0b11 << 16);	// Configura como 100MHz

			GPIOC->PUPDR &= ~(0b11 << 16);
			GPIOC->PUPDR |= (0b10 << 16);	// Ativa o pull-up

			GPIOC->AFR[1] &= ~(0b1111 << 0);
			GPIOC->AFR[1] |= (0b0010 << 0);	// Configura como TIM3_CH3

			TIM3->CCER &= ~(1 << 8);
			tmp = TIM3->CCMR2 & 0x00FF;
			tmp = 	(0b00 << 0)	|	// Canal CC3 configurado como saída
					(0 << 3)	|	// OC3 preload desabilitado
					(0b110 << 4);	// OC3M = PWM1
			TIM3->CCMR2 &= 0x00FF;
			TIM3->CCMR2 |= tmp;
			TIM3->CCER |= (1 << 8);
			break;

		case 4:	// PC9
			GPIOC->MODER &= ~(0b11 << 18);
			GPIOC->MODER |= (0b10 << 18);	// Configura como função alternativa

			GPIOC->OTYPER &= ~(1 << 9);		// Configura como push-pull

			GPIOC->OSPEEDR |= (0b11 << 18);	// Configura como 100MHz

			GPIOC->PUPDR &= ~(0b11 << 18);
			GPIOC->PUPDR |= (0b10 << 18);	// Ativa o pull-up

			GPIOC->AFR[1] &= ~(0b1111 << 4);
			GPIOC->AFR[1] |= (0b0010 << 4);	// Configura como TIM3_CH4

			TIM3->CCER &= ~(1 << 12);
			tmp = TIM3->CCMR2 & 0x00FF;
			tmp = 	(0b00 << 8)	|	// Canal CC2 configurado como saída
					(0 << 11)	|	// OC2 preload desabilitado
					(0b110 << 12);	// OC2M = PWM1
			TIM3->CCMR2 &= 0x00FF;
			TIM3->CCMR2 |= tmp;
			TIM3->CCER |= (1 << 12);
			break;
	}

}

void pwm_setup (pwm_t *pwm, void *pwm_num, uint32_t channel, uint32_t freq) {

	pwm->pwm = pwm_num;
	pwm->freq = freq;
	pwm->channel = channel;

	switch ((uint32_t)pwm_num) {
		case TIM3_BASE:
			__configure_tim3(channel, freq);
			break;

		default:
			break;	// TODO: Hardfault, talvez?
	}
}

void pwm_write (pwm_t *pwm, uint32_t duty) {
	switch (pwm->channel) {
		default:
		case 1:
			((TIM_TypeDef *)pwm->pwm)->CCR1 = duty;
			break;

		case 2:
			((TIM_TypeDef *)pwm->pwm)->CCR2 = duty;
			break;

		case 3:
			((TIM_TypeDef *)pwm->pwm)->CCR3 = duty;
			break;

		case 4:
			((TIM_TypeDef *)pwm->pwm)->CCR4 = duty;
			break;
	}
}

uint32_t pwm_read (const pwm_t *pwm) {

	uint32_t ret;

	switch (pwm->channel) {
		default:
		case 1:
			ret = ((TIM_TypeDef *)pwm->pwm)->CCR1;
			break;

		case 2:
			ret = ((TIM_TypeDef *)pwm->pwm)->CCR2;
			break;

		case 3:
			ret = ((TIM_TypeDef *)pwm->pwm)->CCR3;
			break;

		case 4:
			ret = ((TIM_TypeDef *)pwm->pwm)->CCR4;
			break;
	}

	return ret;
}

void pwm_write_float (pwm_t *pwm, float duty) {

	pwm_write (pwm, (uint32_t)(duty * 1000.0f));
}

float pwm_read_float (const pwm_t *pwm) {

	return 0.001f*(float)pwm_read(pwm);
}

#ifdef __cplusplus
}
#endif

