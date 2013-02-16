#ifndef PORT_TYPES_H
#define PORT_TYPES_H

typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} DigitalOut;

typedef struct {
	uint32_t port;		// Endereco base da porta
	uint32_t pinnum;	// Numero do pino (0 a 31)
} DigitalIn;

typedef struct {
	uint32_t uart;		// Endereco base da UART
	uint32_t baudrate;	// Baudrate
	uint8_t wordsize;	// 8, 7, 6 ou 5 bits
	uint8_t parity;		// N, 1 ou 2 bits de paridade
	uint8_t stopbits;	// 1 ou 2 stop bits
} USART;

#endif

