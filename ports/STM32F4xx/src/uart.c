/*
 * uart.c
 * FuncÃµes para objeto UART
 * Author: David Alain do Nascimento
 * Co-Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 * Version STM32F407xx 0.1
 * Date: 16/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <UART.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>
#include <misc.h>

static const uint32_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

void uart_setup (uart_t *uart, void* uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits) {

	uart->uart = uart_num;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart_num;

	// Ativar o clock da UART e configuração de pinos de IO para USART
	switch ((uint32_t)uart_num) {
	case USART1_BASE:
		RCC->APB2ENR |= (1 << 4);	// Ativa o Clock da UART
		RCC->AHB1ENR |= (1 << 1);	// Ativa o Clock do GPIO

		GPIOB->MODER &= ~(1 << 12);	// PB6 - Alternate Function
		GPIOB->MODER |= (1 << 13);	// PB6 - Alternate Function
		GPIOB->AFR[0] &= ~(0x0F << 24);	// Configura o PB6 como TX
		GPIOB->AFR[0] |= (0x07 << 24);

		GPIOB->MODER &= ~(1 << 14);	// PB7 - Alternate Function
		GPIOB->MODER |= (1 << 15);	// PB7 - Alternate Function
		GPIOB->AFR[0] &= ~(0x0F << 28);	// Configura o PB7 como RX
		GPIOB->AFR[0] |= (0x07 << 28);

		break;
	case USART2_BASE:
		RCC->APB1ENR |= (1 << 17);
		break;
	case USART3_BASE:
		RCC->APB1ENR |= (1 << 18);
		break;
	case UART4_BASE:
		RCC->APB1ENR |= (1 << 19);
		break;
	case UART5_BASE:
		RCC->APB1ENR |= (1 << 20);
		break;
	case USART6_BASE:
		RCC->APB2ENR |= (1 << 5);
		break;
	default:
		return;	// TODO: Chamar um hardfault, talvez?
	}

	// Ativando a USART, o TX e o RX
	usart_typedef->CR1 |= ((1 << 13) | (1 << 3) | (1 << 2));

	uart_set_baud (uart, baud);
	uart_set_wordsize (uart, wordsize);
	uart_set_parity (uart, parity);
	uart_set_stopbits (uart, stopbits);
}

void uart_set_baud (uart_t *uart, uint32_t baud) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	uint32_t pclk = 0, mantissa, frac;

	switch ((uint32_t)uart->uart) {
		case USART1_BASE:
		case USART6_BASE:
			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 13)) >> 13];	// CFGR [15:13] são o Prescaler 2
			break;

		case USART2_BASE:
		case USART3_BASE:
		case UART4_BASE:
		case UART5_BASE:
			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 10)) >> 10];	// CFGR [12:10] são o Prescaler 1
			break;

		default:
			break;	// TODO: Hardfault?
	}

	mantissa = pclk / (16 * baud);
	usart_typedef->BRR = ((mantissa & 0xFFF) << 4);	// TODO: Colocar aqui a parte fracionária
}


void uart_set_wordsize (uart_t *uart, uint32_t wordsize) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	switch (wordsize) {
		case 9:
			usart_typedef->CR1 |= (1 << 12);
			break;
		case 8:
		default:
			usart_typedef->CR1 &= ~(1 << 12);
			break;	// TODO: Considerar chamar um hardfault com wordsize diferente de 9 e 8?
	}
}

void uart_set_parity (uart_t *uart, uint32_t parity) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	switch (parity) {
		case PARITY_NONE:
			usart_typedef->CR1 &= ~(1 << 10);
			break;
		case PARITY_ODD:
			usart_typedef->CR1 |= (1 << 10);
			usart_typedef->CR1 |= (1 << 9);
			break;
		case PARITY_EVEN:
			usart_typedef->CR1 |= (1 << 10);
			usart_typedef->CR1 &= ~(1 << 9);
			break;
		default:
			break;	// TODO: Hardfault?
	}
}

void uart_set_stopbits (uart_t *uart, uint32_t stopbits) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	switch (stopbits) {
		case 1:
			usart_typedef->CR2 &= (~(1 << 13) & ~(1 << 12));
			break;
		case 2:
			usart_typedef->CR2 |= (1 << 13);
			usart_typedef->CR2 &= ~(1 << 12);
			break;
		default:
			break;	// TODO: Hardfault?
	}
}

uint32_t uart_write (const uart_t *uart, const uint8_t *data, uint32_t length) {

	uint32_t i;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	for (i = 0; i < length; i++) {
		while ((usart_typedef->SR & (1 << 6)) == 0) ; // Espera terminar de enviar
		usart_typedef->DR = data[i];
	}

	return i;
}

uint32_t uart_read (const uart_t *uart, uint8_t *data, uint32_t length) {

	uint32_t i;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	for (i = 0; i < length; i++) {
		if (usart_typedef->SR & (1 << 5))
			data[i] = (usart_typedef->DR & 0xFF);	// Ignorar o bit de paridade
		else
			break;
		
	}

	return i;
}

uint32_t uart_data_available (const uart_t *uart) {
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	return (usart_typedef->SR & (1 << 5));
}

#ifdef __cplusplus
}
#endif

