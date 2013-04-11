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

void pwm_setup (pwm_t *pwm, void *pwm_num, uint32_t freq) {
	TIM_TypeDef *pwm_typedef = (TIM_TypeDef *)pwm_num;

	pwm->pwm = pwm_num;
	pwm->freq = freq;

	switch ((uint32_t)pwm_num) {
		case TIM9_BASE:
			// AAR: frequency
			// CCR(1): Duty
			break;

		case TIM10_BASE:
			break;

		case TIM11_BASE:
			break;

		case TIM12_BASE:
			break;

		case TIM13_BASE:
			break;

		case TIM14_BASE:
			break;

		default:
			break;	// TODO: Hardfault, talvez?
	}
}

void pwm_write (const pwm_t *pwm, uint32_t duty) {

}

uint32_t pwm_read (const pwm_t *pwm) {

	return 0;
}

void pwm_write_float (const pwm_t *pwm, float duty) {

}

float pwm_read_float (const pwm_t *pwm) {

	return 0.0f;
}

#ifdef __cplusplus
}
#endif

