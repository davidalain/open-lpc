/**
 * misc.c - Funções miscelâneas utilizados por vários módulos
 * Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include <misc.h>
#include <stm32f4xx.h>

uint32_t get_clock (void) {

	uint32_t sysclock, pllsource = 0, pllm = 2, pllvco = 0, pllp = 2;

	switch (RCC->CFGR & 0x0C) {

	case 0x04:
		sysclock = HSE_VALUE;
		break;

	case 0x08:
		pllsource = (RCC->PLLCFGR & (1 << 22)) >> 22;
		pllm = RCC->PLLCFGR & 0x3F;

		if (pllsource != 0)	{
			/* HSE used as PLL clock source */
			pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
		} else {
			/* HSI used as PLL clock source */
			pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
		}

		pllp = ((RCC->PLLCFGR & (0x03 << 16) >>16) + 1 ) * 2;
		sysclock = pllvco/pllp;

	case 0x00:
	default:
		sysclock = HSI_VALUE;
		break;
	}

	return sysclock;
}

