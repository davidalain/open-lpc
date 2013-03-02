/*
 * spimaster.c
 * Funcões para objeto UART
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 01/03/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <SPI.h>
#include <LPC17xx.h>
#include <system_LPC17xx.h>

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
