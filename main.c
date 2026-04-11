#include "OpenKernel/SystemLib/Std/types.h"
#include "OpenKernel/Drivers/Vga/vga.h"
#include "OpenKernel/SystemLib/SysCalls/basic_syscall.h"
#include "OpenKernel/SystemLib/TimeMng/time.h"
#include "OSServices/Shell/shell.h"
#include "Boot/Mboot_desc/os_boot_desc.h"
#include "OSLib/Draw/draw.h"

void os_main(void)
{
    // Main menu
    vga_set_color_scheme(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
    vga_clear_screen("F");
    vga_draw_scr_bar("T", "Welcome to OpenSoftware-World OS!");
    vga_newline();
    vga_print_scr_nw("Welcome to OpenSoftware-World OS!");
    vga_print_scr("OpenSoftware-World OS version "); vga_print_scr_nw(OS_VER);
    log_message("W", "Due to certain issues related to OpenKernel, some commands may not work.");
    vga_draw_scr_bar("B", "OpenSoftware-World OS 2.0");
    vga_draw_uptime();

    // Shell is starting
    vga_newline();
    vga_set_cursor(12, 4);
    shell_init();
}