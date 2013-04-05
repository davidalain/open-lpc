/*
 * spi_master.c
 * Funcões para objeto SPI Master
 * Author: David Alain do Nascimento
 * Co-author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 * Version STM32F407xx 0.1
 * Date: 05/04/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <spi_master.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>

void spi_setup (spi_t *spi, void *spi_num, uint32_t spi_freq) {
    spi->spi = spi_num;
    SPI_TypeDef *spi_typedef = (SPI_TypeDef *)spi_num;

    // Ativa o modo de transmissão apenas e seta como modo Master
    spi_typedef->CR1 |= ((1 << 14) | (1 << 2));

    // Ativar a SPI
    spi_typedef->CR1 |= (1 << 6);

    spi_set_frequency (spi, spi_freq);
}

void spi_set_frequency (spi_t *spi, uint32_t freq) {
    uint32_t realfreq, i;
    realfreq = SystemCoreClock / freq;
    
}

uint32_t spi_write (const spi_t *spi, const uint8_t *data, uint32_t length) {

	return 0;
}

#ifdef __cplusplus
}
#endif

