#include "headers/gb_ppu.h"
#include "headers/gb_cpu.h"
#include <stdio.h>
#include <stdlib.h>

struct ppu ppu;
struct pixelFetcher pixelFetcher;

void PPU_init() {
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      ppu.screen[i * SCREEN_WIDTH + j] = 0;
    }
  }

  // for (int i = 0; i < 40; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     ppu.spritesToRender[i][j] = 0;
  //   }
  // }
  // ppu.numberOfSpritesToRender = 0;

  for (int i = 0; i < 4; i++)
    ppu.bg_pal[i] = getColor(i);

  ppu.mode = PPU_MODE_OAM_SCAN;
  ppu.ticks = 0;
  ppu.scrollX = 0;
  ppu.scrollY = 0;
  ppu.scanline = 0;

  ppu.canDraw = 0;

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
  ppu.ticks += cycle;
  if (halted)
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
    if (ppu.ticks >= 80) {
      ppu.ticks = 0;
      ppu.mode = PPU_MODE_DRAWING;
    }
  } else if (ppu.mode == PPU_MODE_DRAWING) {
    // printf("PPU_MODE_DRAWING\n");
    if (ppu.ticks >= 172) {
      ppu.mode = PPU_MODE_HORIZONTAL_BLANKING;
      ppu.ticks = 0;
      renderBackgroundScanline();

      uint8_t spritesToRender[40][4];
      uint8_t numberOfSpritesToRender = getSpritesToRender(spritesToRender);
      renderSprites(spritesToRender, numberOfSpritesToRender);

      // renderSpriteScanline();
    }
  } else if (ppu.mode == PPU_MODE_HORIZONTAL_BLANKING) {
    // A full scanline takes 456 ticks to complete. At the end of a
    // scanline, the PPU goes back to the initial OAM Search state.
    // When we reach line 144, we switch to VBlank state instead.
    // HBlank happens when all 160 pixels in a scanline have been output to the
    // screen
    // printf("PPU HORIZONTAL BLANKING\n");
    if (ppu.ticks >= 204) {
      ppu.scanline++;
      ppu.ticks = 0;
      if (ppu.scanline == 144) {
        // enter vblank
        ppu.mode = PPU_MODE_VERTICAL_BLANKING;
      } else {
        ppu.mode = PPU_MODE_OAM_SCAN;
      }
    }
  } else if (ppu.mode == PPU_MODE_VERTICAL_BLANKING) {
    // VBlank happens when all 144 scanlines in a frame have been output to the
    // screen
    // printf("PPU VERTICAL BLANKING");
    REQUEST_INTERRUPT(VBLANK_BIT);

    if (ppu.ticks >= 456) {
      ppu.ticks = 0;
      ppu.scanline++;
      if (ppu.scanline >= 153) {
        // restart scanning modes
        ppu.canDraw = 1;

        ppu.mode = PPU_MODE_OAM_SCAN;
        ppu.scanline = 0;
        pixelFetcher.WLY = 0;
      }
    }
  }
}

void writePPU(uint16_t addr, uint8_t val) {
  if (addr == 0xff40) {
    ppu.reg_lcdc = val;
    return;
  }
  if (addr == 0xff41) {
    ppu.reg_stat = val;
    return;
  }
  if (addr == 0xff42) {
    ppu.scrollY = val;
    return;
  }
  if (addr == 0xff43) {
    ppu.scrollX = val;
    return;
  }
  // if (addr == 0xff44) { ppu.scanline = val; return; } read only
  if (addr == 0xff45) {
    ppu.LYC = val;
    return;
  }
  // 0xff46 is the oam dma transfer, this is taken care of in the mmu
  if (addr == 0xff47) {
    ppu.bg_palValue = val;
    for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
      ppu.bg_pal[colorIndex] =
          getColor((uint8_t)(ppu.bg_palValue >> (2 * colorIndex)) & 0x03);
    }
  }
  if (addr == 0xff48) {
    ppu.ob_pal0Value = val;
    for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
      ppu.ob_pal0[colorIndex] = getColor((val >> (2 * colorIndex)) & 0x03);
    }
  }
  if (addr == 0xff49) {
    ppu.ob_pal1Value = val;
    for (int colorIndex = 0; colorIndex < 4; colorIndex++) {
      ppu.ob_pal1[colorIndex] = getColor((val >> (2 * colorIndex)) & 0x03);
    }
  }
  if (addr == 0xff4a) {
    ppu.WY = val;
    return;
  }
  if (addr == 0xff4b) {
    ppu.WX = val;
    return;
  }
}

uint8_t readPPU(uint16_t addr) {
  if (addr == 0xff40) {
    return ppu.reg_lcdc;
  }
  if (addr == 0xff41) {
    return ppu.reg_stat;
  }
  if (addr == 0xff42) {
    return ppu.scrollY;
  }
  if (addr == 0xff43) {
    return ppu.scrollX;
  }
  if (addr == 0xff44) {
    // return 0x90;
    return ppu.scanline;
  }
  if (addr == 0xff45) {
    return ppu.LYC;
  }
  if (addr == 0xff47) {
    return ppu.bg_palValue;
  }
  if (addr == 0xff48) {
    return ppu.ob_pal0Value;
  }
  if (addr == 0xff49) {
    return ppu.ob_pal1Value;
  }
  if (addr == 0xff4a) {
    return ppu.WY;
  }
  if (addr == 0xff4b) {
    return ppu.WX;
  }

  return 0;
}

uint16_t getBGTileMapArea() {
  return LCDC_GET_BG_TILEMAP_AREA() == 1 ? 0x9C00 : 0x9800;
}

uint16_t getWindowTileMapArea() {
  return LCDC_GET_WINDOW_TILEMAP_AREA() == 1 ? 0x9C00 : 0x9800;
}

// Functions to render the background and window

uint8_t getBGTileId(uint8_t x) {
  uint16_t area = 0;
  uint16_t xOffset = 0;
  uint16_t yOffset = 0;
  if (LCDC_GET_WINDOW_ENABLE()) {
    xOffset = (uint16_t)x;
    yOffset = (uint16_t)32 * ((uint16_t)pixelFetcher.WLY / (uint16_t)8);
  } else {
    area = getBGTileMapArea();
    xOffset = ((((uint16_t)ppu.scrollX + (uint16_t)x) / (uint16_t)8)) & 0x1F;
    yOffset = (uint16_t)32 *
              ((((uint16_t)ppu.scanline + (uint16_t)ppu.scrollY) & 0x00FF) /
               (uint16_t)8);
  }

  uint16_t tileIdAddress = area + ((xOffset + yOffset) & 0x03FF);

  return readByte(tileIdAddress);
}

uint16_t getBGTileData(uint8_t tileId) {
  uint16_t offset = 0;
  if (LCDC_GET_WINDOW_ENABLE()) {
    offset = pixelFetcher.WLY % 8;
  } else {
    // for a tile, 2 bytes make one line (see 2bpp format), that is why we
    // multiply by 2 the modulo
    offset = 2 * (((uint16_t)ppu.scanline + (uint16_t)ppu.scrollY) % 8);
  }

  uint8_t loByte = 0;
  uint8_t hiByte = 0;
  if (LCDC_GET_BGWINDOW_TILEDATA_AREA()) {
    loByte = ppu.video_ram[offset + (uint16_t)tileId * 16];
    hiByte = ppu.video_ram[offset + (uint16_t)tileId * 16 + 1];
  } else {
    loByte = ppu.video_ram[(int16_t)0x1000 + (uint16_t)offset +
                           ((int8_t)tileId) * 16];
    hiByte = ppu.video_ram[0x1000 + offset + ((int8_t)tileId) * 16 + 1];
  }
  return (uint16_t)hiByte << 8 | (uint16_t)loByte;
}

uint32_t getColor(uint8_t bit) {

  if (bit == 0x3)
    return 0;
  if (bit == 0x2)
    return 0xff555555;
  if (bit == 0x1)
    return 0xffaaaaaa;

  return 0xffffff;
}

void renderBackgroundScanline() {

  for (int x = 0; x < SCREEN_WIDTH; x++) {

    uint8_t tileId = getBGTileId(x);

    uint16_t tileData = getBGTileData(tileId);
    uint8_t loByte = (uint8_t)((0x00ff) & tileData);
    uint8_t hiByte = (uint8_t)(((0xff00) & tileData) >> 8);

    uint8_t j = 7 - (x % 8);

    uint8_t bit = (((hiByte >> j) & 0x1) << 1) | ((loByte >> j) & 0x1);

    ppu.screen[SCREEN_WIDTH * ppu.scanline + x] = bit;
  }
}

// functions to render the sprites

/*
 * sprites -> tileId
           -> x_position
           -> y_position
           -> spriteAttributes
*/
uint8_t getSpritesToRender(uint8_t sprites[10][4]) {
  uint8_t sprite_index = 0;
  for (unsigned int i = 0; i < OAM_SIZE; i += 4) {
    uint8_t y_position = ppu.oam[i] - 16;
    // we remove 8 to take into account the fact that 0 hides the sprite,
    // and 8 displays it in it's entirety
    uint8_t x_position = ppu.oam[i + 1] - 8;
    uint8_t tileId = ppu.oam[i + 2];
    uint8_t spriteAttributes = ppu.oam[i + 3];

    // if (0x80 > tileId || tileId > 0x8f) {
    //   continue;
    // }

    if ((ppu.scanline < y_position) ||
        ppu.scanline >= (y_position + LCDC_GET_OBJ_SIZE())) {
      continue;
    }

    if (ppu.oam[i + 1] > 8) {
      sprites[sprite_index][0] = tileId;
      sprites[sprite_index][1] = x_position;
      sprites[sprite_index][2] = y_position;
      sprites[sprite_index][3] = spriteAttributes;

      sprite_index++;
      if (sprite_index == 10)
        return sprite_index;
    }
  }
  if (sprite_index > 0) {
    return sprite_index;
  }
  return 0;
}

uint16_t getSpriteTileData(uint8_t tileId, uint8_t spriteAttributes,
                           uint8_t line, uint8_t y_position) {
  uint16_t offset = 0;

  if (IS_FLIP_Y(spriteAttributes)) {
    offset = (uint16_t)(16 - 2 * ((int16_t)(line - y_position) % 8));
  } else {
    offset = 2 * ((uint16_t)(line - y_position) % 8);
  }

  uint8_t loByte = ppu.video_ram[offset + (uint16_t)tileId * 16];
  uint8_t hiByte = ppu.video_ram[offset + (uint16_t)tileId * 16 + 1];

  return (uint16_t)hiByte << 8 | (uint16_t)loByte;
}

void renderSprites(uint8_t sprites_to_render[10][4],
                   uint8_t numberOfSpritesToRender) {
  if (!LCDC_GET_OBJ_ENABLE())
    return;

  if (numberOfSpritesToRender == 0) {
    return;
  } // we did not find any sprites in the oam

  for (int i = 0; i < numberOfSpritesToRender; i++) {
    uint8_t spriteTileId = sprites_to_render[i][0];
    uint8_t x_position = sprites_to_render[i][1];
    uint8_t y_position = sprites_to_render[i][2];
    uint8_t spriteAttributes = sprites_to_render[i][3];

    if (IS_BG_OVER_SPRITE(spriteAttributes) &&
        ppu.screen[ppu.scanline * SCREEN_WIDTH + x_position] != 0) {
      continue;
    }

    if (ppu.scanline > SCREEN_HEIGHT) {
      break;
    }

    uint16_t tileData = getSpriteTileData(spriteTileId, spriteAttributes,
                                          ppu.scanline, y_position);
    uint8_t loByte = (uint8_t)((0x00ff) & tileData);
    uint8_t hiByte = (uint8_t)(((0xff00) & tileData) >> 8);

    for (int x_pixel = 0; x_pixel < 8; x_pixel++) {
      if (x_pixel + x_position > SCREEN_WIDTH) {
        break;
      }

      uint8_t j;
      if (IS_FLIP_X(spriteAttributes)) {
        j = (x_pixel % 8);
      } else {
        j = 7 - (x_pixel % 8);
      }

      uint8_t bit = (((hiByte >> j) & 0x1) << 1) | ((loByte >> j) & 0x1);

      ppu.screen[SCREEN_WIDTH * ppu.scanline + x_position + x_pixel] = bit;
    }
  }
}

// debugging functions

void displayVram() {
  for (unsigned int i = 0x9800; i < 0xA000; i++) {
    printf("vram[%d] = %X\n", i, ppu.video_ram[i]);
  }
}