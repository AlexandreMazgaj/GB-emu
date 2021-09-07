#pragma once

#include <stdint.h>
#include "constants.h"

// PPPU Modes
#define PPU_MODE_HORIZONTAL_BLANKING 0
#define PPU_MODE_VERTICAL_BLANKING 1
#define PPU_MODE_SEARCHING_OAM 2
#define PPU_MODE_READING_OAM 3


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

    uint8_t screen[SCREEN_HEIGHT * SCREEN_WIDTH];

    uint8_t oam[OAM_SIZE];
    uint8_t video_ram[RAM_SIZE];


    uint8_t tileSet[TILE_SET_SIZE][8][8];

    uint8_t reg_lcdc;
    uint8_t reg_stat;

    uint8_t scrollX;
    uint8_t scrollY;

    // scan line compare
    uint8_t LYC;
    uint8_t WY;
    uint8_t WX;

    // to manage the cycle
    uint8_t mode;
    uint8_t ticks;
    uint8_t scanline;


    // Color palettes

    uint8_t bg_pal[3];
    uint8_t ob_pal0[3];
    uint8_t ob_pal1[3];

    uint8_t bg_palValue;
    uint8_t ob_pal0Value;
    uint8_t ob_pal1Value;

} extern ppu;


void PPU_init();


void PPU_clock();

void writePPU(uint16_t addr, uint8_t val);

void updateTile(uint16_t addr, uint8_t val);

uint8_t readPPU(uint16_t addr);

uint8_t getGBColorFromValue(uint8_t val);

void renderScanline();