#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "display.h"
#include "../utils.h"

char key_buffer[256];
keyboard_event_t *events[10];

char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                   "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                   "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                   "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                   "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                   "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                   '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                   'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                   'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                   'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void register_keyboard_event(uint8_t scancode, keyboard_handler_t handler)
{
  keyboard_event_t event;
  event.scancode = scancode;
  event.handler = handler;
  events[0] = &event;
  print("DJASDJAJKb\n");
}

void keyboard_callback(registers_t *regs)
{
  uint8_t scancode = byte_in(0x60);

  for (int i = 0; i < 10; i++)
  {
    if (events[i]->scancode == scancode)
    {
      events[i]->handler();
    }
  }

  if (scancode > SC_MAX)
  {
    return;
  }

  if (scancode == ENTER)
  {
    print_nl();
    key_buffer[0] = '\0';
  }
  else if (scancode == BACKSPACE)
  {
    if (backspace(key_buffer))
    {
      print_backspace();
    }
  }
  else
  {
    char letter = sc_ascii[(int)scancode];
    append(key_buffer, letter);
    char str[2] = {letter, '\0'};
    print(str);
  }
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, keyboard_callback);
}
