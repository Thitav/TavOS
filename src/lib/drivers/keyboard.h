#ifndef KEYBOARD_H
#define KEYBOARD_H

#define BACKSPACE 0x0e
#define ENTER 0x1c
#define CAPS 0x3a
#define SC_MAX 0x3a

void input(char *msg, char *dest);
void init_keyboard();

#endif
