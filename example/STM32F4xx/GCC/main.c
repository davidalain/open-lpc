#include <stm32f4xx.h>
#include <stdint.h>
#include <open_lpc.h>
#include <serial_io.h>

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

	uart_t uart2;
	digital_io_t led_laranja;

	uart_setup (&uart2, USART2, 115200, 8, PARITY_NONE, 1);
	digitalout_setup (&led_laranja, GPIOD, 13);
	serial_io_setup (&uart2, &uart2);

	openlpc_printf ("Cristovao sends hello world!\r\n");
	openlpc_printf ("SystemCoreClock=[%u]\r\n", SystemCoreClock);

	while (1) {
		digitalout_write (&led_laranja, 1);
		wait_ms (100);
		digitalout_write (&led_laranja, 0);
		wait_ms (100);
	}

    return 0;
}

