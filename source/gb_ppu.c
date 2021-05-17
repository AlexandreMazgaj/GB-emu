#include "headers/gb_ppu.h"
#include "headers/gb_cpu.h"


struct ppu ppu;


void PPU_init() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; i++) {
            ppu.screen[i][j] = 0;
        }
    }

    ppu.mode = PPU_MODE_SEARCHING_OAM;
    ppu.ticks = 0;

    for (int i = 0; i < TILE_SET_SIZE; i++) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++)
                ppu.tileSet[i][x][y] = 0;
        }
    }
}


void PPU_clock() {
    ppu.ticks += cycle;
    // 4 modes
    // mode 0 Horizontal blanking
    // mode 1 Vertical blanking
    // mode 2 Searching OAM for OBJS whos (X, Y) coordinates overlap this line
    // mode 3 Reading OAM and VRAM to generate the picture
    if (ppu.mode == PPU_MODE_SEARCHING_OAM) {
        if (ppu.ticks >= 80) {
            ppu.ticks = 0;
            ppu.mode = PPU_MODE_READING_OAM;
        }
    }
    else if (ppu.mode == PPU_MODE_READING_OAM) {
        if (ppu.ticks >= 172) {
            ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
            ppu.ticks = 0;
            // TODO Render scanline, write a scanline to the framebuffer
        }
    }
    else if (ppu.mode == PPU_MODE_HORIZONTAL_BLANKING) {
        if (ppu.ticks >= 204) {
            ppu.scanline++;
            ppu.ticks = 0;
            if (ppu.scanline == 143) {
                // enter vblank
                ppu.mode = PPU_MODE_VERTICAL_BLANKING;
                // put image data
            }
            else {
                ppu.mode = PPU_MODE_SEARCHING_OAM;
            }
        }
    }
    else if (ppu.mode = PPU_MODE_VERTICAL_BLANKING) {
        if (ppu.ticks >= 456) {
            ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
            ppu.scanline++;
            if (ppu.scanline > 153) {
                // restart scanning modes
                ppu.mode = PPU_MODE_SEARCHING_OAM;
                ppu.scanline = 0;
            }
        }
    }

}


void updateTile(uint16_t addr, uint8_t val) {
    printf("Going through the update tile function\n");
    // get the base address for this tile row
    addr &= 0x1ffe;

    // get which tile and row is updated
    uint16_t tile = (addr >> 4) & 511;
    uint8_t y = (uint8_t)((addr >> 1) & 7);

    for (uint8_t x = 0; x < 8; x++) {
        uint8_t sx = 1 << (7-x);
        ppu.tileSet[tile][y][x] = ((ppu.video_ram[addr] & sx) ? 1 : 0) +
                                  ((ppu.video_ram[addr + 1] & sx) ? 2 : 0);
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
            printf("value color: %X\n", (val >> (2*colorIndex)) & 0x03);
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