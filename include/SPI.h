#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file SPI.h
 * Tipo para interface SPI Master
 * \details Contém funções para configurar e utilizar uma porta SPI Master
 * \author Cristóvão Zuppardo Rufino
 * \version 0.1
 * \date 01/03/2013
 * \copyright Cristóvão e David
 */

#include <port_types.h>
#include <stdint.h>

/*!
 * \struct SPI
 * \brief Define um tipo SPI. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void spi_setup (SPI *spi, uint32_t spi_num, uint32_t spi_freq)
 * \brief Configura uma porta SPI
 * \param spi Ponteiro para estrutura SPI
 * \param spi_num Número da porta a ser utilizada
 * \param spi_freq Baud rate da porta
 */
void spi_setup (SPI *spi, uint32_t spi_num, uint32_t spi_freq);

/*!
 * \fn void spi_set_frequency (SPI *spi, uint32_t freq)
 * \brief Configura somente a frequencia de operação
 * \param spi Ponteiro para estrutura SPI
 * \param freq Novo valor da frequencia em Hz
 */
void spi_set_frequency (const SPI *spi, uint32_t freq);

/*!
 * \fn uint32_t spi_write (const SPI *spi, const uint8_t *data, uint8_t *recv, uint32_t length)
 * \brief Escreve vários bytes pela porta SPI
 * \param spi Ponteiro para estrutura SPI
 * \param data Ponteiro para array de bytes de saída
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t spi_write (const SPI *spi, const uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif

