/*
 * spimaster.c
 * Funcões para objeto UART
 * Author: David Alain do Nascimento
 * Version STM32F407xx 0.1
 * Date: 01/03/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <spi_master.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>

void spi_setup (SPI *spi, uint32_t spi_num, uint32_t spi_freq) {

}

void spi_set_frequency (SPI *spi, uint32_t freq) {

}

uint32_t spi_write (const SPI *spi, const uint8_t *data, uint8_t *recv, uint32_t length) {

	return 0;
}

#ifdef __cplusplus
}
#endif
