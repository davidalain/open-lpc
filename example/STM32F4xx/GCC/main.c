#include <stm32f4xx.h>
#include <stdint.h>

static volatile uint32_t ticks;

// SysTick_Handler é a função padrão para o Timer básico do sistema
// Devidamente configurado, esta função pode ser utilizada para
// Medir tempo do sistema
void SysTick_Handler(void) {
    ticks++;
}

extern void SystemCoreClockUpdate (void);

void wait_ms (uint32_t ms) {
	uint32_t quit = ticks + ms;

	while (ticks < quit)
		;
}

int main (void) {

	SystemCoreClockUpdate();
	SysTick_Config (SystemCoreClock / 4000);	// 1ms de SystemTick
	// TODO: Falta ver como faz para saber que tem que dividir o Clock por 4 (no caso) e depois pelo tempo desejado

	RCC->AHB1ENR |= (1 << 3);

	GPIOD->MODER |= (1 << 26);
	GPIOD->MODER &= ~(1 << 27);
	
	while (1) {	// Faz piscar o LED Laranja :D
		GPIOD->BSRRH |= (1 << 13);
		wait_ms (250);
		GPIOD->BSRRL |= (1 << 13);
		wait_ms (250);
	}

    return 0;
}

