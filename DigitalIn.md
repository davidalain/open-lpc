# DigitalIn #

**DigitalIn** é um objeto que controla um pino de entrada digital. Para se fazer uso do objeto é necessário declarar um **DigitalIn** e utilizar as funções disponíveis.

## Exemplo ##

Exemplo de uso de um **DigitalIn**

```

#include <DigitalIn.h>

DigitalIn MyPin;

digitalin_setup (&MyPin, GPIO0, 0);

while (digitalin_read (&MyPin) == 0) ;
    // Espera sair de zero

```

## Definições ##

`void digitalin_setup (DigitalIn *pin, uint32_t portnum, uint32_t pinnum)`
Configura um pino como entrada digital

`uint32_t digitalin_read (const DigitalOut *pin)`
Lê o valor de um pino digital de entrada