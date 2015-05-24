# UART #

**UART** é um objeto que controla uma porta serial RS-232. Para se fazer uso do objeto é necessário declarar um **UART** e utilizar as funções disponíveis.

## Exemplo ##

Exemplo de uso de um **UART**

```

#include <UART.h>

UART MyUART;

uart_setup (&MyUART, UART0, 115200, 8, PAR_NONE, 1);

while (1) {

    // Espera ter algo disponível para leitura
    while (uart_data_available(&MyUART) == 0) ;

	// Escreve na UART o que foi recebido (ou seja, um ECHO)
	uart_write (&MyUART, uart_read (&MyUART));
}

```

## Definições ##

`void uart_setup (UART *uart, uint32_t uart_num, uint32_t baud, uint32_t wordsize, uint32_t parity, uint32_t stopbits)`
Configura uma serial RS-232

`void uart_set_baud (UART *uart, uint32_t baud)`
Modifica apenas o _baud rate_ da porta serial sem modificar outros parâmetros

`void uart_set_wordsize (UART *uart, uint32_t wordsize)`
Modifica apenas o tamanho da palavra utilizada (5, 6, 7 ou 8 bits) sem modificar outros parâmetros

`void uart_set_parity (UART *uart, uint32_t parity)`
Modifica apenas a paridade da porta (PAR\_NONE, PAR\_ODD, PAR\_EVEN) sem modificar outros parâmetros

`void uart_set_stopbits (UART *uart, uint32_t stopbits)`
Modifica apenas o número de _stop bits_ da porta (1 ou 2) sem modificar outros parâmetros

`void uart_write (const UART *uart, uint8_t byte)`
Escreve um byte na porta serial. (Obs.: a função bloqueia enquanto a saída não está disponível)

`uint8_t uart_read (const UART *uart)`
Lê um byte da porta serial. (Obs.: a função não bloqueia e retorna imediatamente o que tem)

`uint32_t uart_data_available (const UART *uart)`
Verifica se há algum byte disponível para leitura. Se houver retorna não nulo (`!= 0`)