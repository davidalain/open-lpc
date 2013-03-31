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

int main (void) {

	SystemCoreClockUpdate();

	USART_TypeDef *l_usart = USART1;
	uint32_t pclk2 = SystemCoreClock;
	uint32_t div, mantissa;

	RCC->APB2ENR |= (1 << 4);	// Ativa o clock da USART1
	l_usart->CR1 |= (1 << 13);	// USART Enable
	l_usart->CR1 &= ~(1 << 12);	// 8 bits
	l_usart->CR1 &= ~(1 << 10);	// N
	l_usart->CR1 |= (0x3 << 2);	// TX e RX ativo
	l_usart->CR2 &= (~(1 << 13) & ~(1 << 12));	// 1 stop bit

	if (RCC->CFGR & (1 << 29)) {
		div = 2 + ((RCC->CFGR & (0x03 << 27)) >> 27);
		pclk2 = SystemCoreClock / div;
	} else {
		pclk2 = SystemCoreClock;
	}

	mantissa = pclk2 / (16 * 115200);
	l_usart->BRR = (mantissa << 4); // 115200??

	while (1) {
		while (! (l_usart->SR & (1 << 6)));
		l_usart->DR = 'A';
	}

    return 0;
}

