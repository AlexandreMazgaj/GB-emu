#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
// #include "headers/opcodes.h"


int main() {

    CPU_init();
    MMU_init();

    loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/tetris.gb");


    for (int i = 0; i < 100; ++i)
        clock();



    return 0;
}