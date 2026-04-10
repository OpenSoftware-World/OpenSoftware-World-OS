#include "ata.h"
#include "../../SystemLib/SystemIO/io.h"

static void ata_wait_busy() {
    while (inb(ATA_STATUS) & ATA_STATUS_BSY);
}

static void ata_wait_drq() {
    while(!(inb(ATA_STATUS) & ATA_STATUS_DRQ));
}

void ata_sys_disk_init() {

}

void ata_sys_disk_read(uint32_t lba, uint8_t* buffer) {
    ata_wait_busy();

    outb(ATA_DRIVE_SELECT, 0x0E | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT, 1);

    outb(ATA_LBA_LOW, (uint8_t)(lba));
    outb(ATA_LBA_MID, (uint8_t)(lba >> 8));
    outb(ATA_LBA_HIGH, (uint8_t)(lba >> 16));

    outb(ATA_COMMAND, ATA_READ);

    ata_wait_busy();
    ata_wait_drq();

    for (int i = 0; i < 256; i++) {
        ((uint16_t*)buffer)[i] = inw(ATA_DATA);
    }
}

void ata_sys_disk_write(uint32_t lba, const uint8_t* buffer) {
    ata_wait_busy();

    outb(ATA_DRIVE_SELECT, 0x0E | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT, 1);

    outb(ATA_LBA_LOW, (uint8_t)(lba));
    outb(ATA_LBA_MID, (uint8_t)(lba >> 8));
    outb(ATA_LBA_HIGH, (uint8_t)(lba >> 16));

    outb(ATA_COMMAND, ATA_WRITE);

    ata_wait_busy();
    ata_wait_drq();

    for (int i = 0; i < 256; i++) {
        outw(ATA_DATA, ((uint16_t*)buffer)[i]);
    }
}