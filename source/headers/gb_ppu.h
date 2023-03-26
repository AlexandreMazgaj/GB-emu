#pragma once

#include "constants.h"
#include <stdint.h>

// 2BPP processing macros
#define GET_PIXEL_COLOR(hiByte, loByte, pixel)                                 \
  ((uint8_t)(((hiByte) & (1 << pixel)) >> (pixel - 1) |                        \
             ((loByte & (1 << pixel)) >> (pixel))))

// 0xFF40
#define LCDC_GET_LCDPPU_ENABLE() ((ppu.reg_lcdc & (1 << 7)) >> 7)
#define LCDC_GET_WINDOW_TILEMAP_AREA()                                         \
  ((ppu.reg_lcdc & (1 << 6)) >>                                                \
   6) // select which area in the memory to fetch window map form
#define LCDC_GET_WINDOW_ENABLE() ((ppu.reg_lcdc & (1 << 5)) >> 5)
#define LCDC_GET_BGWINDOW_TILEDATA_AREA()                                      \
  ((ppu.reg_lcdc & (1 << 4)) >> 4) // select the addressing mode
#define LCDC_GET_BG_TILEMAP_AREA()                                             \
  ((ppu.reg_lcdc & (1 << 3)) >>                                                \
   3) // select which area in the memory to fetch bg map from
#define LCDC_GET_OBJ_SIZE() ((ppu.reg_lcdc & (1 << 2)) >> 2)
#define LCDC_GET_OBJ_ENABLE() ((ppu.reg_lcdc & (1 << 1)) >> 1)
#define LCDC_GET_BGWINDOW_PRIORITY() (ppu.reg_lcdc & 1)

// 0xFF41
// #define STAT_GET

// Pixel Fetcher mode
enum PixelFetcherMode {
  FETCH_TILE_NO,
  FETCH_TILE_DATA_LO,
  FETCH_TILE_DATA_HI,
  PUSH_PIXELS
};

// PPU Modes
enum PPUMode {
  PPU_MODE_HORIZONTAL_BLANKING = 0,
  PPU_MODE_VERTICAL_BLANKING = 1,
  PPU_MODE_OAM_SCAN = 2,
  PPU_MODE_DRAWING = 3
};

struct ppu {

  uint8_t screen[SCREEN_HEIGHT * SCREEN_WIDTH];

  uint8_t oam[OAM_SIZE];
  uint8_t video_ram[VIDEO_RAM_SIZE];

  uint8_t reg_lcdc;
  uint8_t reg_stat;

  uint8_t scrollX; // specify the top left coordinates of the visible parts of
                   // the bg map
  uint8_t scrollY;

  // scan line compare
  uint8_t LYC; // should be compared to LY and LY and the flag in stat should be
               // set if LYC == LY LY is scanline

  uint8_t WY; // specify the top left coordinates of the window
  uint8_t WX;

  // to manage the cycle
  enum PPUMode mode;
  int ticks;
  uint8_t scanline;

  // Color palettes

  uint8_t bg_pal[3];
  uint8_t ob_pal0[3];
  uint8_t ob_pal1[3];

  uint8_t bg_palValue;
  uint8_t ob_pal0Value;
  uint8_t ob_pal1Value;

  uint16_t bgPixelFifo;
  uint16_t spritePixelFifo;

  uint8_t canDraw;

} extern ppu;

struct pixelFetcher {
  uint8_t x;
  uint8_t y;

  uint8_t
      WLY; // internal scanline counter for the window, incremented everytime a
           // scanline has window elements and reset every V-BLANK

  enum PixelFetcherMode mode;

  unsigned int ticks;

  // save values for the execution of the clock cycles
  uint8_t tileId;
  uint8_t loByte;
  uint8_t hiByte;

} extern pixelFetcher;

void PPU_init();

void PPU_clock();

void writePPU(uint16_t addr, uint8_t val);

uint8_t readPPU(uint16_t addr);

uint8_t getGBColorFromValue(uint8_t val);

uint16_t getWindowTileMapArea();

uint16_t getBGTileMapArea();

uint8_t getBGTileId(uint8_t x);

uint16_t getBGTileData(uint8_t tileId);

uint32_t getColor(uint8_t bit);

void renderBackgroundScanline();

// debugging functions
void displayVram();