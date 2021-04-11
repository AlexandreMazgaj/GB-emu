#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"


int main() {

    CPU_init();

    // loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/tetris.gb");

    registers.af = 0;
    registers.bc = 0;

    registers.b = 0xff;

    printRegFlags();

    printf("register b: %X\n", registers.b);

    inc8bReg(&registers.b);

    printf("register b: %X\n", registers.b);

    printRegFlags();

    

    return 0;
}