#ifndef OPENLPC_PORT_TYPES_H
#define OPENLPC_PORT_TYPES_H

/*
 * port_types.h
 * Tipos definidos para cada arquitetura
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
	void* port;			// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} digital_io_t;

typedef struct {
	void* port;			// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} analog_io_t;

typedef struct {
	void* uart;			// Endereco base da UART
	uint32_t baudrate;	// Baudrate
	uint8_t wordsize;	// 9, 8, 7, 6 ou 5 bits
	uint8_t parity;		// N, 1 ou 2 bits de paridade
	uint8_t stopbits;	// 1 ou 2 stop bits
} uart_t;

typedef struct {
	void* i2c;
	uint32_t freq;
} i2cmaster_t;

typedef struct {
	void* spi;
	uint32_t freq;
} spi_t;

typedef struct {
	void* pwm;
	uint32_t freq;
	uint32_t channel;
} pwm_t;

typedef struct {
	void* timer;
	uint32_t prescaler;
	uint32_t div;
	uint32_t clksel;
} timer_t;

typedef struct {
	void *counter;
	uint32_t div;
} counter_t;

#ifdef __cplusplus
}
#endif

#endif

