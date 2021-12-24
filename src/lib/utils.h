#ifndef UTILS_H
#define UTILS_H

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

#define high_16(address) (uint16_t)(((address) >> 16) & 0xffff)
#define low_16(address) (uint16_t)((address)&0xffff)
#define high_8(address) (uint8_t)(((address) >> 8) & 0xff)
#define low_8(address) (uint8_t)((address)&0xff)

void memcpy(uint8_t *source, uint8_t *dest, uint32_t nbytes);
void strrev(char str[]);
void its(int n, char str[]);
void append(char str[], char n);
int strlen(char str[]);
int backspace(char str[]);

#endif
