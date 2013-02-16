#ifndef DIGITALIN_H
#define DIGITALIN_H

/*!
 * \file DigitalIn.h
 * Tipo para interface com pinos digitais de entrada.
 * \details Contém funções para configurar e utilizar um pino como entrada digital
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 15/02/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>

/*!
 * \struct DigitalIn
 * \brief Define um tipo pino de entrada digital. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void digitalin_setup (DigitalIn &pin, uint32_t portnum, uint32_t pinnum)
 * \brief Configura um pino como entrada digital
 * \param pin Ponteiro para estrutura DigitalIn
 * \param portnum Número da porta ao qual o pino pertence
 * \param pinnum Número correspondente do pino na porta (começando por zero)
 */
void digitalin_setup (DigitalIn &pin, uint32_t portnum, uint32_t pinnum);

/*!
 * \fn uint32_t digitalin_read (const DigitalIn &pin)
 * \brief Lê o valor de um pino digital
 * \param pin Ponteiro para estrutura DigitalIn
 * \returns O valor 1 (um) para nível lógico alto ou 0 (zero) para nível lógico baixo
 */
uint32_t digitalin_read (const DigitalOut &pin);

#endif

