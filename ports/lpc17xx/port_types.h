#ifndef PORT_TYPES_H
#define PORT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// TODO: Talvez juntar DigitalOut e DigitalIn na mesma estrutura?
typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} DigitalOut;

typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} DigitalIn;

typedef struct {
	uint32_t usart;		// Endereco base da UART
	uint32_t baudrate;	// Baudrate
	uint8_t wordsize;	// 8, 7, 6 ou 5 bits
	uint8_t parity;		// N, 1 ou 2 bits de paridade
	uint8_t stopbits;	// 1 ou 2 stop bits
} USART;

#ifdef __cplusplus
}
#endif

#endif

