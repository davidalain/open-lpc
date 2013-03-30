#include <stdint.h>

static volatile uint32_t ticks;

// SysTick_Handler é a função padrão para o Timer básico do sistema
// Devidamente configurado, esta função pode ser utilizada para
// Medir tempo do sistema
void SysTick_Handler(void) {
    ticks++;
}

int main (void) {

    while (1)
        ;

    return 0;
}

