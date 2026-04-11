#include "OpenKernel/SystemLib/Std/types.h"
#include "OpenKernel/Drivers/Vga/vga.h"
#include "OpenKernel/SystemLib/SysCalls/basic_syscall.h"
#include "OpenKernel/SystemLib/TimeMng/time.h"
#include "OSServices/Shell/shell.h"
#include "Boot/Mboot_desc/os_boot_desc.h"

void os_main(void)
{
    // Main menu
    vga_set_color_scheme(VGA_COLOR_BLUE, VGA_COLOR_WHITE);
    vga_clear_screen("F");
    vga_print_scr_nw("Welcome to the OpenSoftware-World OS!");
    vga_print_scr("OpenSoftware-World OS version "); vga_print_scr_nw(OS_VER);

    // Shell is starting
    vga_newline();
    vga_set_cursor(12, 4);
    shell_init();
}