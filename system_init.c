#include "OpenKernel/Drivers/Vga/vga.h"
#include "OpenKernel/SystemLib/SysCalls/basic_syscall.h"
#include "OpenKernel/SystemLib/KernelFunc/kernel_func.h"
#include "OpenKernel/SystemLib/TimeMng/time.h"
#include "OpenKernel/OFS/ofs.h"
#include "OSLib/CreateSystemFile/sys_file.h"

void system_init()
{
    // The system is starting up and displaying log messages
    vga_init();
    sleep(30);
    ofs_init();
    create_system_file();
    log_message("S", "System disk read successful; loading the kernel...");
    sleep(30);
    log_message("I", "Kernel initialized successfully.");
    sleep(20);
    log_message("I", "VGA Driver initalized successfully.");
    sleep(10);
    log_message("I", "RTC Services initalized successfully.");
    sleep(10);
    log_message("I", "Shell initalized successfully.");
    sleep(5);
    log_message("W", "Since this system is still new, there may be some glitches.");
    sleep(15);
    log_message("U", "The hardware status is unknown.");
    sleep(25);
    log_message("S", "The system is ready to start; the system is starting.");
    sleep(100);

    // Jump to the main menu
    exec_func("os_start");
}