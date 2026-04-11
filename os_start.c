#include "OpenKernel/Drivers/Vga/vga.h"
#include "OpenKernel/SystemLib/TimeMng/time.h"
#include "OpenKernel/SystemLib/KernelFunc/kernel_func.h"

void os_start()
{
    vga_set_text_color(VGA_COLOR_WHITE);
    vga_clear_screen("F");
    vga_print_scr_nw("OpenSoftware-World OS 2.0 is starting.");
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(5);
    vga_print_scr("=");
    sleep(10);

    exec_func("os_main");
}