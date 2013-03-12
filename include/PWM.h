#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file PWM.h
 * Tipo para interface PWM
 * \details Contém funções para configurar e utilizar um PWM
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 07/03/2013
 * \copyright Cristóvão
 */

#include <port_types.h>
#include <stdint.h>

/*!
 * \struct PWM
 * \brief Define um tipo serial RS-232. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void pwm_setup (PWM *pwm, uint32_t pin_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits)
 * \brief Configura uma porta serial
 * \param pwm Ponteiro para estrutura PWM
 * \param pwm_num Número da porta a ser utilizada
 * \param baud Baud rate da porta
 * \param wordsize Tamanho da palavra da serial: 5, 6, 7 ou 8 bits
 * \param parity Paridade da porta serial: PAR_NONE, PAR_ODD, PAR_EVEN
 * \param stopbits Número de stopbits: 1 ou 2
 */
void pwm_setup (PWM *pwm, uint32_t pwm_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits);

/*!
 * \fn uint32_t pwm_write (const PWM *pwm, const uint8_t *data, uint32_t length)
 * \brief Escreve vários bytes pela porta serial
 * \param pwm Ponteiro para estrutura PWM
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t pwm_write (const PWM *pwm, const uint8_t *data, uint32_t length);

/*!
 * \fn void pwm_read (const PWM *pwm)
 * \brief Lê vários bytes da porta serial
 * \param pwm Ponteiro para estrutura PWM
 * \param data Ponteiro para array de bytes
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t pwm_read (const PWM *pwm, uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif
