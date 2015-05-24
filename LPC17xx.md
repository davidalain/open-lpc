# Cortex-M3 NXP LPC17xx #

Família de microcontroladores Cortex-M3 na NXP. O port da _HAL_ está sendo desenvolvido utilizando a plataforma de desenvolvimento [\*mbed\*](http://mbed.org) que possui um LPC1768.

A configuração do _hardware_ deste microcontrolador é:
  * Clock de 96MHz
  * 64KB RAM (32KB de RAM + 16KB para USB e 16KB para Ethernet)
  * 6 canais PWM
  * Conversores A/D com resolução de 12 bits
  * Conversor D/A com resolulção de 10 bits
  * Interface Ethernet
  * USB Host e USB Device
  * 4 UART RS-232 (UART0/2/3) e RS-485 (UART1)
  * 3 SPI _master_ ou _slave_
  * I2C _master_ e _slave_
  * CAN

Os manuais do LPC17xx estão disponíveis na sessão de Downloads.

## Dispositivos já implementados ##

  * Portas de I/O (DigitalOut e DigitalIn)
  * UART

## Dispositivos em implementação ##

  * I2C Master
