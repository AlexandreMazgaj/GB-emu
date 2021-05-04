#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
// #include "headers/opcodes.h"


int main() {

    CPU_init();
    MMU_init();

    // loadCartridge("/Users/mazgajalexandre/workspace/gameboy_emu/roms/ducktales.gb");


    for (uint16_t i = 0xc000; i < 0xc09f + 1; i++) {
        writeByte(i, 0x4d);
    }

    printf("----------------------\n");

    for (uint16_t i = 0xfe00; i < 0xfe9f + 1; i++) {
        printf("oam %X -> %X\n", i, readByte(i));
    }

    printf("----------------------\n");


    printf("starting oam dma\n");
    writeByte(0xff46, 0xc0);


    printf("----------------------\n");

    for (uint16_t i = 0xfe00; i < 0xfe9f + 1; i++) {
        printf("oam %X -> %X\n", i, readByte(i));
    }

    printf("----------------------\n");




    return 0;
}