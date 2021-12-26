#include "lib/drivers/display.h"
#include "lib/cpu/isr.h"
#include "lib/drivers/keyboard.h"
#include "lib/std/string.h"

extern void main()
{
  print("Installing interrupt service routines (ISRs)\n");
  isr_install();

  print("Initializing keyboard\n");
  init_keyboard();

  print("Initialization sequence completed\n");
  print_nl();
  print("TavOS v0.0.1\n");
  print_nl();

  while (1)
  {
    char cmd[256];
    input("> ", cmd);

    if (strcmp(cmd, "clear"))
    {
      clear_screen();
    }
    else
    {
      print("Unknown command\n");
    }
  }
}
