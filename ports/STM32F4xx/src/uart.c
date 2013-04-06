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

static const uint32_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

static void enable_uart1 (void) {
    RCC->AHB1ENR |= (1 << 1);	// Ativa o Clock do GPIO

    GPIOB->MODER &= ~(1 << 12);	// PB6 - Alternate Function
    GPIOB->MODER |= (1 << 13);	// PB6 - Alternate Function
    GPIOB->AFR[0] &= ~(0x0F << 24);	// Configura o PB6 como TX
    GPIOB->AFR[0] |= (0x07 << 24);

    GPIOB->MODER &= ~(1 << 14);	// PB7 - Alternate Function
    GPIOB->MODER |= (1 << 15);	// PB7 - Alternate Function
    GPIOB->AFR[0] &= ~(0x0F << 28);	// Configura o PB7 como RX
    GPIOB->AFR[0] |= (0x07 << 28);
}

static void enable_uart2 (void) {
    RCC->AHB1ENR |= (1 << 0);	// Ativa o Clock do GPIO

    GPIOA->MODER &= ~(1 << 4);	// PA2 - Alternate Function
    GPIOA->MODER |= (1 << 5);	// PA2 - Alternate Function
    GPIOA->AFR[0] &= ~(0x0F << 8);	// Configura o PA2 como TX
    GPIOA->AFR[0] |= (0x07 << 8);

    GPIOA->MODER &= ~(1 << 6);	// PA3 - Alternate Function
    GPIOA->MODER |= (1 << 7);	// PA3 - Alternate Function
    GPIOA->AFR[0] &= ~(0x0F << 12);	// Configura o PA3 como RX
    GPIOA->AFR[0] |= (0x07 << 12);
}

static void enable_uart3 (void) {
    RCC->AHB1ENR |= (1 << 2);	// Ativa o Clock do GPIO

    GPIOC->MODER &= ~(1 << 20);	// PC10 - Alternate Function
    GPIOC->MODER |= (1 << 21);	// PC10 - Alternate Function
    GPIOC->AFR[1] &= ~(0x0F << 8);	// Configura o PC10 como TX
    GPIOC->AFR[1] |= (0x07 << 8);

    GPIOC->MODER &= ~(1 << 22);	// PC11 - Alternate Function
    GPIOC->MODER |= (1 << 23);	// PC11 - Alternate Function
    GPIOC->AFR[1] &= ~(0x0F << 12);	// Configura o PC11 como RX
    GPIOC->AFR[1] |= (0x07 << 12);
}

static void enable_uart4 (void) {
    RCC->AHB1ENR |= (1 << 0);	// Ativa o Clock do GPIO

    GPIOA->MODER &= ~(1 << 0);	// PA0 - Alternate Function
    GPIOA->MODER |= (1 << 1);	// PA0 - Alternate Function
    GPIOA->AFR[0] &= ~(0x0F << 0);	// Configura o PA0 como TX
    GPIOA->AFR[0] |= (0x08 << 0);

    GPIOA->MODER &= ~(1 << 2);	// PA1 - Alternate Function
    GPIOA->MODER |= (1 << 3);	// PA1 - Alternate Function
    GPIOA->AFR[0] &= ~(0x0F << 1);	// Configura o PA1 como RX
    GPIOA->AFR[0] |= (0x08 << 1);
}

static void enable_uart5 (void) {
    RCC->AHB1ENR |= (1 << 2);	// Ativa o Clock do GPIO
    RCC->AHB1ENR |= (1 << 3);	// Ativa o Clock do GPIO

    GPIOC->MODER &= ~(1 << 24);	// PC12 - Alternate Function
    GPIOC->MODER |= (1 << 25);	// PC12 - Alternate Function
    GPIOC->AFR[1] &= ~(0x0F << 16);	// Configura o PC12 como TX
    GPIOC->AFR[1] |= (0x08 << 16);

    GPIOD->MODER &= ~(1 << 4);	// PD2 - Alternate Function
    GPIOD->MODER |= (1 << 5);	// PD2 - Alternate Function
    GPIOD->AFR[0] &= ~(0x0F << 8);	// Configura o PD2 como RX
    GPIOD->AFR[0] |= (0x08 << 8);
}

static void enable_uart6 (void) {
    RCC->AHB1ENR |= (1 << 1);	// Ativa o Clock do GPIO

    GPIOB->MODER &= ~(1 << 12);	// PB6 - Alternate Function
    GPIOB->MODER |= (1 << 13);	// PB6 - Alternate Function
    GPIOB->AFR[0] &= ~(0x0F << 24);	// Configura o PB6 como TX
    GPIOB->AFR[0] |= (0x07 << 24);

    GPIOB->MODER &= ~(1 << 14);	// PB7 - Alternate Function
    GPIOB->MODER |= (1 << 15);	// PB7 - Alternate Function
    GPIOB->AFR[0] &= ~(0x0F << 28);	// Configura o PB7 como RX
    GPIOB->AFR[0] |= (0x07 << 28);
}

void uart_setup (uart_t *uart, void* uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits) {

	uart->uart = uart_num;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart_num;

	// Ativar o clock da UART e configuração de pinos de IO para USART
	switch ((uint32_t)uart_num) {
	case USART1_BASE:
		RCC->APB2ENR |= (1 << 4);	// Ativa o Clock da UART
        enable_uart1();
		break;
	case USART2_BASE:
		RCC->APB1ENR |= (1 << 17);
        enable_uart2();
		break;
	case USART3_BASE:
		RCC->APB1ENR |= (1 << 18);
        enable_uart3();
		break;
	case UART4_BASE:
		RCC->APB1ENR |= (1 << 19);
        enable_uart4();
		break;
	case UART5_BASE:
		RCC->APB1ENR |= (1 << 20);
        enable_uart5();
		break;
	case USART6_BASE:
		RCC->APB2ENR |= (1 << 5);
        enable_uart6();
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
	uint32_t pclk = 0, mantissa;

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
    uart->baudrate = baud;
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

    uart->wordsize = wordsize;
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

    uart->parity = parity;
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

    uart->stopbits = stopbits;
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

