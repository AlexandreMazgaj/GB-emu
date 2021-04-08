#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"


int main() {

    CPU_init();

    loadRom("/Users/mazgajalexandre/workspace/gameboy_emu/roms/tetris.gb");

    IME = 1;

    // writing IE, enabling timer interrupt
    writeByte(0xffff, 0x06);
    // IF
    writeByte(0xff0f, 0x06);

    checkInterrupts();

    uint8_t ie = readByte(0xffff);
    uint8_t iF = readByte(0xff0f);


    printf("ie = %X\n", ie);
    printf("iF = %X\n", iF);

    

    return 0;
}