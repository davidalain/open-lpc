#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/*
 * port_types.h
 * Tipos definidos para cada arquitetura
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// TODO: Talvez juntar DigitalOut e DigitalIn na mesma estrutura?
typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} digitalout_t;

typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} digitalin_t;

typedef struct {
	uint32_t uart;		// Endereco base da UART
	uint32_t baudrate;	// Baudrate
	uint8_t wordsize;	// 8, 7, 6 ou 5 bits
	uint8_t parity;		// N, 1 ou 2 bits de paridade
	uint8_t stopbits;	// 1 ou 2 stop bits
} uart_t;

typedef struct {
	uint32_t i2c;
} i2cmaster_t;

typedef struct {
	uint32_t spi;
	uint32_t freq;
} spi_t;

typedef struct {
	uint32_t pwm;
	uint32_t freq;
} pwm_t;

typedef struct {
	uint32_t timer;
	uint32_t prescaler;
	uint32_t div;
	uint32_t clksel;
} timer_t;

#ifdef __cplusplus
}
#endif

#endif
