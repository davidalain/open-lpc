/*
 * i2cmaster.c
 * Funcões para I2C Master
 * Author: Cristóvão Zuppardo Rufino
 * Version LPC17xx 0.1
 * Date: 20/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <I2CMaster.h>
#include <LPC17xx.h>
#include <system_LPC17xx.h>

static void i2cmaster_set_clock (const I2CMaster *i2c, uint32_t i2c_clk) {
	uint32_t clk_sel, pclk;
	uint16_t scl_hl;
	LPC_I2C_TypeDef *l_i2c;

	switch (i2c->i2c) { // Determina a divisão do clock
		case LPC_I2C0_BASE:
			clk_sel = (LPC_SC->PCLKSEL0 >> 14) & 0x03;
			break;
		case LPC_I2C1_BASE:
			clk_sel = (LPC_SC->PCLKSEL1 >> 6) & 0x03;
			break;
		case LPC_I2C2_BASE:
			clk_sel = (LPC_SC->PCLKSEL1 >> 20) & 0x03;
			break;
		default:
			break;
	}

		switch (clk_sel) {  // Determina o clock do periférico
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

	scl_hl = pclk / i2c_clk;
	l_i2c = (LPC_I2C_TypeDef *)i2c->i2c;
	l_i2c->I2SCLH = scl_hl / 2;
	l_i2c->I2SCLL = (scl_hl - l_i2c->I2SCLH); // Coloca o I2C com 50% de duty no clock
}
	
void i2cmaster_setup (I2CMaster *i2c, uint32_t i2c_num, uint32_t i2c_clk) {

	i2c->i2c = i2c_num;

	switch (i2c_num) {
		case LPC_I2C0_BASE:

			LPC_SC->PCONP |= (1 << 7); // Ativa o HW do I2C0
			LPC_PINCON->PINSEL1 &= ~(0x02 << 22);
			LPC_PINCON->PINSEL1 |= (0x01 << 22); // Seleciona P0.27 como SDA
			LPC_PINCON->PINSEL1 &= ~(0x02 << 24);
			LPC_PINCON->PINSEL1 |= (0x01 << 24); // Seleciona P0.28 como SCL
			
			// OBS: De acordo com o "User Manual LPC17XX.pdf", os pinos P0.27
			// e P0.28 já são coletor aberto c/ pull-up e pull-down desativados
			// OBS2: De acordo com o mesmo arquivo P0.27 e P0.28 já estão configurados
			// como Standard Mode (100kHz) e com 'glitch' e 'slew rate' já ativos
			// no reset
			break;

		case LPC_I2C1_BASE:

			LPC_SC->PCONP |= (1 << 19); // Ativa o HW do I2C1
			
			LPC_PINCON->PINSEL0 |= (0x03 << 0); // Seleciona P0.0 como SDA1
			
			LPC_PINCON->PINSEL0 |= (0x03 << 2); // Seleciona P0.1 como SCL1
			
			LPC_PINCON->PINMODE0 |= (0x02 << 0);
			LPC_PINCON->PINMODE0 &= ~(0x01 << 0); //Tira o pull-up e pull-down do SDA1

			LPC_PINCON->PINMODE0 |= (0x02 << 2);
			LPC_PINCON->PINMODE0 &= ~(0x01 << 2); // Tira o pull-up e pull-down do SCL1
			
			LPC_PINCON->PINMODE_OD0 |= (1 << 0); // Coloca como open-drain o SDA1
			LPC_PINCON->PINMODE_OD0 |= (1 << 1); // Coloca como open-drain o SCL1
			break;

		case LPC_I2C2_BASE:

			LPC_SC->PCONP |= (1 << 26); // Ativa o HW do I2C2

			LPC_PINCON->PINSEL0 &= ~(0x01 << 20);
			LPC_PINCON->PINSEL0 |= (0x02 << 20); // Seleciona P0.10 como SDA2
			
			LPC_PINCON->PINSEL0 &= ~(0x02 << 22);
			LPC_PINCON->PINSEL0 |= (0x01 << 22); // Seleciona P0.11 como SCL2

			LPC_PINCON->PINMODE0 |= (0x02 << 20);
			LPC_PINCON->PINMODE0 &= ~(0x01 << 20); // Tira o pull-up e pull-down do SDA2

			LPC_PINCON->PINMODE0 |= (0x02 << 22);
			LPC_PINCON->PINMODE0 &= ~(0x01 << 22); // Tira o pull-up e pull-down do SCL2

			LPC_PINCON->PINMODE_OD0 |= (1 << 10); // Coloca como open-drain o SDA2
			LPC_PINCON->PINMODE_OD0 |= (1 << 11); // Coloca como open-drain o SCL2
			break;

		default:
			// TODO: Invocar um hardfault, talvez...
			break;
	}

	i2cmaster_set_clock (i2c, i2c_clk);
}

uint32_t i2cmaster_read (const I2CMaster *i2c, uint8_t address, uint8_t *data, uint32_t length) {
	return 0;
}

uint32_t i2cmaster_write (const I2CMaster *i2c, uint8_t address, const uint8_t data, uint32_t length) {
	return 0;
}

void i2cmaster_generate_start (const I2CMaster *i2c) {

}

void i2cmaster_generate_stop (const I2CMaster *i2c) {

}

#ifdef __cplusplus
}
#endif