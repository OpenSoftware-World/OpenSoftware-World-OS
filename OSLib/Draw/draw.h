#ifndef DRAW_H
#define DRAW_H

#include "../../OpenKernel/SystemLib/Std/types.h"
#include "../../OpenKernel/Drivers/Vga/vga.h"

void vga_draw_scr(int x, int y, char c, unsigned char color);
void vga_draw_scr_str(int x, int y, const char *str, unsigned char color);
void vga_draw_scr_bar(const char *mode, const char* text);
void vga_draw_uptime();
void itoa2(int val, char* buf);

#endif