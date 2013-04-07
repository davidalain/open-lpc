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
#include <misc.h>

static void enable_spi1 (void) {
	RCC->AHB1ENR |= (1 << 1);	// Ativa o clock do GPIO

	GPIOB->MODER &= (~(0x03 << 6) & ~(0x03 << 8) & ~(0x03 << 10));
	GPIOB->MODER |= ((0x02 << 6) | (0x02 << 8) | (0x02 << 10));		// Configura PB3, PB4 e PB5 como função alternativa

	GPIOB->OSPEEDR &= (~(0x03 << 6) & ~(0x03 << 8) & ~(0x03 << 10));
	GPIOB->OSPEEDR |= ((0x02 << 6) | (0x02 << 8) | (0x02 << 10));	// Configura PB3, PB4 e PB5 como 50MHz fast speed

	GPIOB->AFR[0] &= ~(0xFFF << 12);
	GPIOB->AFR[0] |= (0x555 << 12);		// Configura PB3, PB4 e PB5 como SCK, MISO e MOSI respectivamente 
}

static void enable_spi2 (void) {
	RCC->AHB2ENR |= (1 << 1);	// Ativa o clock do GPIO

	GPIOB->MODER &= (~(0x03 << 26) & ~(0x03 << 28) & ~(0x03 << 30));
	GPIOB->MODER |= ((0x02 << 26) | (0x02 << 28) | (0x02 << 30));		// Configura PB13, PB14 e PB15 como função alternativa

	GPIOB->OSPEEDR &= (~(0x03 << 26) & ~(0x03 << 28) & ~(0x03 << 30));
	GPIOB->OSPEEDR |= ((0x02 << 26) | (0x02 << 28) | (0x02 << 30));	// Configura PB13, PB14 e PB15 como 50MHz fast speed

	GPIOB->AFR[1] &= ~(0xFFF << 20);
	GPIOB->AFR[1] |= (0x555 << 20);		// Configura PB13, PB14 e PB15 como SCK, MISO e MOSI respectivamente
}

static void enable_spi3 (void) {
	RCC->AHB1ENR |= (1 << 2);	// Ativa o clock do GPIO

	GPIOC->MODER &= (~(0x03 << 20) & ~(0x03 << 22) & ~(0x03 << 24));
	GPIOC->MODER |= ((0x02 << 20) | (0x02 << 22) | (0x02 << 24));		// Configura PC10, PC11 e PC12 como função alternativa

	GPIOC->OSPEEDR &= (~(0x03 << 20) & ~(0x03 << 22) & ~(0x03 << 24));
	GPIOC->OSPEEDR |= ((0x02 << 20) | (0x02 << 22) | (0x02 << 24));	// Configura PC10, PC11 e PC12 como 50MHz fast speed

	GPIOC->AFR[1] &= ~(0xFFF << 8);
	GPIOC->AFR[1] |= (0x666 << 8);		// Configura PC10, PC11 e PC12 como SCK, MISO e MOSI respectivamente
}

void spi_setup (spi_t *spi, void *spi_num, uint32_t spi_freq) {
    spi->spi = spi_num;
    SPI_TypeDef *spi_typedef = (SPI_TypeDef *)spi_num;

	switch ((uint32_t)spi_num) {
		case SPI1_BASE:
			RCC->APB2ENR |= (1 << 12);	// Ativa o clock
			enable_spi1();

		case SPI2_BASE:
			RCC->APB1ENR |= (1 << 14);	// Ativa o clock
			enable_spi2();

		case SPI3_BASE:
			RCC->APB1ENR |= (1 << 15);	// Ativa o clock
			enable_spi3();

		default:
			break;	// TODO: Hardfault?
	}

    // Ativa o modo de transmissão apenas e seta como modo Master
    spi_typedef->CR1 |= ((1 << 14) | (1 << 2));

    // Ativar a SPI
    spi_typedef->CR1 |= (1 << 6);

    spi_set_frequency (spi, spi_freq);
}

static uint32_t SPI_Baudrate_Divisor[] = {2, 4, 8, 16, 32, 64, 128, 256};

void spi_set_frequency (spi_t *spi, uint32_t freq) {
    uint32_t realfreq, i, pclk = 0;
	SPI_TypeDef *spi_typedef = (SPI_TypeDef *)spi->spi;

	switch ((uint32_t)spi->spi) {
		case SPI1_BASE:
//			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 13)) >> 13];	// CFGR [15:13] são o Prescaler 2
			pclk = get_fpclk (APB2);
			break;

		case SPI2_BASE:
		case SPI3_BASE:
//			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 10)) >> 10];	// CFGR [12:10] são o Prescaler 1
			pclk = get_fpclk (APB1);
			break;

		default:
			break;	// TODO: Hardfault?
	}

    realfreq = pclk / freq;
    for (i = 31; i >=0; i--) 
		if (realfreq & (1 << i)) break;

	realfreq &= (1 << i);
	spi->freq = realfreq;
	for (i = 0; i < sizeof(SPI_Baudrate_Divisor); i++)
		if (SPI_Baudrate_Divisor[i] == realfreq) break;

	spi_typedef->CR1 &= ~(0x07 << 3);
	spi_typedef->CR1 |= (i << 3);
}

uint32_t spi_write (const spi_t *spi, const uint8_t *data, uint32_t length) {
	uint32_t i;
	SPI_TypeDef *spi_typedef = (SPI_TypeDef *)spi->spi;

	for (i = 0; i < length; i++) {
		spi_typedef->DR = data[i];
		while ((spi_typedef->SR & (1 << 1)) == 0)
			;
	}

	return i;
}

#ifdef __cplusplus
}
#endif

