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
      // printf("Color: %X\n", ppu.screen[i * SCREEN_WIDTH + j]);
      pixels[i * SCREEN_WIDTH + j] = getColor(ppu.screen[i * SCREEN_WIDTH + j]);
    }
  }
  SDL_UnlockSurface(surface);
}

void drawFirstTile(SDL_Surface *surface) {
  SDL_LockSurface(surface);

  Uint32 *pixels = (Uint32 *)surface->pixels;

  uint32_t t = 0;
  uint32_t line = 0;

  for (uint16_t tile = 0; tile < VIDEO_RAM_SIZE - 0x10; tile += 0x10) {

    int tileLine = 0;

    for (uint16_t i = tile; i < (tile + 0x10); i += 2) {

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

        pixels[(8 - j) + t * 8 + tileLine * SCREEN_WIDTH +
               line * (SCREEN_WIDTH * 8)] = getColor(bit);
      }
      tileLine++;
    }
    if (t >= 15) {
      t = 0;
      line++;
      if (line >= 20)
        break;
    } else {
      t++;
    }
  }

  SDL_UnlockSurface(surface);
}

int main() {

  CPU_init();
  MMU_init();
  PPU_init();

  uint8_t error =
      loadCartridge("/home/alex/workspace/gameboy_emu/GB-emu/roms/Tetris.gb");

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
  Uint32 *pixels = (Uint32 *)(scaledGraphics->pixels);

  while (1) {

    // t1 = SDL_GetTicks();

    if (emuRun) {
      if (CPU_clock() == 220) {
        emuRun = 0;
        // break;
      }

      PPU_clock();
    } else {
      // if (oneByOne) {
      //   while (!CPU_clock())
      //     ;
      //   PPU_clock();
      //   oneByOne = 0;
      // }
    }

    if ((SDL_PollEvent(&e)) != 0) {
      if (e.type == SDL_QUIT) {
        break;
      }
      // key down
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_SPACE:
          // Start or pause the emulation
          emuRun ^= 1;
          break;
        case SDLK_y:
          oneByOne = 1;
          break;
        case SDLK_p:
          printRegisters(1);
          break;
        case SDLK_RIGHT:
          mmu.inputs[RIGHT_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_q:
          mmu.inputs[A_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_LEFT:
          mmu.inputs[LEFT_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_w:
          mmu.inputs[B_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_UP:
          mmu.inputs[UP_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_s:

          mmu.inputs[SELECT_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_DOWN:

          mmu.inputs[DOWN_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        case SDLK_a:

          mmu.inputs[START_BUTTON] = 0;
          REQUEST_INTERRUPT(JOYPAD_BIT);
          break;
        }
      }
      // key up
      else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
          mmu.inputs[RIGHT_BUTTON] = 1;
          break;
        case SDLK_q:
          mmu.inputs[A_BUTTON] = 1;
          break;
        case SDLK_LEFT:
          mmu.inputs[LEFT_BUTTON] = 1;
          break;
        case SDLK_w:
          mmu.inputs[B_BUTTON] = 1;
          break;
        case SDLK_UP:
          mmu.inputs[UP_BUTTON] = 1;
          break;
        case SDLK_s:
          mmu.inputs[SELECT_BUTTON] = 1;
          break;
        case SDLK_DOWN:
          mmu.inputs[DOWN_BUTTON] = 1;
          break;
        case SDLK_a:
          mmu.inputs[START_BUTTON] = 1;
          break;
        }
      }
    }

    if (emuRun && ppu.canDraw) {
      //   SDL_BlitScaled(gameboyGraphics, NULL, scaledGraphics, NULL);

      SDL_RenderClear(renderer);
      // renderTileChatGPT(renderer);

      // drawFirstTile(scaledGraphics);
      drawScreen(scaledGraphics);

      SDL_UpdateTexture(texture, NULL, scaledGraphics->pixels,
                        SCREEN_WIDTH * 4);

      SDL_RenderCopy(renderer, texture, NULL, NULL);

      SDL_RenderPresent(renderer);
      // Update the surface
      //   if (SDL_UpdateWindowSurface(window) < 0) {
      //     printf("ERROR WITH THE WINDOW\n");
      //   }
      ppu.canDraw = 0;
    }

    // t2 = SDL_GetTicks();
    // elapsed = t2 - t1;
    // remaining = interval - elapsed;
    // if (remaining > 0) {
    //   // SDL_Delay(remaining/2);
    //   elapsed = interval;
    // }
  }

  SDL_DestroyWindow(window);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}