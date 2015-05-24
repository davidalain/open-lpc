# DigitalOut #

**DigitalOut** é um objeto que controla um pino de saída digital. Para se fazer uso do objeto é necessário declarar um **DigitalOut** e utilizar as funções disponíveis.

## Exemplo ##

Exemplo de uso de um **DigitalOut**

```

#include <DigitalOut.h>

DigitalOut MyPin;
DigitalOut MyOtherPin;

digitalout_setup (&MyPin, GPIO0, 0);
digitalout_setup (&MyOtherPin, GPIO0, 1);

// Coloca a saída em nível lógico alto
digitalout_write (&MyPin, 1);

// Lê o estado de um pino de saída e configura o outro como o mesmo estado
digitalout_write (&MyOtherPin, digitalout_read(&MyPin));

```

## Definições ##

`void digitalout_setup (DigitalOut *pin, uint32_t portnum, uint32_t pinnum)`
Configura um pino como saída digital

`uint32_t digitalin_read (const DigitalOut *pin)`
Lê o valor de um pino digital de saída

`void digitalout_write (const DigitalOut *pin, uint32_t value)`
Modifica o nível lógico do pino de saída.