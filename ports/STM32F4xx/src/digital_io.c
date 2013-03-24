/*
 * digital_io.c
 * Funcões para objetos DigitalIn e DigitalOut
 * Author: David Alain do Nascimento
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
	pin->port = portnum;
	pin->pinnum = pinnum;

	switch (portnum) {	// Reconfigura os registradores dos pinos em PINCON

		default:
			// TODO: Invoke a hard-fault function or so
			return ;
	}
}

static inline uint32_t digital_generic_read (const digital_io_t *pin) {
	GPIO_TypeDef *port = (GPIO_TypeDef *)pin->port;

	if (port->FIOPIN & (1 << ((struct _pin *)pin)->pinnum)){
		return 1;
	}else{
		return 0;
	}
}

void digitalin_setup (digital_io_t *pin, void* portnum, uint32_t pinnum) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)portnum;

	digital_general_setup (pin, portnum, pinnum);

	gpio->FIODIR &= ~(1 << pinnum);
	gpio->FIOMASK &= ~(1 << pinnum);
}

uint32_t digitalin_read (const digital_io_t *pin) {
	return digital_generic_read(pin);
}

void digitalout_setup (digital_io_t *pin, void* portnum, uint32_t pinnum) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)portnum;

	digital_general_setup (pin, portnum, pinnum);

	gpio->FIODIR |= (1 << pinnum);
	gpio->FIOMASK &= ~(1 << pinnum);
}

void digitalout_write (const digital_io_t *pin, uint32_t value) {
	GPIO_TypeDef *gpio = (GPIO_TypeDef *)pin->port;

	if (value)
		gpio->FIOSET = 1 << pin->pinnum;
	else
		gpio->FIOCLR = 1 << pin->pinnum;
}

uint32_t digitalout_read (const digital_io_t *pin) {
	return digital_generic_read(pin);
}

#ifdef __cplusplus
}
#endif

