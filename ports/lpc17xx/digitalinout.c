/*
 * digitalinout.c
 * Funcões para objetos DigitalIn e DigitalOut
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 16/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <DigitalIn.h>
#include <DigitalOut.h>

#include <LPC17xx.h>

static struct _pin {
	uint32_t port;
	uint32_t pinnum;
};

inline static void digital_general_setup (void *pin, uint32_t portnum, uint32_t pinnum) {
	((struct _pin *)pin)->port = portnum;
	((struct _pin *)pin)->pinnum = pinnum;

	switch (portnum) {	// Reconfigura os registradores dos pinos em PINCON
		case LPC_GPIO0_BASE:
			if (pinnum < 16) {
				LPC_PINCON->PINSEL0 &= ~(0x03 << (pinnum * 2));	// PINSELn = Seleciona o tipo do pino: 00 = GPIO
				LPC_PINCON->PINMODE0 &= ~(0x3 << (pinnum * 2));	// PINMODEn = Seleciona tipo de resistor: 00 = Pull-down
			} else {
				LPC_PINCON->PINSEL1 &= ~(0x03 << ((pinnum - 16) * 2));
				LPC_PINCON->PINMODE1 &= ~(0x03 << ((pinnum - 16) * 2));
			}
			break;
		case LPC_GPIO1_BASE:
			if (pinnum < 16) {
				LPC_PINCON->PINSEL2 &= ~(0x03 << (pinnum * 2));
				LPC_PINCON->PINMODE2 &= ~(0x03 << (pinnum * 2));
			} else {
				LPC_PINCON->PINSEL3 &= ~(0x03 << ((pinnum - 16) * 2));
				LPC_PINCON->PINMODE3 &= ~(0x03 << ((pinnum - 16) * 2));
			}
			break;
		case LPC_GPIO2_BASE:
			LPC_PINCON->PINSEL4 &= ~(0x3 << (pinnum * 2));
			LPC_PINCON->PINMODE4 &= ~(0x3 << (pinnum * 2));
			break;
		case LPC_GPIO3_BASE:
			LPC_PINCON->PINSEL7 &= ~(0x3 << ((pinnum - 16) * 2));
			LPC_PINCON->PINMODE7 &= ~(0x3 << ((pinnum - 16) * 2));
			break;
		case LPC_GPIO4_BASE:
			LPC_PINCON->PINSEL9 &= ~(0x3 << ((pinnum - 16) * 2));
			LPC_PINCON->PINMODE9 &= ~(0x3 << ((pinnum - 16) * 2));
			break;
		default:
			// TODO: Invoke a hard-fault function or so
			break;
	}
}

static inline uint32_t digital_generic_read (const void *pin) {
	LPC_GPIO_TypeDef *port = (LPC_GPIO_TypeDef *)((struct _pin *)pin)->port;

	if (port->FIOPIN & (1 << ((struct _pin *)pin)->pinnum))
		return 1;
	else
		return 0;
}

void digitalin_setup (DigitalIn *pin, uint32_t portnum, uint32_t pinnum) {
	LPC_GPIO_TypeDef *l_port = (LPC_GPIO_TypeDef *)portnum;

	digital_general_setup (pin, portnum, pinnum);

	l_port->FIODIR &= ~(1 << pinnum);
	l_port->FIOMASK &= ~(1 << pinnum);
}

uint32_t digitalin_read (const DigitalOut *pin) {
	return digital_generic_read(pin);
}

void digitalout_setup (DigitalOut *pin, uint32_t portnum, uint32_t pinnum) {
	LPC_GPIO_TypeDef *l_port = (LPC_GPIO_TypeDef *)portnum;

	digital_general_setup (pin, portnum, pinnum);

	l_port->FIODIR |= (1 << pinnum);
	l_port->FIOMASK &= ~(1 << pinnum);
}

void digitalout_write (const DigitalOut *pin, uint32_t value) {
	LPC_GPIO_TypeDef *port = (LPC_GPIO_TypeDef *)pin->port;

	if (value)
		port->FIOSET = 1 << pin->pinnum;
	else
		port->FIOCLR = 1 << pin->pinnum;
}

uint32_t digitalout_read (const DigitalOut *pin) {
	return digital_generic_read(pin);
}

#ifdef __cplusplus
}
#endif

