#include "headers/gb_mmu.h"
#include <stdio.h>
#include <stdlib.h>
#include "headers/gb_cpu.h"
#include "headers/gb_ppu.h"

struct mmu mmu;



void MMU_init() {

    mmu.mbc_type = 0;
    mmu.mbc_useRam = 0;
    mmu.mbc_isRamActive = 0;
    mmu.mbc_romBank = 1;

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


void MBC1_writeToRom(uint16_t addr, uint8_t val) {
    if (addr >= 0x0000 && addr <= 0x1fff) {
        if (val == 0x00)
            mmu.mbc_isRamActive = 0;
        else
            mmu.mbc_isRamActive = 1;
    }
    else if (addr >= 0x2000 && addr <= 0x3fff) {
        if (val == 0x00) { mmu.mbc_romBank = 0x01; return; }
        if (val == 0x20) { mmu.mbc_romBank = 0x21; return; }
        if (val == 0x40) { mmu.mbc_romBank = 0x41; return; }
        if (val == 0x60) { mmu.mbc_romBank = 0x61; return; }

        mmu.mbc_romBank = 0x1f & val;
    }
    else if (addr >= 0x4000 && addr <= 0x5fff) {
        if (mmu.mbc_hasRam) {
            mmu.mbc_ramBank = val & 0x03;
        }
        else
            printf("Should implement bigger ROM for MBC1\n");
    }
    else if (addr >= 0x6000 && addr <= 0x7fff) {
        printf("Should implement ram mode for MBC1\n");
    }
}

void MBC2_writeToRom(uint16_t addr, uint8_t val) {

}

void MBC3_writeToRom(uint16_t addr, uint8_t val) {

}


void loadCartridge(char* path) {
    FILE *cartridgePtr;

    cartridgePtr = fopen(path, "rb"); // b is for binary

    if (cartridgePtr == NULL)
        printf("Could not open the file\n");

    fseek(cartridgePtr, 0, SEEK_END);

    size_t size = ftell(cartridgePtr);

    fseek(cartridgePtr, 0L, SEEK_SET);

    for (unsigned int i = 0; i < size; ++i) {
        uint8_t c = fgetc(cartridgePtr);
        mmu.cartridge_data[i] = c;
    }

    fclose(cartridgePtr);

    // we check the mbc type
    uint8_t mbc_type = mmu.cartridge_data[0x0147];
    switch (mbc_type) {
        case 0x00: mmu.mbc_type = 0; break;
        case 0x01: mmu.mbc_type = 1; break;
        case 0x02: mmu.mbc_type = 1; mmu.mbc_hasRam = 1; break;
        case 0x05: mmu.mbc_type = 2; break;
        default: printf("You should implement more memory banks\n");
                 break;
    }

    // if the type is 0, we load the cartridge directly in the rom
    if (mmu.mbc_type == 0) {
        printf("It is a type 0 mbc\n");
        for (int i = 0; i < ROM_BANK_SIZE; i++) {
            mmu.rom[i] = mmu.cartridge_data[i];
        }
    }
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
    // BEGIN ROM
    // should not be able to write here

    if (addr >= 0x0000 && addr <= 0x7fff) {
        if (mmu.mbc_type == 1) {
            MBC1_writeToRom(addr, val);
        }
        else if (mmu.mbc_type == 2) {
            MBC2_writeToRom(addr, val);
        }
        else if (mmu.mbc_type == 3) {
            MBC3_writeToRom(addr, val);
        }
    }
    // if (addr >= 0x0000 &&  addr <= 0x3fff) {
    //     mmu.rom[addr] = val;
    // }
    // else if (addr >= 0x4000 && addr <= 0x7fff) {
    //     mmu.rom[addr - 0x4000] = val;
    // }
    //END ROM
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