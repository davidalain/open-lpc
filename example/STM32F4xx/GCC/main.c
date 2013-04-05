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

void wait_ms (uint32_t ms) {
	uint32_t quit = ticks + ms;

	while (ticks < quit)
		;
}

int main (void) {

	SysTick_Config (SystemCoreClock / 1000);	// 1ms de SystemTick

	digital_io_t led_laranja;
	uart_t uart1;
	uint8_t a = 'C';

	digitalout_setup (&led_laranja, GPIOD, 13);
	uart_setup (&uart1, USART1, 115200, 8, PARITY_NONE, 1);

	while (1) {
		digitalout_write (&led_laranja, 1);
		uart_write (&uart1, &a, 1);
		wait_ms (50);
		digitalout_write (&led_laranja, 0);
		uart_write (&uart1, &a, 1);
		wait_ms (50);
	}

    return 0;
}

