#include "headers/gb_mmu.h"
#include <stdio.h>
#include <stdlib.h>
#include "headers/gb_cpu.h"
#include "headers/gb_ppu.h"

struct mmu mmu;



MMU_init() {
    for (int i = 0; i < ROM_BANK_SIZE; i++) {
        mmu.rom[i] = 0;
    }

    for (int i = 0; i < RAM_SIZE; i++) {
        mmu.video_ram[i] = 0;
        mmu.external_ram[i] = 0;
    }

    for (int i = 0; i < HIGH_RAM_SIZE; i++) {
        mmu.high_ram[i] = 0;
    }
}

void loadRom(char* path) {
    FILE *romPtr;

    romPtr = fopen(path, "rb"); // b is for binary

    if (romPtr == NULL)
        printf("Could not open the file\n");

    fseek(romPtr, 0, SEEK_END);

    size_t size = ftell(romPtr);

    fseek(romPtr, 0L, SEEK_SET);

    for (unsigned int i = 0; i < size; ++i) {
        uint8_t c = fgetc(romPtr);
        mmu.rom[i] = c;
    }

    fclose(romPtr);
}



// TODO Finish readByte function
uint8_t readByte(uint16_t addr) {
    if (addr >= 0x0000 &&  addr <= 0x3fff) {
        return mmu.rom[addr];
    }
    else if (addr >= 0x4000 && addr <= 0x7fff) {
        return mmu.rom[addr - 0x4000];
    }
    else if (addr >= 0x8000 && addr <= 0x9fff) {
        return mmu.video_ram[addr - 0x8000];
    }
    else if (addr >= 0xa000 && addr <= 0xbfff) {
        return mmu.external_ram[addr - 0xa000];
    }
    else if (addr >= 0xc000 && addr <= 0xdfff) {
        return mmu.work_ram[addr - 0xc000];
    }
    else if (addr >= 0xfe00 && addr <= 0xfe9f) {
        return ppu.oam[addr - 0xfe00];
    }
    else if (addr >= 0xff80 && addr <= 0xfffe) {
        return mmu.high_ram[addr - 0xff80];
    }
    else if (addr == 0xff0f) {
        return IF;
    }
    else if (addr == 0xffff) {
        return IE;
    }
}

uint16_t readWord(uint16_t addr) {
    return ((uint16_t)readByte(addr) | (uint16_t)(readByte(addr+1) << 8));
}


// TODO finish writeByte function
void writeByte(uint16_t addr, uint8_t val) {
    if (addr >= 0x0000 &&  addr <= 0x3fff) {
        mmu.rom[addr] = val;
    }
    else if (addr >= 0x4000 && addr <= 0x7fff) {
        mmu.rom[addr - 0x4000] = val;
    }
    else if (addr >= 0x8000 && addr <= 0x9fff) {
        mmu.video_ram[addr - 0x8000] = val;
    }
    else if (addr >= 0xa000 && addr <= 0xbfff) {
        mmu.external_ram[addr - 0xa000] = val;
    }
    else if (addr >= 0xc000 && addr <= 0xdfff) {
        mmu.work_ram[addr - 0xc000] = val;
    }
    else if (addr >= 0xfe00 && addr <= 0xfe9f) {
        ppu.oam[addr - 0xfe00] = val;
    }
    else if (addr >= 0xff80 && addr <= 0xfffe) {
        mmu.high_ram[addr - 0xff80] = val;
    }
    else if (addr == 0xff0f) {
        IF = val;
    }
    else if (addr == 0xffff) {
        IE = val;
    }
}


void writeWord(uint16_t addr, uint16_t val) {
    uint8_t hi = ((uint8_t)(val >> 8));
    uint8_t lo = ((uint8_t)val);

    writeByte(addr, lo);
    writeByte(addr+1, hi);

}


uint16_t popWordStack() {
    uint16_t val = readWord(registers.sp);
    registers.sp +=2;
    return val;
}


void pushWordStack(uint16_t val) {
    registers.sp -=2;
    writeWord(registers.sp, val);
}