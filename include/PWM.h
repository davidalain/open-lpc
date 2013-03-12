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
 * \struct pwm_t
 * \brief Define um tipo pwm_t. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void pwm_setup (pwm_t *pwm, uint32_t pin_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits)
 * \brief Configura um PWM
 * \param pwm Ponteiro para estrutura pwm_t
 * \param pwm_num Número do PWM a ser utilizado
 * \param freq Frequência de operação do PWM
 */
void pwm_setup (pwm_t *pwm, uint32_t pwm_num, uint32_t freq);

/*!
 * \fn uint32_t pwm_write (const pwm_t *pwm, uint32_t duty)
 * \brief Modifica o duty cycle do sinal PWM
 * \param pwm Ponteiro para estrutura pwm_t
 * \param duty Valor do novo duty cycle
 */
void pwm_write (const pwm_t *pwm, uint32_t duty);

/*!
 * \fn void pwm_read (const pwm_t *pwm)
 * \brief Lê o valor do duty cycle do PWM
 * \param pwm Ponteiro para estrutura pwm_t
 * \returns Duty cycle do PWM
 */
uint32_t pwm_read (const pwm_t *pwm);

/*!
 * \fn uint32_t pwm_write_float (const pwm_t *pwm, float duty)
 * \brief Modifica o duty cycle do sinal PWM
 * \param pwm Ponteiro para estrutura pwm_t
 * \param duty Valor do novo duty cycle
 */
void pwm_write_float (const pwm_t *pwm, float duty);

/*!
 * \fn void pwm_read_float (const pwm_t *pwm)
 * \brief Lê o valor do duty cycle do PWM
 * \param pwm Ponteiro para estrutura pwm_t
 * \returns Duty cycle do PWM
 */
uint32_t pwm_read_float (const pwm_t *pwm);

#ifdef __cplusplus
}
#endif

#endif
