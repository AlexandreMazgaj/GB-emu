#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
// #include "headers/opcodes.h"


int main() {

    CPU_init();
    MMU_init();

    loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/ducktales.gb");

    printf("nb rom banks: %d\n", mmu.mbc_nbRomBank);




    return 0;
}