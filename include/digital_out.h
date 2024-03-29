#ifndef OPENLPC_DIGITAL_OUT_H
#define OPENLPC_DIGITAL_OUT_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file digital_out.h
 * Tipo para interface com pinos digitais de saída.
 * \details Contém funções para configurar e utilizar um pino como entrada digital
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 15/02/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>

/*!
 * \struct digitalout_t
 * \brief Define um tipo pino de saída digital. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void digitalout_setup (digitalout_t *pin, uint32_t portnum, uint32_t pinnum)
 * \brief Configura um pino como saída digital
 * \param pin Ponteiro para estrutura digitalout_t
 * \param portnum Número da porta ao qual o pino pertence
 * \param pinnum Número correspondente do pino na porta (começando por zero)
 */
void digitalout_setup (digital_io_t *pin, void* portnum, uint32_t pinnum);

/*!
 * \fn void digitalout_write (const digitalout_t *pin, uint32_t value)
 * \brief Escreve o valor de um pino digital de saída
 * \param pin Ponteiro para estrutura digitalout_t
 * \param value Valor a ser escrito na saída. 0 (zero) para nível lógico baixo. Diferetente de zero para nível lógico alto
 */
void digitalout_write (const digital_io_t *pin, uint32_t value);

/*!
 * \fn uint32_t digitalout_read (const digitalout_t *pin)
 * \brief Lê o valor de um pino digital
 * \param pin Ponteiro para estrutura digitalout_t
 * \returns O valor 1 (um) para nível lógico alto ou 0 (zero) para nível lógico baixo
 */
uint32_t digitalout_read (const digital_io_t *pin);

#ifdef __cplusplus
}
#endif

#endif

