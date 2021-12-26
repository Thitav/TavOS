#ifndef INT_H
#define INT_H

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

#define high_8(address) (uint8_t)(((address) >> 8) & 0xff)
#define low_8(address) (uint8_t)((address)&0xff)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xffff)
#define low_16(address) (uint16_t)((address)&0xffff)

#endif
