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

    LPC_SPI_TypeDef *l_spi;
    
    spi->spi = spi_num;
    l_spi = (LPC_SPI_TypeDef *)spi_num;

    LPC_SC->PCONP |= (1 << 8);  // Ativa a SPI. No reset, o SPI já está ativo
    LPC_PINCON->PINSEL0 |= (0x03 << 30);    // Seleciona P0.15 como SCLK
    LPC_PINCON->PINSEL1 |= (0x03 << 2);     // Seleciona P0.17 como MISO
    LPC_PINCON->PINSEL1 |= (0x03 << 4);     // Seleciona P0.18 como MOSI
    // TODO: Aqui não estamos ativando o SSEL (Slave select)

    spi_set_frequency (spi, spi_freq); 
    l_spi->SPCR = (1 << 5); // BitEnable = 0 (8 bits/transfer), CPHA = 0
                            // CPOL = 0 (SCK ativo em HIGH), MSTR = 1, LSBR = 1
                            // LSBF = 0 (Transmite do MSb para o LSb), SPIE = 0
                            // Interrupções desligadas

}

void spi_set_frequency (const SPI *spi, uint32_t freq) {

    uint32_t pclk, clk_sel;
    LPC_SPI_TypeDef *l_spi;

    switch (spi->spi) {
        case LPC_SPI_BASE:  // TODO: SPI é deprecated; criar também o SSP0/1
            clk_sel = (LPC_SC->PCLKSEL0 >> 16) & 0x03;
            break;

        default:
            // TODO: Hardfault, talvez?
            break;
    }

    	switch (clk_sel) {
		default:
		case 0x00:
			pclk = SystemCoreClock / 4;
			break;
		case 0x01:
			pclk = SystemCoreClock;
			break;
		case 0x02:
			pclk = SystemCoreClock / 2;
			break;
		case 0x03:
			pclk = SystemCoreClock / 8;
			break;
	}

    l_spi = (LPC_SPI_TypeDef *)spi->spi;

    if ((pclk / freq) < 8)
        l_spi->SPCCR = 8;
    else
        l_spi->SPCCR = (pclk / freq);

}

uint32_t spi_write (const SPI *spi, const uint8_t *data, uint32_t length) {

    uint32_t i;
    LPC_SPI_TypeDef *l_spi;

    l_spi = (LPC_SPI_TypeDef *)spi->spi;
    i = 0;
    while (length > 0) {
        l_spi->SPDR = data[i];
        while ((l_spi->SPSR & (1 << 7)) == 0);  // Aguarda até terminar a transferência
        length--; i++;
    }

    return i;
}

#ifdef __cplusplus
}
#endif

