/*
 * uart.c
 * Func√µes para objeto UART
 * Author: David Alain do Nascimento
 * Version STM32F407xx 0.1
 * Date: 16/02/2013
 * Copyright: Crist√≥v√£o e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <uart.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>

#define IS_PARITY_VALID(parity)			((parity == PAR_NONE) || (parity == PAR_ODD) || (parity == PAR_EVEN))
#define IS_STOP_BITS_VALID(stopbits)	((stopbits == 1) || (stopbits == 2))

/* Usado pela API da ST na configuraÁ„o da USART*/
static USART_InitTypeDef USART_InitStruct;


void uart_setup (uart_t *uart, void* uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits) {

	if(uart == NULL)
		return;

	uart->uart = uart_num;  // Necess·rio setar a UART para que as funÁıes
	// abaixo saibam onde ir para configurar as coisas

	USART_InitStruct.USART_BaudRate = baud;

	switch(wordsize){
	case 8:		USART_InitStruct.USART_WordLength = USART_WordLength_8b;	break;
	case 9:		USART_InitStruct.USART_WordLength = USART_WordLength_9b;	break;
	default:	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	break; //evita erros de confuraÁ„o
	}

	switch(stopbits){
	case 1:		USART_InitStruct.USART_StopBits = USART_StopBits_1;		break;
	case 2:		USART_InitStruct.USART_StopBits = USART_StopBits_2;		break;
	default:	USART_InitStruct.USART_StopBits = USART_StopBits_1;		break; //evita erros de confuraÁ„o
	}

	switch(parity){
	case PAR_NONE:	USART_InitStruct.USART_Parity = USART_Parity_No;	break;
	case PAR_ODD:	USART_InitStruct.USART_Parity = USART_Parity_Odd;	break;
	case PAR_EVEN:	USART_InitStruct.USART_Parity = USART_Parity_Even;	break;
	default:		USART_InitStruct.USART_Parity = USART_Parity_No;	break; //evita erros de confuraÁ„o
	}

	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //N„o usa controle de fluxo, implica funcionar como UART

	USART_Init((uint32_t*)uart_num , &USART_InitStruct);

}

void uart_set_baud (uart_t *uart, uint32_t baud) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	USART_InitStruct.USART_BaudRate = baud;

	USART_Init((uint32_t*)usart_typedef , &USART_InitStruct);
}

void uart_set_wordsize (uart_t *uart, uint32_t wordsize) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	switch(wordsize){
	case 8:		USART_InitStruct.USART_WordLength = USART_WordLength_8b;	break;
	case 9:		USART_InitStruct.USART_WordLength = USART_WordLength_9b;	break;
	default:	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	break; //evita erros de confuraÁ„o
	}

	USART_Init((uint32_t*)usart_typedef , &USART_InitStruct);
}

void uart_set_parity (uart_t *uart, uint32_t parity) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	switch(parity){
	case PAR_NONE:	USART_InitStruct.USART_Parity = USART_Parity_No;	break;
	case PAR_ODD:	USART_InitStruct.USART_Parity = USART_Parity_Odd;	break;
	case PAR_EVEN:	USART_InitStruct.USART_Parity = USART_Parity_Even;	break;
	default:		USART_InitStruct.USART_Parity = USART_Parity_No;	break; //evita erros de confuraÁ„o
	}

	USART_Init((uint32_t*)usart_typedef , &USART_InitStruct);
}

void uart_set_stopbits (uart_t *uart, uint32_t stopbits) {

	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	switch(stopbits){
	case 1:		USART_InitStruct.USART_StopBits = USART_StopBits_1;		break;
	case 2:		USART_InitStruct.USART_StopBits = USART_StopBits_2;		break;
	default:	USART_InitStruct.USART_StopBits = USART_StopBits_1;		break; //evita erros de confuraÁ„o
	}

	USART_Init((uint32_t*)usart_typedef , &USART_InitStruct);
}

uint32_t uart_write (const uart_t *uart, const uint8_t *data, uint32_t length) {

	uint32_t i;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

    for(i = 0 ; i < length ; i++){
        while(USART_GetFlagStatus(usart_typedef, USART_FLAG_TXE) == RESET);
        USART_SendData(usart_typedef, data[i]);
    }

	return i;
}

uint32_t uart_read (const uart_t *uart, uint8_t *data, uint32_t length) {

	uint32_t i;
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;

	for(i = 0 ; i < length ; i++){

		if(USART_GetITStatus( usart_typedef, USART_IT_RXNE ) == SET){
			data[i] = USART_ReceiveData( usart_typedef );
		}else{
			break;
		}
	}

	return i;
}

uint32_t uart_data_available (const uart_t *uart) {
	USART_TypeDef *usart_typedef = (USART_TypeDef *)uart->uart;
	return (USART_GetITStatus( usart_typedef, USART_IT_RXNE ) == SET);
}

#ifdef __cplusplus
}
#endif
