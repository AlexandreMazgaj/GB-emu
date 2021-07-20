#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"


int main() {

    CPU_init();
    MMU_init();

    loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/ducktales.gb");

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