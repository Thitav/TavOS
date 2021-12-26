#include "mem.h"

void memcpy(uint8_t *src, uint8_t *dest, uint32_t nbytes)
{
  for (int i = 0; i < nbytes; i++)
  {
    *(dest + i) = *(src + i);
  }
}
