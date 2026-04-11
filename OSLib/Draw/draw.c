#include "draw.h"
#include "../../OpenKernel/SystemLib/TimeMng/time.h"
#include "../../OpenKernel/SystemLib/SystemIO/io.h"

//extern uint32_t uptime();

volatile unsigned short* vgabuffer = (unsigned short*)VBUFFER;

void vga_draw_scr(int x, int y, char c, unsigned char color) {
    if (x < 0 || x >= VWIDTH || y < 0 || y >= VHEIGHT) {
        return;
    }
    vgabuffer[y * VWIDTH + x] = (color << 8) | c;   
}

void vga_draw_scr_bar(const char *mode ,const char* text) {
    if (mode[0] == 'B') {
        int y = VHEIGHT - 1;
        for (int x = 0; x < VWIDTH; x++) {
            vga_draw_scr(x, y, ' ', 0x7F);
        }
        int i = 0;
        while (text[i] && i < VWIDTH)
        {
            vga_draw_scr(i, y, text[i], 0x7F);
            i++;
        }
    } else if (mode[0] == 'T') {
        int y = 0;
        for (int x = 0; x < VWIDTH; x++) {
            vga_draw_scr(x, y, ' ', 0x7F);
        }

        // Yazıyı bas
        int i = 0;
        while (text[i] && i < VWIDTH) {
            vga_draw_scr(i, y, text[i], 0x7F);
            i++;
        }
    }
}

#define RTC_ADDR 0x70
#define RTC_DATA 0x71

void itoa2(int val, char* buf) {
    buf[0] = '0' + (val / 10);
    buf[1] = '0' + (val % 10);
}

static uint8_t rtc_read(uint8_t reg) {
    outb(RTC_ADDR, reg);
    return inb(RTC_DATA);
}

static uint8_t bcd_to_bin(uint8_t val) {
    return ((val / 16) * 10) + (val & 0x0F);
}

void vga_draw_uptime() {
    char uptime_str[9]; // HH:MM:SS
    uint8_t sec, min, hour, day, month, year;
    sec = rtc_read(0x00);
    min = rtc_read(0x02);
    hour = rtc_read(0x04);
    day = rtc_read(0x07);
    month = rtc_read(0x08);
    year = rtc_read(0x09);

    sec = bcd_to_bin(sec);
    min = bcd_to_bin(min);
    hour = bcd_to_bin(hour);
    day = bcd_to_bin(day);
    month = bcd_to_bin(month);
    year = bcd_to_bin(year);

    sys_time.hours = hour;
    sys_time.minutes = min;
    sys_time.seconds = sec;
    sys_time.day = day;
    sys_time.month = month;
    sys_time.year = year + 2000;

    // HH
    itoa2(hour, &uptime_str[0]);
    uptime_str[2] = ':';
    // MM
    itoa2(min, &uptime_str[3]);
    uptime_str[5] = ':';
    // SS
    itoa2(sec, &uptime_str[6]);
    uptime_str[8] = '\0';

    int x = VWIDTH - 8;
    int y = 0;

    for (int i = 0; i < 8; i++) {
        vga_draw_scr(x + i, y, uptime_str[i], 0x7F);
    }
}