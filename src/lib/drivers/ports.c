#include "ports.h"

uint8_t byte_in(uint16_t port)
{
  uint8_t result;
  asm("in %%dx, %%al"
      : "=a"(result)
      : "d"(port));
  return result;
}

void byte_out(uint16_t port, uint8_t data)
{
  asm("out %%al, %%dx"
      :
      : "a"(data), "d"(port));
}
