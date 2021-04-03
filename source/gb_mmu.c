#include "headers/gb_mmu.h"

struct mmu mmu;

uint8_t readByte(uint16_t addr) {
    if (addr >= 0x0000 &&  addr <= 0x3fff) {
        return mmu.rom_bank0[addr];
    }
    else if (addr >= 0x4000 && addr <= 0x7fff) {
        return mmu.rom_bankn[addr - 0x4000];
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
        return mmu.oam[addr - 0xfe00];
    }
    else if (addr >= 0xff80 && addr <= 0xfffe) {
        return mmu.high_ram[addr - 0xff80];
    }
}

uint16_t readWord(uint16_t addr) {
    return ((uint16_t)readByte(addr) | (uint16_t)(readByte(addr+1) << 8));
}


void writeByte(uint16_t addr, uint8_t val) {
    if (addr >= 0x0000 &&  addr <= 0x3fff) {
        mmu.rom_bank0[addr] = val;
    }
    else if (addr >= 0x4000 && addr <= 0x7fff) {
        mmu.rom_bankn[addr - 0x4000] = val;
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
        mmu.oam[addr - 0xfe00] = val;
    }
    else if (addr >= 0xff80 && addr <= 0xfffe) {
        mmu.high_ram[addr - 0xff80] = val;
    }
}


void writeWord(uint16_t addr, uint16_t val) {
    uint8_t hi = ((uint8_t)(val >> 8));
    uint8_t lo = ((uint8_t)val);

    writeByte(addr, lo);
    writeByte(addr+1, hi);

}