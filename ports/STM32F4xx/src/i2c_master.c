/*
 * i2cmaster.c
 * Funcões para I2C Master
 * Author: David Alain do Nascimento
 * Version STM32F407xx 0.1
 * Date: 20/02/2013
 * Copyright: Cristóvão e David
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <i2c_master.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>

// Status para Master Transmit (MT)
#define MT_START_TRANSMITTED_ACK 			0x08
#define MT_REPEATED_START_TRANSMITTED_ACK 	0x10
#define MT_SLA_W_TRANSMITTED_ACK 			0x18
#define MT_SLA_W_TRANSMITTED_NACK 			0x20
#define MT_BYTE_TRANSMITTED_ACK 			0x28
#define MT_BYTE_TRANSMITTED_NACK 			0x30
#define MT_SLA_RW_ARBITRATION_LOST 			0x38

// Status para Master Receive (MR)
#define MR_START_TRANSMITTED_ACK 			0x08
#define MR_REPEATED_START_TRANSMITTED 		0x10
#define MR_ARBITRATION_LOST 				0x38
#define MR_SLA_R_TRANSMITTED_ACK 			0x40
#define MR_SLA_R_TRANSMITTED_NACK 			0x48
#define MR_BYTE_RECEIVED_ACK 				0x50
#define MR_BYTE_RECEIVED_NACK 				0x58

static void i2cmaster_set_clock (const i2cmaster_t *i2c, uint32_t i2c_clk) {
	uint32_t clk_sel, pclk;
	uint16_t scl_hl;
	I2C_InitTypeDef *l_i2c;

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
	
void i2cmaster_setup (i2cmaster_t *i2c, void *i2c_num, uint32_t i2c_clk) {
	LPC_I2C_TypeDef *l_i2c;

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
	l_i2c = (LPC_I2C_TypeDef *)i2c_num;
	l_i2c->I2CONSET |= (1 << 6);	// Ativa o I2C
}

uint32_t i2cmaster_read (const i2cmaster_t *i2c, uint8_t address, uint8_t *data, uint32_t length) {

	uint32_t i;
	LPC_I2C_TypeDef *l_i2c;

	l_i2c = (LPC_I2C_TypeDef *)i2c->i2c;

	i2cmaster_generate_start (i2c);

	l_i2c->I2DAT = (address | (1 << 0));    // Envia o endereço indicando leitura (R/W bit = 0)
	l_i2c->I2CONCLR |= (1 << 3);    // Limpa a flag SI

	i = 0;
	while (length > 0) {
		while ((l_i2c->I2CONSET & (1 << 3)) == 0);  // Espera ficar pronto para transmitir
		data[i] = l_i2c->I2DATA_BUFFER;
		length--; i++;
		l_i2c->I2CONCLR |= (1 << 3);    // Limpa a flag SI
	}

	i2cmaster_generate_stop (i2c);

	return i;   // Retorna o total lido
}

uint32_t i2cmaster_write (const i2cmaster_t *i2c, uint8_t address, const uint8_t *data, uint32_t length) {

	uint32_t i;
	LPC_I2C_TypeDef *l_i2c;

	l_i2c = (LPC_I2C_TypeDef *)i2c->i2c;

	i2cmaster_generate_start (i2c);

	l_i2c->I2DAT = (address & ~(1 << 0));   // Envia o endereço indicando escrita (R/W bit = 0)
	l_i2c->I2CONCLR |= (1 << 3);	// Limpa a flag SI
	
	i = 0;
	while (length > 0) {
		while ((l_i2c->I2CONSET & (1 << 3)) == 0);  // Espera ficar pronto para transmitir
		l_i2c->I2DAT = data[i];
		length--; i++;
		l_i2c->I2CONCLR |= (1 << 3);    // Limpa a flag SI
	}

	return i;
}

void i2cmaster_generate_start (const i2cmaster_t *i2c) {
	LPC_I2C_TypeDef *l_i2c;

	l_i2c = (LPC_I2C_TypeDef *)i2c->i2c;

	l_i2c->I2CONSET |= (1 << 5);	// Sinaliza START
	l_i2c->I2CONCLR |= (1 << 3);	// Limpa a interrupção

	while ((l_i2c->I2CONSET & (1 << 3)) == 0)
		;   // Aguarda o fim do START
	l_i2c->I2CONCLR |= (1 << 5);	// Limpa o START
}

void i2cmaster_generate_stop (const i2cmaster_t *i2c) {
	LPC_I2C_TypeDef *l_i2c;

	l_i2c = (LPC_I2C_TypeDef *)i2c->i2c;

	if (l_i2c->I2CONSET & (1 << 5))
		l_i2c->I2CONCLR |= (1 << 5);	// Limpa o START se estiver setado

	l_i2c->I2CONSET |= (1 << 4);
	l_i2c->I2CONCLR |= (1 << 4);	// Sinaliza o STOP
}

#ifdef __cplusplus
}
#endif
