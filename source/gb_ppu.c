#include "headers/gb_ppu.h"


struct ppu ppu;


void PPU_init() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; i++) {
            ppu.screen[i][j] = 0;
        }
    }
}


void writePPU(uint16_t addr, uint8_t val) {
    if (addr == 0xff40) { ppu.reg_lcdc = val; return; }
    if (addr == 0xff41) { ppu.reg_stat = val; return; }
    if (addr == 0xff42) { ppu.scrollY = val; return; }
    if (addr == 0xff43) { ppu.scrollX = val; return; }
    // if (addr == 0xff44) { ppu.LY = val; return; } read only
    if (addr == 0xff45) { ppu.LYC = val; return; }
    if (addr == 0xff47) {
        ppu.bg_palValue = val;
        for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
            ppu.bg_pal[colorIndex] = getGBColorFromValue((val >> (2*colorIndex)) & 0x03);
        }
    }
    if (addr == 0xff48) {
        ppu.ob_pal0Value = val;
        for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
            ppu.ob_pal0[colorIndex] = getGBColorFromValue((val >> (2*colorIndex)) & 0x03);
        }
    }
    if (addr == 0xff49) {
        ppu.ob_pal1Value = val;
        for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
            ppu.ob_pal1[colorIndex] = getGBColorFromValue((val >> (2*colorIndex)) & 0x03);
        }
    }
    if (addr == 0xff4a) { ppu.WY = val; return; }
    if (addr == 0xff4b) { ppu.WX = val; return; }
}


uint8_t readPPU(uint16_t addr) {
    if (addr == 0xff40) { return ppu.reg_lcdc; }
    if (addr == 0xff41) { return ppu.reg_stat; }
    if (addr == 0xff42) { return ppu.scrollY; }
    if (addr == 0xff43) { return ppu.scrollX; }
    if (addr == 0xff44) { return ppu.LY; }
    if (addr == 0xff45) { return ppu.LYC; }
    if (addr == 0xff47) { return ppu.bg_palValue; }
    if (addr == 0xff48) { return ppu.ob_pal0Value; }
    if (addr == 0xff49) { return ppu.ob_pal1Value; }
    if (addr == 0xff4a) { return ppu.WY; }
    if (addr == 0xff4b) { return ppu.WX; }
}


uint8_t getGBColorFromValue(uint8_t val) {
    if (val == 0) return 255;
    if (val == 1) return 192;
    if (val == 2) return 96;
    if (val == 3) return 0;
}