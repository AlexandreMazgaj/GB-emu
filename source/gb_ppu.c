#include "headers/gb_ppu.h"
#include "headers/gb_cpu.h"
#include <stdlib.h>


struct ppu ppu;
struct pixelFetcher pixelFetcher;


void PPU_init() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            ppu.screen[i + j*SCREEN_HEIGHT] = 0;
        }
    }

    ppu.mode = PPU_MODE_OAM_SCAN;
    ppu.ticks = 0;
    ppu.scrollX = 0;
    ppu.scrollY = 0;
    ppu.scanline = 0;

    for (int i = 0; i < TILE_SET_SIZE; i++) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++)
                ppu.tileSet[i][x][y] = 0;
        }
    }

    ppu.bgPixelFifo = malloc(sizeof(PixelFifo));
    ppu.spritePixelFifo = malloc(sizeof(PixelFifo));


    pixelFetcher.mode = FETCH_TILE_NO;
    pixelFetcher.ticks = 0;
    pixelFetcher.WLY = 0;
    pixelFetcher.x = 0;
    pixelFetcher.y = 0;
    pixelFetcher.tileId = 0;
    pixelFetcher.hiByte = 0;
    pixelFetcher.loByte = 0;
}

// There are 144 visible scanlines
void PPU_clock() {
    // ppu.ticks += cycle;
    ppu.ticks++;
    // displayVram();
    // printf("ppu ticks: %d\n", ppu.ticks);
    // 4 modes
    // mode 0 Horizontal blanking
    // mode 1 Vertical blanking
    // mode 2 Searching OAM for OBJS whos (X, Y) coordinates overlap this line
    // mode 3 Reading OAM and VRAM to draw the picture
    if (ppu.mode == PPU_MODE_OAM_SCAN) {
        // printf("PPU OAM_SCAN\n");
        if (ppu.ticks >= 40) {
            ppu.ticks = 0;
            ppu.mode = PPU_MODE_DRAWING;
        }
    }
    else if (ppu.mode == PPU_MODE_DRAWING) {

        ppu.scrollX++;
        // printf("PPU_MODE_DRAWING\n");
        if (ppu.ticks >= 160) {
            ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
            ppu.ticks = 0;
            clockBGPixelFetch();
            // TODO Draw the image
        }
    }
    else if (ppu.mode == PPU_MODE_HORIZONTAL_BLANKING) {
        // A full scanline takes 456 ticks to complete. At the end of a
        // scanline, the PPU goes back to the initial OAM Search state.
        // When we reach line 144, we switch to VBlank state instead.
        // HBlank happens when all 160 pixels in a scanline have been output to the screen
        // printf("PPU HORIZONTAL BLANKING\n");
        if (ppu.ticks >= 456) {
            // printf("INCREASING SCANLINE\n");
            ppu.scanline++;
            ppu.ticks = 0;
            if (ppu.scanline == 144) {
                // enter vblank
                ppu.mode = PPU_MODE_VERTICAL_BLANKING;
            }
            else {
                ppu.mode = PPU_MODE_OAM_SCAN;
            }
        }
    }
    else if (ppu.mode == PPU_MODE_VERTICAL_BLANKING) {
        // VBlank happens when all 144 scanlines in a frame have been output to the screen
        // printf("PPU VERTICAL BLANKING");
        REQUEST_INTERRUPT(VBLANK_BIT);
        if (ppu.ticks >= 456) {
            ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
            ppu.scanline++;
            if (ppu.scanline >= 153) {
                // restart scanning modes
                ppu.mode = PPU_MODE_OAM_SCAN;
                ppu.scanline = 0;
                pixelFetcher.WLY = 0;
            }
        }
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



uint16_t getBGTileMapArea() {
    return LCDC_GET_BG_TILEMAP_AREA() == 1? 0x9C00 : 0x9800;
}

uint16_t getWindowTileMapArea() {
    return LCDC_GET_WINDOW_TILEMAP_AREA() == 1? 0x9C00 : 0x9800;
}


// Functions for the pixel fetcher and pixel fifo 


uint8_t getBGTileId() {
    uint16_t area = 0;
    uint16_t xOffset = 0;
    uint16_t yOffset = 0;
    if (LCDC_GET_WINDOW_ENABLE()) {
        area = getWindowTileMapArea();
        xOffset = (uint16_t)pixelFetcher.x;
        yOffset = (uint16_t)32*((uint16_t)pixelFetcher.WLY / (uint16_t)8);
    }
    else {
        area = getBGTileMapArea();
        xOffset = (((uint16_t)ppu.scrollX / (uint16_t)8) + (uint16_t)pixelFetcher.x) & 0x1F;
        yOffset = (uint16_t)32*(((uint16_t)ppu.scanline + (uint16_t)ppu.scrollY) & 0x00FF) / (uint16_t)8;
    }

    uint16_t tileIdAddress = area + (xOffset + yOffset) & 0x03FF;

    return ppu.video_ram[tileIdAddress];
}

uint8_t getBGTileDataLo(uint8_t tileId) {
    uint16_t offset = 0;
    if (LCDC_GET_WINDOW_ENABLE()) {
        offset = pixelFetcher.WLY % 8;
    }
    else {
        offset = 2*(((uint16_t)ppu.scanline + (uint16_t)ppu.scrollY) % 8);
    }

    uint8_t loByte = 0;
    if (LCDC_GET_BGWINDOW_TILEDATA_AREA()) {
        loByte = ppu.video_ram[offset + (uint16_t)tileId];
    }
    else {
        loByte = ppu.video_ram[offset + (int16_t)tileId];
    }
    return loByte;
}

uint8_t getBGTileDataHi(uint8_t tileId) {
    uint16_t offset = 0;
    if (LCDC_GET_WINDOW_ENABLE()) {
        offset = pixelFetcher.WLY % 8;
    }
    else {
        offset = 2*(((uint16_t)ppu.scanline + (uint16_t)ppu.scrollY) % 8);
    }

    uint8_t hiByte = 0;
    if (LCDC_GET_BGWINDOW_TILEDATA_AREA()) {
        hiByte = ppu.video_ram[offset + (uint16_t)tileId] + 1;
    }
    else {
        hiByte = ppu.video_ram[offset + (int16_t)tileId + 1];
    }
    return hiByte;
}

void clockBGPixelFetch() {
    // every mode takes two ticks
    if (++pixelFetcher.ticks % 2 != 0)
        return;
    
    switch (pixelFetcher.mode) {
        case FETCH_TILE_NO :  {
            pixelFetcher.tileId = getBGTileId();
            // printf("Tile ID: %X\n", pixelFetcher.tileId);
            pixelFetcher.mode = FETCH_TILE_DATA_LO;
            break;
        }
        case FETCH_TILE_DATA_LO : {
            pixelFetcher.loByte = getBGTileDataLo(pixelFetcher.tileId);
            pixelFetcher.mode = FETCH_TILE_DATA_HI;
            break;
        }
        case FETCH_TILE_DATA_HI : {
            pixelFetcher.hiByte = getBGTileDataHi(pixelFetcher.tileId);
            pixelFetcher.mode = PUSH_PIXELS;
            break;
        }
        case PUSH_PIXELS : {
            // TODO
            // printf("pixelFetcher loByte: %X, hiByte: %X\n", pixelFetcher.loByte, pixelFetcher.hiByte);
            pixelFetcher.mode = FETCH_TILE_NO;
            pixelFetcher.x++;
            break;
        }
    }
}


// debugging functions

void displayVram() {
    for (unsigned int i = 0; i < 10; i++) {
        printf("vram[%d] = %X\n", i, ppu.video_ram[i]);
    }
}