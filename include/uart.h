/*!
 * \file uart.h
 * Tipo para interface RS-232 (serial)
 * \details ContÃ©m funÃ§Ãµes para configurar e utilizar uma porta serial RS-232
 * \author CristÃ³vÃ£o Zuppardo Rufino
 * \version 0.1
 * \date 15/02/2013
 * \copyright CristÃ³vÃ£o e David
 */

#ifndef OPENLPC_UART_H
#define OPENLPC_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <port_types.h>
#include <stdint.h>

/*!
 * \struct uart_t
 * \brief Define um tipo serial RS-232. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void uart_setup (uart_t *uart, uint32_t uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits)
 * \brief Configura uma porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \param uart_num Número da porta a ser utilizada
 * \param baud Baud rate da porta
 * \param wordsize Tamanho da palavra da serial: 5, 6, 7 ou 8 bits
 * \param parity Paridade da porta serial: PAR_NONE, PAR_ODD, PAR_EVEN
 * \param stopbits Número de stopbits: 1 ou 2
 */
void uart_setup(uart_t *uart, void* uart_num, uint32_t baud, uint32_t wordsize,
		uint32_t parity, uint32_t stopbits);

/*!
 * \fn void uart_set_baud (uart_t *uart, uint32_t baud)
 * \brief Configura somente o baud rate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo valor do baud rate
 */
void uart_set_baud(uart_t *uart, uint32_t baud);

/*!
 * \fn void uart_set_wordsize (uart_t *uart, uint32_t wordsize)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo valor do tamanho da palavra da serial
 */
void uart_set_wordsize(uart_t *uart, uint32_t wordsize);

/*!
 * \fn void uart_set_parity (uart_t *uart, uint32_t parity)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Nova paridade: PAR_NONE, PAR_ODD ou PAR_EVEN
 */
void uart_set_parity(uart_t *uart, uint32_t parity);

/*!
 * \fn void uart_set_stopbits (uart_t *uart, uint32_t stopbits)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo número de stop bits
 */
void uart_set_stopbits(uart_t *uart, uint32_t stopbits);

/*!
 * \fn uint32_t uart_write (const uart_t *uart, const uint8_t *data, uint32_t length)
 * \brief Escreve vários bytes pela porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t uart_write(const uart_t *uart, const uint8_t *data, uint32_t length);

/*!
 * \fn void uart_read (const uart_t *uart)
 * \brief Lê vários bytes da porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t uart_read(const uart_t *uart, uint8_t *data, uint32_t length);

/*!
 * \fn void uart_data_available (const uart_t *uart)
 * \brief Retorna se há algum byte para ser lido pela porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \returns 0 (zero) caso não haja. Diferente de zero se houver
 */
uint32_t uart_data_available(const uart_t *uart);

/*!
 * \fn void uart_set_rx_interrupt (const uart_t *uart, void (*interrupt)(void))
 * \brief Configura a função dada por 'interrupt' como interrupção de recepçao de dados pela serial
 * \param uart Ponteiro para estrutura uart_t
 * \param interrupt Ponteiro de função que deve ser chamado quando houver uma interrupção na serial dada por 'uart->uart'
 */
void uart_set_interrupt_handler(const uart_t *uart, void (*interrupt)(void));

/**
 * @fn void uart_disable_interrupt(const uart_t *uart, uint16_t usart_it)
 * @brief Desabilita a interrupção dada por @arg usart_it
 * @param uart Ponteiro para estrutura uart_t
 * @param usart_int Iterrupção a ser desabilitada
 * 		Esse parâmetro pode ser um dos seguintes valores:
 *            @arg UART_INT_CTS:  Interrupção de mudança no CTS (CTS)
 *            @arg UART_INT_LBD:  Interrupção de detecção de parada na linha (Line Break Detection)
 *            @arg UART_INT_TXE:  Interrupção de registrador de transmissão de dados vazio (Transmit Data Register Empty)
 *            @arg UART_INT_TC:   Interrupção de transmissão completa (Transmission Complete)
 *            @arg UART_INT_RXNE: Interrupção de registrador de recepção de dados vazio (Receive Data Register Not Empty)
 *            @arg UART_INT_IDLE: Interrupção de detecção de linha ociosa (Idle Line Detection)
 *            @arg UART_INT_PE:   Interrupção de erro de paridade (Parity Error)
 *            @arg UART_INT_ERR:  Interrupção de erro (Frame error, noise error, overrun error)
 */
void uart_disable_interrupt(const uart_t *uart, uint16_t usart_int);

/**
 * @fn void uart_disable_interrupt(const uart_t *uart, uint16_t usart_it)
 * @brief Habilita a interrupção dada por @arg usart_it
 * @param uart Ponteiro para estrutura uart_t
 * @param usart_int Iterrupção a ser habilitada
 * 		Esse parâmetro pode ser um dos seguintes valores:
 *            @arg UART_INT_CTS:  Interrupção de mudança no CTS (CTS)
 *            @arg UART_INT_LBD:  Interrupção de detecção de parada na linha (Line Break Detection)
 *            @arg UART_INT_TXE:  Interrupção de registrador de transmissão de dados vazio (Transmit Data Register Empty)
 *            @arg UART_INT_TC:   Interrupção de transmissão completa (Transmission Complete)
 *            @arg UART_INT_RXNE: Interrupção de registrador de recepção de dados vazio (Receive Data Register Not Empty)
 *            @arg UART_INT_IDLE: Interrupção de detecção de linha ociosa (Idle Line Detection)
 *            @arg UART_INT_PE:   Interrupção de erro de paridade (Parity Error)
 *            @arg UART_INT_ERR:  Interrupção de erro (Frame error, noise error, overrun error)
 */
void uart_enable_interrupt(const uart_t *uart, uint16_t usart_int);

/*! 
 * \def PARITY_NONE
 * Define transmissÃ£o sem paridade. Equivalente ao valor 0 (zero)
 */
#define PARITY_NONE 0
/*! 
 * \def PARITY_ODD
 * Define transmissÃ£o com paridade Ã­mpar. Equivalente ao valor 1 (um)
 */
#define PARITY_ODD 1
/*! 
 * \def PARITY_EVEN
 * Define transmissÃ£o com paridade par. Equivalente ao valor 2 (dois)
 */
#define PARITY_EVEN 2


#define UART_INT_REG(CRx, BitIndex)		((uint16_t)((CRx << 0x5) | BitIndex))

#define UART_INT_PE				UART_INT_REG(0x1, 0x08)
#define UART_INT_TXE			UART_INT_REG(0x1, 0x07)
#define UART_INT_TC				UART_INT_REG(0x1, 0x06)
#define UART_INT_RXNE			UART_INT_REG(0x1, 0x05)
#define UART_INT_IDLE			UART_INT_REG(0x1, 0x04)

#define UART_INT_LBD			UART_INT_REG(0x2, 0x04)

#define UART_INT_CTS			UART_INT_REG(0x3, 0x0A)
#define UART_INT_ERR			UART_INT_REG(0x3, 0x00)


#ifdef __cplusplus
}
#endif

#endif

