#ifndef SYS_FILE_H
#define SYS_FILE_H

#include "../../OpenKernel/OFS/ofs.h"
#include "../../OpenKernel/SystemLib/Std/types.h"
#include "../../OpenKernel/SystemLib/TimeMng/time.h"
#include "../../Boot/Mboot_desc/os_boot_desc.h"
#include "../../OpenKernel/Kernel/openkernel_information.h"

void create_system_file() {

    // File System Information
    sleep(1);

    uint8_t buf[512] = "File System Name: OpenFileSystem (OFS)";
    ofs_create_file("/OFS/ofs_name.info", 512);
    ofs_write_file("/OFS/ofs_name.info", buf, 512);

    sleep(1);

    uint8_t buf2[512] = "File System Version: 1.0";
    ofs_create_file("/OFS/ofs_version.info", 512);
    ofs_write_file("/OFS/ofs_version.info", buf2, 512);

    sleep(1);

    // Bootloader Information

    uint8_t buf3[512] = OS_BOOTLDR_NAME " " OS_BOOTLDR_VER;
    ofs_create_file("/Boot/bootldr.info", 512);
    ofs_write_file("/Boot/bootldr.info", buf3, 512);

    sleep(1);

    // System Information

    uint8_t buf4[512] = KRNL_NAME " " KRNL_VER " (" KRNL_ARCH ") - Last Commit: " KRNL_LAST_COMMIT;
    ofs_create_file("/System/Kernel/krnl.info", 512);
    ofs_write_file("/System/Kernel/krnl.info", buf4, 512);

    sleep(1);

    uint8_t buf5[512] = OS_NAME " " OS_VER;
    ofs_create_file("/System/system.info", 512);
    ofs_write_file("/System/system.info", buf5, 512);

    // Include Apps

    sleep(1);

    ofs_create_file("Apps/TestApp/test_app.app", 512);
    sleep(1);
    ofs_create_file("Apps/HelloWorld/hello.app", 512);
    sleep(1);
}

#endif