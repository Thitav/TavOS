#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "display.h"
#include "../std/string.h"
#include "../std/int.h"
#include "../std/mem.h"

int lowercase = 1;
int key_offset = 0;
char key_buffer[256];

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

void input(char *msg, char *dest)
{
  print(msg);

  int last_offset = key_offset;
  char result_buffer[256] = "";

  while (1)
  {
    char scancode = key_buffer[key_offset - 1];

    if (last_offset == key_offset)
    {
      continue;
    }

    if (scancode == ENTER)
    {
      memcpy(result_buffer, dest, sizeof(result_buffer));
      print_nl();
      return;
    }
    else if (scancode == BACKSPACE)
    {
      if (strrm(result_buffer))
      {
        print_backspace();
      }
    }
    else
    {
      char letter = sc_ascii[scancode];

      if (lowercase)
      {
        letter = tolower(letter);
      }

      strappend(result_buffer, letter);
      char str[] = {letter, '\0'};
      print(str);
    }
    last_offset = key_offset;
  }
}

void keyboard_callback(registers_t *regs)
{
  uint8_t scancode = byte_in(0x60);

  if (scancode > SC_MAX)
  {
    return;
  }

  if (scancode == CAPS)
  {
    lowercase = !lowercase;
  }
  else
  {
    strappend(key_buffer, scancode);
    key_offset++;
  }
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, keyboard_callback);
}
