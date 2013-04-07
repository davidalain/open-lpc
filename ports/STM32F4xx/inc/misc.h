/**
 * misc.h - Funções miscelâneas utilizados por vários módulos
 * Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
	APB1 = 0,
	APB2
} APBAHBSource;

uint32_t get_fpclk(APBAHBSource source);

#ifdef __cplusplus
}
#endif
#endif

