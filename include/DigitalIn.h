#ifndef DIGITALIN_H
#define DIGITALIN_H

#ifdef __cplusplus
extern "C" {
#endif

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
#include <stdint.h>

/*!
 * \struct digitalin_t
 * \brief Define um tipo pino de entrada digital. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void digitalin_setup (digitalin_t *pin, uint32_t portnum, uint32_t pinnum)
 * \brief Configura um pino como entrada digital
 * \param pin Ponteiro para estrutura digitalin_t
 * \param portnum Número da porta ao qual o pino pertence
 * \param pinnum Número correspondente do pino na porta (começando por zero)
 */
void digitalin_setup (digitalin_t *pin, uint32_t portnum, uint32_t pinnum);

/*!
 * \fn uint32_t digitalin_read (const digitalin_t *pin)
 * \brief Lê o valor de um pino digital
 * \param pin Ponteiro para estrutura digitalin_t
 * \returns O valor 1 (um) para nível lógico alto ou 0 (zero) para nível lógico baixo
 */
uint32_t digitalin_read (const digitalin_t *pin);

#ifdef __cplusplus
}
#endif

#endif

