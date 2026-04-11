#include "shell.h"
#include "command_ls.h"
#include "../../OpenKernel/Drivers/Vga/vga.h"
#include "../../OpenKernel/SystemLib/SysCalls/basic_syscall.h"
#include "../../OpenKernel/SystemLib/TimeMng/time.h"
#include "../../OpenKernel/SystemLib/SystemIO/io.h"
#include "../../OpenKernel/Drivers/Keyboard/keyboard.h"
#include "../../OpenKernel/SystemLib/Std/std.h"
#include "../../OpenKernel/Kernel/KernelServices/SystemManagement/sysmng.h"
#include "../../OpenKernel/Kernel/openkernel_information.h"
#include "../../Boot/Mboot_desc/os_boot_desc.h"
#include "../../OpenKernel/Drivers/Cpu/cpu.h"
#include "../../OpenKernel/SystemLib/Memory/mem.h"
#include "../../OpenKernel/OFS/ofs.h"

void shell_inp() {
    vga_set_text_color(VGA_COLOR_GREEN);
    vga_print_scr("root");
    vga_set_text_color(VGA_COLOR_WHITE);
    vga_print_scr("@");
    vga_set_text_color(VGA_COLOR_CYAN);
    vga_print_scr("shell");
    vga_set_text_color(VGA_COLOR_WHITE);
    vga_print_scr("> ");
}

