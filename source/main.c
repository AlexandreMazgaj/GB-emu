#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"
#include "headers/gb_ppu.h"
#include <SDL2/SDL.h>



void drawScreen(SDL_Surface *surface)
{
    SDL_LockSurface(surface);
    uint32_t *pixels = (uint32_t *)surface->pixels;
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            pixels[i*SCREEN_WIDTH + j] = ppu.screen[i][j] == 0 ? 0 : 0xFFFFFFFF;
        }
    }
    SDL_UnlockSurface(surface);
}




int main() {

    CPU_init();
    MMU_init();

    loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/tetris.gb");

    for (int i = 0; i < 100; i++) {
        clock();
    }

    // SETCFLAG(1);
    // SETHFLAG(0);
    // SETNFLAG(0);
    // SETZFLAG(0);

    // registers.pc = 0;

    // registers.sp = 0xff;

    // registers.e = 0;

    // registers.a = 0xff;

    // registers.b = 0x0;

    // // mmu.rom[1] = 0xdd;

    // exe_adcab();


    // printf("%X\n", registers.a);

    // printRegFlags();

    // printf("%X\n", registers.hl);





    return 0;
}