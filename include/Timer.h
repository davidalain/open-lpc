#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file Timer.h
 * Interface para timer
 * \details Contém funções para configurar e utilizar um timer de hardware
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 13/03/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>
#include <stdint.h>

/*!
 * \struct timer_t
 * \brief Define um tipo timer_t. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void timer_setup (timer_t *timer, uint32_t timer_num, uint32_t prescaler, uint32_t div)
 * \brief Configura um timer
 * \param timer Ponteiro para estrutura timer_t
 * \param timer_num Número da porta a ser utilizada
 * \param prescaler Valor do prescaler
 * \param div Valor do divisor
 */
void timer_setup (timer_t *timer, uint32_t timer_num, uint32_t prescaler, uint32_t div);

/*!
 * \fn void timer_set_prescaler (timer_t *timer, uint32_t prescaler)
 * \brief Configura somente o prescaler do timer
 * \param timer Ponteiro para estrutura timer_t
 * \param prescaler Valor do prescaler
 * \param div Valor do divisor
 */
void timer_set_prescaler (timer_t *timer, uint32_t prescaler, uint32_t div);

/*!
 * \fn void timer_reset (const timer_t *timer)
 * \brief Zera o timer
 * \param timer Ponteiro para estrutura timer_t
 */
void timer_reset (const timer_t *timer);

/*!
 * \fn uint32_t timer_read (const timer_t *timer)
 * \brief Realiza uma leitura no timer
 * \param timer Ponteiro para estrutura timer_t
 * \returns Valor do timer
 */
uint32_t timer_read (const timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif

