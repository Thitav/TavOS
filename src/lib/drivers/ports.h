#ifndef PORTS_H
#define PORTS_H

#include "../std/int.h"

uint8_t byte_in(uint16_t port);
void byte_out(uint16_t port, uint8_t data);

#endif
