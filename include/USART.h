#ifndef USART_H
#define USART_H

/*!
 * \file USART.h
 * Tipo para interface RS-232 (serial)
 * \details Contém funções para configurar e utilizar uma porta serial RS-232
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 15/02/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>

/*!
 * \struct USART
 * \brief Define um tipo serial RS-232. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void usart_setup (USART &usart, uint32_t usart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits)
 * \brief Configura uma porta serial
 * \param usart Ponteiro para estrutura USART
 * \param usart_num Número da porta a ser utilizada
 * \param baud Baud rate da porta
 * \param wordsize Tamanho da palavra da serial: 5, 6, 7 ou 8 bits
 * \param parity Paridade da porta serial: PAR_NONE, PAR_ODD, PAR_EVEN
 * \param stopbits Número de stopbits: 1 ou 2
 */
void usart_setup (USART &usart, uint32_t usart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits);

/*!
 * \fn void usart_set_baud (USART &usart, uint32_t baud)
 * \brief Configura somente o baud rate
 * \param usart Ponteiro para estrutura USART
 * \param baud Novo valor do baud rate
 */
void usart_set_baud (USART &usart, uint32_t baud);

/*!
 * \fn void usart_set_wordsize (USART &usart, uint32_t wordsize)
 * \brief Configura somente o baudrate
 * \param usart Ponteiro para estrutura USART
 * \param baud Novo valor do tamanho da palavra da serial
 */
void usart_set_wordsize (USART &usart, uint32_t wordsize);

/*!
 * \fn void usart_set_parity (USART &usart, uint32_t parity)
 * \brief Configura somente o baudrate
 * \param usart Ponteiro para estrutura USART
 * \param baud Nova paridade: PAR_NONE, PAR_ODD ou PAR_EVEN
 */
void usart_set_parity (USART &usart, uint32_t parity);

/*!
 * \fn void usart_set_stopbits (USART &usart, uint32_t stopbits)
 * \brief Configura somente o baudrate
 * \param usart Ponteiro para estrutura USART
 * \param baud Novo número de stop bits
 */
void usart_set_stopbits (USART &usart, uint32_t stopbits);

/*!
 * \fn void usart_write (const USART &usart, uint8_t byte)
 * \brief Escreve um byte pela porta serial
 * \param usart Ponteiro para estrutura USART
 * \param byte Valor a escrever
 */
void usart_write (const USART &usart, uint8_t byte);

/*!
 * \fn void usart_read (const USART &usart)
 * \brief Lê um byte da porta serial
 * \param usart Ponteiro para estrutura USART
 * \returns Byte lido
 * Esta função devolve imediatamente o valor lido, sem esperar
 */
uint8_t usart_read (const USART &usart);

/*!
 * \fn void usart_data_available (const USART &usart)
 * \brief Retorna se há algum byte para ser lido pela porta serial
 * \param usart Ponteiro para estrutura USART
 * \returns 0 (zero) caso não haja. Diferente de zero se houver
 */
uint32_t usart_data_available (const USART &usart);

/*! 
 * \def PAR_NONE
 * Define transmissão sem paridade. Equivalente ao valor 0 (zero)
 */
#define PAR_NONE 0
/*! 
 * \def PAR_ODD
 * Define transmissão com paridade ímpar. Equivalente ao valor 1 (um)
 */
#define PAR_ODD 1
/*! 
 * \def PAR_EVEN
 * Define transmissão com paridade par. Equivalente ao valor 2 (dois)
 */
#define PAR_EVEN 2

#endif

