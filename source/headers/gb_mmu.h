#pragma once

#include <stdint.h>
#include "constants.h"

struct mmu {
    uint8_t rom[ROM_BANK_SIZE];
    uint8_t video_ram[RAM_SIZE];
    uint8_t external_ram[RAM_SIZE];
    uint8_t work_ram[RAM_SIZE];
    uint8_t high_ram[HIGH_RAM_SIZE];

    // holds the data of the cartridge
    uint8_t cartridge_data[MAX_CARTRIDGE_SIZE];

    // mbc attributes
    uint8_t mbc_type;
    uint8_t mbc_useRam;

} extern mmu;


MMU_init();

void loadCartridge(char* path);


uint8_t readByte(uint16_t addr);
uint16_t readWord(uint16_t addr);

void writeByte (uint16_t addr, uint8_t val);
void writeWord(uint16_t  addr, uint16_t val);

uint16_t popWordStack();

void pushWordStack(uint16_t val);