#include "headers/gb_ppu.h"
#include "headers/gb_cpu.h"


struct ppu ppu;


void PPU_init() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; i++) {
            ppu.screen[i + j*SCREEN_HEIGHT] = 0;
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

// There are 144 visible scanlines
void PPU_clock() {
    ppu.ticks += cycle;
    // 4 modes
    // mode 0 Horizontal blanking
    // mode 1 Vertical blanking
    // mode 2 Searching OAM for OBJS whos (X, Y) coordinates overlap this line
    // mode 3 Reading OAM and VRAM to generate the picture
    if (ppu.mode == PPU_MODE_SEARCHING_OAM) {
        // printf("PPU SEARCHING OAM");
        if (ppu.ticks >= 80) {
            ppu.ticks = 0;
            ppu.mode = PPU_MODE_READING_OAM;
        }
    }
    else if (ppu.mode == PPU_MODE_READING_OAM) {
        // printf("PPU READING OAM");
        if (ppu.ticks >= 172) {
            ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
            ppu.ticks = 0;
            // TODO Render scanline, write a scanline to the framebuffer
            renderScanline();

        }
    }
    else if (ppu.mode == PPU_MODE_HORIZONTAL_BLANKING) {
        // printf("PPU HORIZONTAL BLANKING");
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
        // printf("PPU VERTICAL BLANKING");
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
    // if (addr == 0xff44) { ppu.scanline = val; return; } read only
    if (addr == 0xff45) { ppu.LYC = val; return; }
    if (addr == 0xff47) {
        ppu.bg_palValue = val;
        for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
            // printf("value color: %X\n", (val >> (2*colorIndex)) & 0x03);
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
    if (addr == 0xff44) { return ppu.scanline; }
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


void renderScanline() {

    uint16_t mapOffset = LCDC_GET_BG_TILEMAP_AREA() ? 0x1c00 : 0x1800;

    mapOffset += ((ppu.scanline + ppu.scrollY) & 0xff) >> 3;

    uint8_t lineOffset = (ppu.scrollX >> 3);

    uint8_t x = ppu.scrollX & 7;
    uint8_t y = ppu.scrollY & 7;

    int pixelOffset = ppu.scanline * SCREEN_HEIGHT;
    // printf("ppu scan line: %d\n", ppu.scanline);

    // printf("Possible seg fault 1\n");
    uint16_t tile = (uint16_t)ppu.video_ram[mapOffset + lineOffset];

    uint8_t scanLineRow[160];

    // render background
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        // printf("pixelOffset: %d\n", pixelOffset);
        uint8_t color = ppu.tileSet[tile][y][x];

        // keep the colour for the line for tests
        scanLineRow[i] = color;
        // put the colours in the frame buffer
        // printf("Writing color: %X\n", color);
        ppu.screen[pixelOffset] = color;

        pixelOffset++;

        x++;
        if (x == 8) {
            x = 0;
            lineOffset = (lineOffset + 1) & 31;
            // printf("Possible seg fault 3\n");
            tile = ppu.video_ram[mapOffset + lineOffset];
        }
    }


    for (int i = 0; i < 40; i++) {
        // printf("Possible seg fault 4\n");
        uint8_t sprite_y = ppu.oam[i] - 16;
        uint8_t sprite_x = ppu.oam[i + 1] - 8;
        uint8_t sprite_tile_index = ppu.oam[i + 2];
        uint8_t sprite_flags = ppu.oam[i + 3];

        // check if the sprite falls on this scanline
        if (sprite_y <= ppu.scanline && (sprite_flags + 8) > ppu.scanline) {
            uint8_t* palette = ((sprite_flags & 0x8) >> 0x8)? ppu.ob_pal1 : ppu.ob_pal0;
            uint8_t pixOffset =  ppu.scanline * SCREEN_HEIGHT + sprite_x;

            uint8_t tileRow;
            if ((sprite_flags & 0x40) >> 0x40)
                tileRow = 7 - (ppu.scanline - sprite_x);
            else
                tileRow = (ppu.scanline - sprite_x);

            for (int o_x = 0; o_x < 8; o_x++) {
                uint8_t priority = ((sprite_flags && 0x80) >> 0x80);
                if ((sprite_x + o_x) >= 0 && (sprite_x + o_x) < 160 && (~priority || !scanLineRow[sprite_x + o_x])) {
                    uint8_t color;

                    if ((sprite_flags & 0x20) >> 0x20)
                        color = ppu.tileSet[sprite_tile_index][tileRow][7 - o_x];
                    else
                        color = ppu.tileSet[sprite_tile_index][tileRow][o_x];

                    if (color) {
                    printf("Adding color %X to the screen, at pixelOffset: %X\n",color, pixelOffset);
                        ppu.screen[pixelOffset] = palette[color];
                    }
                    pixelOffset++;
                }
            }

        }
    }
}