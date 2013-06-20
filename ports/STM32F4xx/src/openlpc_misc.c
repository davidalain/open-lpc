/**
 * misc.c - Funções miscelâneas utilizados por vários módulos
 * Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include <openlpc_misc.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>
#include <stdint.h>

static const uint32_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

uint32_t get_fpclk(APBAHBSource source) {

	uint32_t pclk = 0;

	switch ((uint32_t)source) {
		case 1:
			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 13)) >> 13];	// CFGR [15:13] são o Prescaler 2
			break;

		case 0:
			pclk = SystemCoreClock >> APBAHBPrescTable[(RCC->CFGR & (0x07 << 10)) >> 10];	// CFGR [12:10] são o Prescaler 1
			break;

		default:
			break;
	}

	return pclk;
}

