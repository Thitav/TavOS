#include "display.h"
#include "ports.h"
#include "../std/mem.h"

void set_cursor(int offset)
{
  offset /= 2;

  byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  byte_out(VGA_DATA_REGISTER, high_8(offset));
  byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  byte_out(VGA_DATA_REGISTER, low_8(offset));
}

int get_cursor()
{
  byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
  int offset = byte_in(VGA_DATA_REGISTER) << 8;
  byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
  offset += byte_in(VGA_DATA_REGISTER);
  return offset * 2;
}

void vmem_set_char(char c, int offset)
{
  char *vmem = (char *)VIDEO_ADDRESS;
  vmem[offset] = c;
  vmem[offset + 1] = 0x0f;
}

int get_offset(int col, int row)
{
  return 2 * (row * MAX_COLS + col);
}

int get_row_from_offset(int offset)
{
  return offset / (2 * MAX_COLS);
}

int get_nl_offset(int offset)
{
  return get_offset(0, get_row_from_offset(offset) + 1);
}

int scroll_nl(int offset)
{
  memcpy(
      (uint8_t *)(get_offset(0, 1) + VIDEO_ADDRESS),
      (uint8_t *)(get_offset(0, 0) + VIDEO_ADDRESS),
      MAX_COLS * (MAX_ROWS - 1) * 2);

  for (int col = 0; col < MAX_COLS; col++)
  {
    vmem_set_char(' ', get_offset(col, MAX_ROWS - 1));
  }

  return offset - 2 * MAX_COLS;
}

void print(char *str)
{
  int offset = get_cursor();
  int i = 0;

  while (str[i] != '\0')
  {
    if (offset >= MAX_ROWS * MAX_COLS * 2)
    {
      offset = scroll_nl(offset);
    }

    if (str[i] == '\n')
    {
      offset = get_nl_offset(offset);
    }
    else
    {
      vmem_set_char(str[i], offset);
      offset += 2;
    }

    i++;
  }

  set_cursor(offset);
}

void print_nl()
{
  int newOffset = get_nl_offset(get_cursor());
  if (newOffset >= MAX_ROWS * MAX_COLS * 2)
  {
    newOffset = scroll_nl(newOffset);
  }
  set_cursor(newOffset);
}

void clear_screen()
{
  int screen_size = MAX_COLS * MAX_ROWS;

  for (int i = 0; i < screen_size; i++)
  {
    vmem_set_char(' ', i * 2);
  }

  set_cursor(get_offset(0, 0));
}

void print_backspace()
{
  int new_cursor = get_cursor() - 2;
  vmem_set_char(' ', new_cursor);
  set_cursor(new_cursor);
}
