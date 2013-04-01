#include <stm32f4xx.h>
#include <stdint.h>

#include <digital_out.h>
#include <digital_in.h>

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

	digital_io_t led_laranja;
	digital_io_t user_sw;

	digitalout_setup (&led_laranja, GPIOD, 13);
	digitalin_setup (&user_sw, GPIOA, 0);

	while (1) {
		digitalout_write (&led_laranja, digitalin_read (&user_sw));
	}

    return 0;
}

