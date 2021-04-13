#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"


int main() {

    CPU_init();

    // loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/tetris.gb");
    registers.f = 0;

    registers.a = 0x7f;


    printf("before: %X\n", registers.a);

    printRegFlags();

    exe_rrca();

    printRegFlags();

    printf("after: %X\n", registers.a);

    return 0;
}