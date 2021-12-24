#include "lib/drivers/display.h"
#include "lib/cpu/isr.h"
#include "lib/drivers/keyboard.h"

void test_handler()
{
  print("handler\n");
}

extern void main()
{
  print("Installing interrupt service routines (ISRs)\n");
  isr_install();

  print("Initializing keyboard\n");
  init_keyboard();

  print("Initialization sequence completed\n");
  print_nl();
  print("Tchorbi OS v0.0.1\n");
  print_nl();

  register_keyboard_event(21, &test_handler);
}
