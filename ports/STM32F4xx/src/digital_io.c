/*
 * digital_io.c
 * Funcões para objetos DigitalIn e DigitalOut
 * Author: David Alain do Nascimento
 * Co-author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 * Version STM32F407xx 0.1
 * Date: 16/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <digital_in.h>
#include <digital_out.h>

#include <stm32f4xx.h>

inline static void digital_general_setup (digital_io_t *pin, void *portnum, uint32_t pinnum) {

	uint32_t port_bit;

	pin->port = portnum;
	pin->pinnum = pinnum;

	// Ativando CLOCK para GPIO
	port_bit = ((uint32_t)portnum - AHB1PERIPH_BASE) / 0x0400;
	RCC->AHB1ENR |= (1 << port_bit);
}

static inline uint32_t digital_generic_read (const digital_io_t *pin) {
	GPIO_TypeDef *p_gpio = (GPIO_TypeDef *)pin->port;
	return (p_gpio->IDR & (1 << pin->pinnum))?1:0;
}

void digitalin_setup (digital_io_t *pin, void* portnum, uint32_t pinnum) {

	GPIO_TypeDef *p_gpio = (GPIO_TypeDef *)portnum;
	digital_general_setup (pin, portnum, pinnum);

	// Configura o pino de GPIO como INPUT	
	p_gpio->MODER &= (~(1 << (pinnum * 2 + 1)) & ~(1 << (pinnum * 2)));

	// Configura o pino sem PULL-UP e PULL-DOWN
	p_gpio->PUPDR &= (~(1 << (pinnum * 2 + 1)) & ~(1 << (pinnum * 2)));
}

uint32_t digitalin_read (const digital_io_t *pin) {
	return digital_generic_read(pin);
}

void digitalout_setup (digital_io_t *pin, void* portnum, uint32_t pinnum) {

	GPIO_TypeDef *p_gpio = (GPIO_TypeDef *)portnum;
	digital_general_setup (pin, portnum, pinnum);

	// Configura o pino de GPIO como OUTPUT	
	p_gpio->MODER &= ~(1 << (pinnum * 2 + 1));
	p_gpio->MODER |= (1 << (pinnum * 2));

	// Configura o pino sem PULL-UP e PULL-DOWN
	p_gpio->PUPDR &= (~(1 << (pinnum * 2 + 1)) & ~(1 << (pinnum * 2)));

	// Configura a velocidade máxima de saída como 2 MHz
	p_gpio->OSPEEDR &= (~(1 << (pinnum * 2 + 1)) & ~(1 << (pinnum * 2)));
}

void digitalout_write (const digital_io_t *pin, uint32_t value) {
	GPIO_TypeDef *p_gpio = (GPIO_TypeDef *)pin->port;

	if (value)
		p_gpio->BSRRH |= (1 << pin->pinnum);
	else
		p_gpio->BSRRL |= (1 << pin->pinnum);
}

uint32_t digitalout_read (const digital_io_t *pin) {
	return digital_generic_read(pin);
}

#ifdef __cplusplus
}
#endif

