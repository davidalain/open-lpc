/*
 * usart.c
 * Funcões para objeto USART
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 16/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <USART.h>
#include <LPC17xx.h>
#include <system_LPC17xx.h>

static void usart_calculate_parameters (uint32_t baudrate, uint16_t *dl, 
                                        uint8_t *divaddval, uint8_t *mulval) {

	uint32_t a, b, c;
	
	// SystemCoreClock possui o clock do microcontrolador
	if (SystemCoreClock % (baudrate * 16) == 0) { // Melhor caso: o baudrate é mútiplo
		*dl = SystemCoreClock / (baudrate * 16);  // do clock principal
		*divaddval = 0;
		*mulval = 1;
		return ;
	}

	a = baudrate;
	b = SystemCoreClock % baudrate;

	// Calcula o MDC entre o baudrate e o resto da divisão entre o clock e o baudrate
	// a saída está em 'b'
	for (;;) {
		if (a % b == 0) break;
		c = a % b;
		a = b;
		b = c;
	}

	*dl = SystemCoreClock / (baudrate * 16);
	*divaddval = *dl % b;
	*mulval = baudrate % b;
}
	
void usart_setup (USART *usart, uint32_t usart_num, 
                  uint32_t baud, uint32_t wordsize, 
                  uint32_t parity, uint32_t stopbits) {

	usart->usart = usart_num;   // Necessário setar a USART para que as funções 
								// abaixo saibam onde ir para configurar as coisas

	switch (usart_num) {
		case LPC_UART0_BASE:
			LPC_SC->PCONP |= (1 << 3); // Ativa a porta serial (obs: já vem ativa por default) 
			LPC_PINCON->PINSEL0 &= ~(0x02 << 4);
			LPC_PINCON->PINSEL0 |= (0x01 << 4); // Seleciona GPIO0.2 como TXD
			LPC_PINCON->PINMODE0 &= ~(0x03 << 6); // Garante que o RXD está sem resistor de pull-down
			LPC_PINCON->PINSEL0 &= ~(0x02 << 6);
			LPC_PINCON->PINSEL0 |= (0x01 << 6); // Seleciona GPIO0.3 como RXD
			break;

		case LPC_UART1_BASE:
			LPC_SC->PCONP |= (1 << 4); // Ativa a porta serial (obs: já vem ativa por default)
			break;

		case LPC_UART2_BASE:
			LPC_SC->PCONP |= (1 << 24);
			break;

		case LPC_UART3_BASE:
			LPC_SC->PCONP |= (1 << 25);
			break;

		default:
			// TODO: Call some hardfault?
			return ;
	};

	usart_set_baud (usart, baud);
	usart_set_wordsize (usart, wordsize);
	usart_set_baud (usart, baud);
	usart_set_parity (usart, parity);
	usart_set_stopbits (usart, stopbits);
	
}

void usart_set_baud (USART *usart, uint32_t baud) {
	uint16_t dl;
	uint8_t divaddval, mulval;
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;

	usart_calculate_parameters (baud, &dl, &divaddval, &mulval);
	
	l_usart->LCR |= (1 << 7);  // DLAB = 1
	l_usart->DLL = (dl & 0x00FF);
	l_usart->DLM = ((dl & 0xFF00) >> 8);
	l_usart->LCR &= ~(1 << 7); // DLAB = 0
	l_usart->FDR = ((mulval & 0x0F) << 4) | (divaddval & 0x0F);
}

void usart_set_wordsize (USART *usart, uint32_t wordsize) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;
	
	switch (wordsize) {
		case 5:
			l_usart->LCR &= ~(0x03 << 0);
			break;
			
		case 6:
			l_usart->LCR &= ~(0x02 << 0);
			l_usart->LCR |= (0x01 << 0);
			break;
			
		case 7:
			l_usart->LCR &= ~(0x01 << 0);
			l_usart->LCR |= (0x02 << 0);
			break;
			
		case 8:
		default:
			l_usart->LCR |= (0x03 << 0);
			break;
	}
}

void usart_set_parity (USART *usart, uint32_t parity) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;

	switch (parity) {
		case PAR_ODD:
			l_usart->LCR |= (1 << 3); // Ativa a geração de paridade
			l_usart->LCR &= ~(0x03 << 4); // Ativa paridade ímpar
			break;

		case PAR_EVEN:
			l_usart->LCR |= (1 << 3);
			l_usart->LCR |= (0x01 << 4);
			break;

		case PAR_NONE:
		default:
			l_usart->LCR &= ~(1 << 3); // Desliga geração de paridade
			break;
	}
}

void usart_set_stopbits (USART *usart, uint32_t stopbits) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;

	switch (stopbits) {
		case 2:
			l_usart->LCR |= (1 << 2);
			break;
			
		default:
		case 1:
			l_usart->LCR &= ~(1 << 2);
			break;
	}
}

void usart_write (const USART *usart, uint8_t byte) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;
	while ((l_usart->LSR & (1 << 6)) == 0); // OBS: Aguarda até a transmissão
	l_usart->THR = byte;
}

uint8_t usart_read (const USART *usart) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;
	return l_usart->RBR;	// OBS: Não há espera para ver se há dado válido
}

uint32_t usart_data_available (const USART *usart) {
	LPC_UART_TypeDef *l_usart = (LPC_UART_TypeDef *)usart->usart;
	return (l_usart->LSR & 0x01);
}

#ifdef __cplusplus
}
#endif