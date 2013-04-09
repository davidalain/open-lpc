#ifndef OPENLPC_UART_H
#define OPENLPC_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file uart.h
 * Tipo para interface RS-232 (serial)
 * \details Contém funções para configurar e utilizar uma porta serial RS-232
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 15/02/2013
 * \copyright Cristóvão e David
 */

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
void uart_setup (uart_t *uart, void* uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits);

/*!
 * \fn void uart_set_baud (uart_t *uart, uint32_t baud)
 * \brief Configura somente o baud rate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo valor do baud rate
 */
void uart_set_baud (uart_t *uart, uint32_t baud);

/*!
 * \fn void uart_set_wordsize (uart_t *uart, uint32_t wordsize)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo valor do tamanho da palavra da serial
 */
void uart_set_wordsize (uart_t *uart, uint32_t wordsize);

/*!
 * \fn void uart_set_parity (uart_t *uart, uint32_t parity)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Nova paridade: PAR_NONE, PAR_ODD ou PAR_EVEN
 */
void uart_set_parity (uart_t *uart, uint32_t parity);

/*!
 * \fn void uart_set_stopbits (uart_t *uart, uint32_t stopbits)
 * \brief Configura somente o baudrate
 * \param uart Ponteiro para estrutura uart_t
 * \param baud Novo número de stop bits
 */
void uart_set_stopbits (uart_t *uart, uint32_t stopbits);

/*!
 * \fn uint32_t uart_write (const uart_t *uart, const uint8_t *data, uint32_t length)
 * \brief Escreve vários bytes pela porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t uart_write (const uart_t *uart, const uint8_t *data, uint32_t length);

/*!
 * \fn void uart_read (const uart_t *uart)
 * \brief Lê vários bytes da porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t uart_read (const uart_t *uart, uint8_t *data, uint32_t length);

/*!
 * \fn void uart_data_available (const uart_t *uart)
 * \brief Retorna se há algum byte para ser lido pela porta serial
 * \param uart Ponteiro para estrutura uart_t
 * \returns 0 (zero) caso não haja. Diferente de zero se houver
 */
uint32_t uart_data_available (const uart_t *uart);

/*! 
 * \def PARITY_NONE
 * Define transmissão sem paridade. Equivalente ao valor 0 (zero)
 */
#define PARITY_NONE 0
/*! 
 * \def PARITY_ODD
 * Define transmissão com paridade ímpar. Equivalente ao valor 1 (um)
 */
#define PARITY_ODD 1
/*! 
 * \def PARITY_EVEN
 * Define transmissão com paridade par. Equivalente ao valor 2 (dois)
 */
#define PARITY_EVEN 2

#ifdef __cplusplus
}
#endif

#endif
