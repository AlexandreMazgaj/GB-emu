#pragma once

#include <stdint.h>
#include "constants.h"

// 0xFF40
#define LCDC_GET_LCDPPU_ENABLE() ((ppu.reg_lcdc & (1 << 7)) >> 7)
#define LCDC_GET_WINDOW_TILEMAP_AREA() ((ppu.reg_lcdc & (1 << 6)) >> 6)
#define LCDC_GET_WINDOW_ENABLE() ((ppu.reg_lcdc & (1 << 5)) >> 5)
#define LCDC_GET_BGWINDOW_TILEDATA_AREA() ((ppu.reg_lcdc & (1 << 4)) >> 4)
#define LCDC_GET_BG_TILEMAP_AREA() ((ppu.reg_lcdc & (1 << 3)) >> 3)
#define LCDC_GET_OBJ_SIZE() ((ppu.reg_lcdc & (1 << 2)) >> 2)
#define LCDC_GET_OBJ_ENABLE() ((ppu.reg_lcdc & (1 << 1)) >> 1)
#define LCDC_GET_BGWINDOW_PRIORITY() (ppu.reg_lcdc & 1)


// 0xFF41
// #define STAT_GET


struct ppu {
    uint8_t oam[OAM_SIZE];

    uint8_t reg_lcdc;
    uint8_t reg_stat;

    uint8_t scrollX;
    uint8_t scrollY;

    uint8_t LY;
    uint8_t LYC;
    uint8_t WY;
    uint8_t WX;

} extern ppu;


void writePPU(uint16_t addr, uint8_t val);