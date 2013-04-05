#ifndef OPENLPC_SPI_MASTER_H
#define OPENLPC_SPI_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file spi_master.h
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
 * \struct spi_t
 * \brief Define um tipo spi_t. Cada arquitetura possui uma implementação deste tipo.
 */

/*!
 * \fn void spi_setup (spi_t *spi, void *spi_num, uint32_t spi_freq)
 * \brief Configura uma porta SPI
 * \param spi Ponteiro para estrutura spi_t
 * \param spi_num Número da porta a ser utilizada
 * \param spi_freq Baud rate da porta
 */
void spi_setup (spi_t *spi, void *spi_num, uint32_t spi_freq);

/*!
 * \fn void spi_set_frequency (spi_t *spi, uint32_t freq)
 * \brief Configura somente a frequencia de operação
 * \param spi Ponteiro para estrutura spi_t
 * \param freq Novo valor da frequencia em Hz
 */
void spi_set_frequency (spi_t *spi, uint32_t freq);

/*!
 * \fn uint32_t spi_write (const spi_t *spi, const uint8_t *data, uint32_t length)
 * \brief Escreve vários bytes pela porta SPI
 * \param spi Ponteiro para estrutura spi_t
 * \param data Ponteiro para array de bytes de saída
 * \param length Tamanho de data
 * \returns Quantidade total de bytes escritos
 */
uint32_t spi_write (const spi_t *spi, const uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif

