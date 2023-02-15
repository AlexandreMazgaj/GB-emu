#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/gb_ppu.h"
#include "headers/opcodes.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void drawScreen(SDL_Surface *surface) {
  SDL_LockSurface(surface);
  uint32_t *pixels = (uint32_t *)surface->pixels;
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      // pixels[i*SCREEN_WIDTH + j] = ppu.screen[i*SCREEN_WIDTH + j] == 0 ? 0 :
      // 0xFFFFFFFF;
      pixels[i * SCREEN_WIDTH + j] = 0xFFFFFFFF;
    }
  }
  SDL_UnlockSurface(surface);
}

uint32_t getColor(uint8_t bit) {
  if (bit == 0x3)
    return 0;
  if (bit == 0x2)
    return 0x2f3536;
  if (bit == 0x1)
    return 0xbebebe;

  return 0xffffff;
  ;
}

void drawFirstTile(SDL_Surface *surface) {
  SDL_LockSurface(surface);

  //   SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  int pix = 0;
  for (uint16_t i = 0x300; i < 0x310; i += 2) {
    uint8_t loByte = ppu.video_ram[i];
    uint8_t hiByte = ppu.video_ram[i + 1];

    for (int j = 0; j < 8; j++) {

      uint8_t bit;
      if (j == 0) {
        bit = (uint8_t)(((hiByte & 0x1) << 1) | (loByte & 0x1));
      } else {
        bit = (uint8_t)(((hiByte & (0x1 << j)) >> (j - 1)) |
                        ((loByte & (0x1 << j)) >> j));
      }

      //   if (loByte != 0 || hiByte != 0) {
      //     printf("bit : %X\n", bit);
      //   }

      pixels[pix * SCREEN_WIDTH + j] = getColor(bit);
    }
    pix++;
  }

  SDL_UnlockSurface(surface);
}

int main() {

  CPU_init();
  MMU_init();
  PPU_init();

  // uint8_t error =
  // loadCartridge("/home/alex/workspace/gameboy_emu/GB-emu/roms/01-special.gb");

  uint8_t error = loadCartridge(
      "/home/alex/workspace/gameboy_emu/GB-emu/roms/03-op-sp,hl.gb");

  // uint8_t error =
  // loadCartridge("/home/alex/workspace/gameboy_emu/GB-emu/roms/11-op-a,(hl).gb");

  if (error)
    return 9;

  SDL_Surface *gameboyGraphics = NULL;
  SDL_Surface *scaledGraphics = NULL;

  // The window we'll be rendering to
  SDL_Window *window = NULL;

  // The surface contained by the window
  SDL_Surface *screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow("GAME BOY", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 2,
                            SCREEN_HEIGHT * 2, SDL_WINDOW_SHOWN);
  SDL_SetWindowResizable(window, SDL_TRUE);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           SCREEN_WIDTH, SCREEN_HEIGHT);

  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);

  gameboyGraphics =
      SDL_CreateRGBSurface(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 32, 0, 0, 0, 0);
  scaledGraphics =
      SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

  SDL_RenderPresent(renderer);

  // //Update the surface
  // SDL_UpdateWindowSurface( window );

  SDL_Delay(100);
  unsigned int t1;
  unsigned int t2;
  unsigned int elapsed;
  int remaining;
  unsigned int interval = 1000 / TICKS;

  Uint8 *keys = SDL_GetKeyboardState(NULL);

  uint8_t emuRun = 0;
  uint8_t oneByOne = 0;

  SDL_Event e;

  printf("Everything is ready, lauching emulator\n");

  // printf("rom[0x7ff3] = %X\n", mmu.rom[0x7ff3]);

  // FILE *file = fopen("output_rom.txt", "w");

  // for (int i = 0; i < 1000; i++) {
  //     fprintf(file, "rom[%X] = %X\n", i, mmu.rom[i]);
  // }

  // fclose(file);

  while (1) {

    t1 = SDL_GetTicks();

    if (emuRun) {
      if (CPU_clock() == 220) {
        // emuRun = 0;
      }

      PPU_clock();
    } else {
      if (oneByOne) {
        while (!CPU_clock())
          ;
        // PPU_clock();
        oneByOne = 0;
      }
    }

    if ((SDL_PollEvent(&e)) != 0) {
      if (e.type == SDL_QUIT) {
        break;
      }
      // Start or pause the emulation
      if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_SPACE]) {
        emuRun ^= 1;
      }

      if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_B]) {
        break;
      }

      if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_Y]) {
        oneByOne = 1;
      }

      if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_P]) {
        printRegisters();
      }
    }

    if (emuRun && ppu.video_ram[0x300] != 0) {
      //   drawScreen(gameboyGraphics);
      drawFirstTile(gameboyGraphics);
      //   SDL_BlitScaled(gameboyGraphics, NULL, scaledGraphics, NULL);
      SDL_UpdateTexture(texture, NULL, gameboyGraphics->pixels,
                        SCREEN_WIDTH * 4);
      //   SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
      // Update the surface
      //   if (SDL_UpdateWindowSurface(window) < 0) {
      //     printf("ERROR WITH THE WINDOW\n");
      //   }
    }

    t2 = SDL_GetTicks();
    elapsed = t2 - t1;
    remaining = interval - elapsed;
    if (remaining > 0) {
      // SDL_Delay(remaining/2);
      elapsed = interval;
    }
  }

  SDL_DestroyWindow(window);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}