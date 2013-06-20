/*
 * counter.h
 *
 *  Created on: 15/06/2013
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include <stdint.h>
#include <port_types.h>

void counter_setup (counter_t *counter, void *timer, uint32_t div);
uint32_t counter_read (const counter_t *counter);
void counter_reset (const counter_t *counter);

#endif /* COUNTER_H_ */
