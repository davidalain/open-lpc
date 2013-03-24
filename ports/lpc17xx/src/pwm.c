/*
 * pwm.c
 * Funcões para objeto pwm_t
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 12/03/2013
 * Copyright: Cristóvão e David
 */

#include <pwm.h>
#include <LPC17xx.h>
#include <system_LPC17xx.h>

void pwm_setup (pwm_t *pwm, void *pwm_num, uint32_t freq) {

}

void pwm_write (const pwm_t *pwm, uint32_t duty) {

}

uint32_t pwm_read (const pwm_t *pwm) {

	return 0;
}

void pwm_write_float (const pwm_t *pwm, float duty) {

}

float pwm_read_float (const pwm_t *pwm) {

	return 0;
}