void shell_init() {
    char cmd[MAX_CMD_LEN];
    uint8_t idx = 0;

    shell_inp();

    while (1) {
        char c = get_char();

        if (c == '\b') {
            if (idx > 0) {
                idx--;
                vga_bckspc();
            }
        } else if (c == '\n') {
            vga_newline();
            cmd[idx] = 0;
            idx = 0;

            if (strcmp(cmd, LIST_STRING) == 0 || strcmp(cmd, U_LIST_STRING) == 0) {
                vga_print_scr("Commands: clear, cls, list, seqlist, ver, shellinfo, osfetch, shutdown, reboot, time, version, echo, cpuinfo, help, diskinfo, sysinfo, dir, ls, copy, ren, del, cat, size\n");
            } else if (strcmp(cmd, SEQLIST_STRING) == 0 || strcmp(cmd, U_SEQLIST_STRING) == 0) {
                vga_print_scr_nw("Commands:");
                vga_print_scr("clear,"); vga_print_scr_nw(" cpuinfo");
                vga_print_scr("cls,"); vga_print_scr_nw(" help");
                vga_print_scr("list,"); vga_print_scr_nw(" diskinfo");
                vga_print_scr("seqlist,"); vga_print_scr_nw(" sysinfo");
                vga_print_scr("ver,"); vga_print_scr_nw(" dir");
                vga_print_scr("shellinfo,"); vga_print_scr_nw(" ls");
                vga_print_scr("osfetch,"); vga_print_scr_nw(" copy");
                vga_print_scr("shutdown,"); vga_print_scr_nw(" ren");
                vga_print_scr("reboot,"); vga_print_scr_nw(" del");
                vga_print_scr("time,"); vga_print_scr_nw(" cat");
                vga_print_scr("version,"); vga_print_scr_nw(" size");
                vga_print_scr_nw("echo");
                log_message("W", "Due to certain issues related to OpenKernel, some commands may not work.");
            } else if (strcmp(cmd, OSFETCH_STRING) == 0 || strcmp(cmd, U_OSFETCH_STRING) == 0) {
                
                vga_print_scr_nw("  ____   _____      root@shell");
                vga_print_scr_nw(" / __ \\ / ___/      ----------");
                vga_print_scr("| |  | | \\__ \\      OS: "); vga_print_scr(OS_NAME); vga_print_scr(" "); vga_print_scr_nw(OS_VER);
                vga_print_scr("| |  | |___/  /     Kernel: "); vga_print_scr(KRNL_NAME); vga_print_scr(" "); vga_print_scr_nw(KRNL_VER);
                vga_print_scr("| |  | |___/  /     Bootloader Name: "); vga_print_scr_nw(OS_BOOTLDR_NAME);
                vga_print_scr("| |   | ___/  /     Bootloader version: "); vga_print_scr_nw(OS_BOOTLDR_VER);
                vga_print_scr(" \\____/|_____/      Architecture: "); vga_print_scr_nw(KRNL_ARCH);
                vga_print_scr("                    Shell: "); vga_print_scr(OS_SHELL_NAME); vga_print_scr(" "); vga_print_scr_nw(OS_SHELL_VER);
            } else if (strcmp(cmd, CLEAR_STRING) == 0 || strcmp(cmd, CLS_STRING) == 0 || strcmp(cmd, U_CLEAR_STRING) == 0 || strcmp(cmd, U_CLS_STRING) == 0) {
                vga_clear_screen("C");
            } else if (strcmp(cmd, TIME_STRING) == 0 || strcmp(cmd, U_TIME_STRING) == 0) {
                print_time();
            } else if (strncmp(cmd, ECHO_STRING, 5) == 0 || strncmp(cmd, U_ECHO_STRING, 5) == 0) {
                vga_print_scr(cmd + 5);
                vga_newline();
            } else if (strcmp(cmd, SHELLINFO_STRING) == 0 || strcmp(cmd, U_SHELLINFO_STRING) == 0) {
                vga_print_scr_nw("OpenSoftware-World Shell 1.1");
            } else if (strcmp(cmd, SHUTDOWN_STRING) == 0 || strcmp(cmd, U_SHUTDOWN_STRING) == 0) {
                sys_next_status("S", 0);
            } else if (strcmp(cmd, REBOOT_STRING) == 0 || strcmp(cmd, U_REBOOT_STRING) == 0) {
                sys_next_status("R", 0);
            } else if (strcmp(cmd, VERSION_STRING) == 0 || strcmp(cmd, VER_STRING) == 0 || strcmp(cmd, U_VERSION_STRING) == 0 || strcmp(cmd, U_VER_STRING) == 0) {
                vga_print_scr(OS_NAME); vga_print_scr(" "); vga_print_scr(OS_VER);
                vga_newline();
            } else if (strcmp(cmd, CPUINFO_STRING) == 0 || strcmp(cmd, U_CPUINFO_STRING) == 0) {
                get_sys_cpuinfo("B");
            } else if (strcmp(cmd, HELP_STRING) == 0 || strcmp(cmd, U_HELP_STRING) == 0) {
                vga_print_scr("Type \"list\" for a list of all commands.");
                vga_newline();
            } else if (strcmp(cmd, DISKINFO_STRING) == 0 || strcmp(cmd, U_DISKINFO_STRING) == 0) {
                uint8_t rbuf[512];
                memset(rbuf, 0, 512);
                ofs_read_file("/OFS/ofs_name.info", rbuf);

                for (int i = 0; i < 512; i++) {
                    if (rbuf[i] == 0) break;
                    ptchar(rbuf[i]);
                }
                vga_newline();

                uint8_t rbuf2[512];
                memset(rbuf2, 0, 512);
                ofs_read_file("/OFS/ofs_version.info", rbuf2);

                for (int i = 0; i < 512; i++) {
                    if (rbuf2[i] == 0) break;
                    ptchar(rbuf2[i]);
                }
                vga_newline();

            } else if (strcmp(cmd, SYSINFO_STRING) == 0 || strcmp(cmd, U_SYSINFO_STRING) == 0) {
                vga_print_scr("System Information:");
                vga_newline();
                vga_print_scr("OS: "); vga_print_scr(OS_NAME); vga_print_scr(" "); vga_print_scr_nw(OS_VER);
                vga_print_scr("Kernel: "); vga_print_scr(KRNL_NAME); vga_print_scr(" "); vga_print_scr_nw(KRNL_VER);
                vga_print_scr("Architecture: "); vga_print_scr_nw(KRNL_ARCH);
                vga_print_scr("Shell: "); vga_print_scr(OS_SHELL_NAME); vga_print_scr(" "); vga_print_scr_nw(OS_SHELL_VER);
                
                uint8_t rbuf[512];
                memset(rbuf, 0, 512);
                ofs_read_file("/OFS/ofs_name.info", rbuf);

                for (int i = 0; i < 512; i++) {
                    if (rbuf[i] == 0) break;
                    ptchar(rbuf[i]);
                }
                vga_newline();

                uint8_t rbuf2[512];
                memset(rbuf2, 0, 512);
                ofs_read_file("/OFS/ofs_version.info", rbuf2);

                for (int i = 0; i < 512; i++) {
                    if (rbuf2[i] == 0) break;
                    ptchar(rbuf2[i]);
                }
                vga_newline();

                get_sys_cpuinfo("B");
                vga_newline();
            } else if (strcmp(cmd, DIR_STRING) == 0 || strcmp(cmd, U_DIR_STRING) == 0 || strcmp(cmd, LS_STRING) == 0 || strcmp(cmd, U_LS_STRING) == 0) {
                ofs_list_files();
            } else if (strncmp(cmd, COPY_STRING, 5) == 0 || strncmp(cmd, U_COPY_STRING, 5) == 0) {

            } else if (strncmp(cmd, REN_STRING, 4) == 0 || strncmp(cmd, U_REN_STRING, 4) == 0) {
                
            } else if (strncmp(cmd, DEL_STRING, 4) == 0 || strncmp(cmd, U_DEL_STRING, 4) == 0) {
                ofs_delete_file(cmd + 4);
            } else if (strncmp(cmd, CAT_STRING, 10) == 0 || strncmp(cmd, U_CAT_STRING, 4) == 0) {
                uint8_t rbuf[512];
                memset(rbuf, 0, 512);
                ofs_read_file(cmd + 10, rbuf);

                for (int i = 0; i < 512; i++) {
                    if (rbuf[i] == 0) break;
                    ptchar(rbuf[i]);
                }
                vga_newline();
            } else if (strncmp(cmd, SIZE_STRING, 5) == 0 || strncmp(cmd, U_SIZE_STRING, 5) == 0) {
                
            } else if (strcmp(cmd, "") == 0) {
                vga_print_scr("");
            }
            else {
                vga_print_scr_nw("The command you entered could not be found. Please type list for a list of all commands.");
            }

            shell_inp();
        } else {
            if (idx < MAX_CMD_LEN - 1) {
                cmd[idx++] = c;
                ptchar(c);
            }
        }
    }
}