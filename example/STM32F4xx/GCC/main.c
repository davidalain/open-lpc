#include <stm32f4xx.h>
#include <stdint.h>

#include <digital_out.h>
#include <digital_in.h>
#include <UART.h>

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

	uart_t uart1;

	uart_setup (&uart1, USART1, 115200, 8, PARITY_NONE, 1);	

	while (1) {
		uart_write (&uart1, (uint8_t *)"A", 1);
	}

    return 0;
}

