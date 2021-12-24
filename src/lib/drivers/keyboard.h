#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../utils.h"

#define BACKSPACE 0x0e
#define ENTER 0x1c
#define SC_MAX 58

typedef void (*keyboard_handler_t)();
typedef struct
{
  uint8_t scancode;
  keyboard_handler_t handler;
} keyboard_event_t;

void init_keyboard();
void register_keyboard_event(uint8_t scancode, keyboard_handler_t handler);

#endif
