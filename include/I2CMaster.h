#ifndef I2CMASTER_H
#define I2CMASTER_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file I2CMaster.h
 * Tipo para interface I2C em modo Master
 * \details Contém funções para configurar e utilizar uma porta I2C como dispositivo Master
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 20/02/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>
#include <stdint.h>

/*!
 * \struct I2CMaster
 * \brief Define um tipo serial RS-232. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void i2cmaster_setup (I2CMaster *i2c, uint32_t i2c_num)
 * \brief Configura uma porta I2C em modo Master
 * \param i2c Ponteiro para estrutura I2CMaster
 * \param i2c_num Número da porta a ser utilizada
	 * \param i2c_clk Clock de operação do I2C
 */
void i2cmaster_setup (I2CMaster *i2c, uint32_t i2c_num, uint32_t i2c_clk);

/*!
 * \fn uint32_t i2cmaster_read (const I2CMaster *i2c, uint8_t address, uint8_t *data, uint32_t length)
 * \brief Lê um conjunto de bytes do endereço especificado
 * \param i2c Ponteiro para estrutura I2CMaster
 * \param address Endereço do dispositivo
 * \param data Ponteiro onde escrever os dados lidos
 * \param length Tamanho, em bytes, da leitura a ser executada
 * \returns 0 em caso de sucesso
 */
uint32_t i2cmaster_read (const I2CMaster *i2c, uint8_t address, uint8_t *data, uint32_t length);

/*!
 * \fn uint32_t i2cmaster_write (const I2CMaster *i2c, uint8_t address, const uint8_t data, uint32_t length)
 * \brief Escreve um conjunto de bytes no endereço especificado
 * \param i2c Ponteiro para estrutura I2CMaster
 * \param address Endereço do dispositivo
 * \param data Ponteiro de origem dos dados
 * \param length Tamanho, em bytes, dos dados
 * \returns 0 em caso de sucesso
 */
uint32_t i2cmaster_write (const I2CMaster *i2c, uint8_t address, const uint8_t *data, uint32_t length);

/*!
 * \fn void i2cmaster_generate_start (const I2CMaster *i2c)
 * \brief Gera uma condição 'start' na linha de dados
 * \param i2c Ponteiro para estrutura I2CMaster
 */
void i2cmaster_generate_start (const I2CMaster *i2c);

/*!
 * \fn void i2cmaster_generate_stop (const I2CMaster *i2c)
 * \brief Gera uma condição 'stop' na linha de dados
 * \param i2c Ponteiro para estrutura I2CMaster
 */
void i2cmaster_generate_stop (const I2CMaster *i2c);

/*!
 * \def I2C_100KHZ
 * Define o clock da porta I2C igual a 100kHz
 */
#define I2C_100KHZ  100000

/*!
 * \def I2C_100KHZ
 * Define o clock da porta I2C igual a 100kHz
 */
#define I2C_400KHZ  400000
	
#ifdef __cplusplus
}
#endif

#endif
