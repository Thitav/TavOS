#ifndef DISPLAY_H
#define DISPLAY_H

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_HIGH 0x0e
#define VGA_OFFSET_LOW 0x0f
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

void print(char *str);
void print_nl();
void clear_screen();
void print_backspace();

#endif
