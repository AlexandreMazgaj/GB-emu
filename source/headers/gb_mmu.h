#pragma once

#include <stdint.h>
#include "constants.h"

struct mmu {
    uint8_t rom[MAX_CARTRIDGE_SIZE];

    uint8_t video_ram[RAM_SIZE];
    uint8_t external_ram[MAX_RAM_SIZE];
    uint8_t work_ram[RAM_SIZE];
    uint8_t high_ram[HIGH_RAM_SIZE];


    // mbc attributes
    uint8_t mbc_type;
    uint8_t mbc_hasRam;
    uint8_t mbc_isRamActive;
    uint8_t mbc_romBank;
    uint8_t mbc_ramBank;

    uint8_t mbc_nbRomBank;

    uint8_t mbc_ramMode;

} extern mmu;


void MMU_init();


void MBC1_writeToRom(uint16_t addr, uint8_t val);
void MBC1_writeRam(uint16_t addr, uint8_t val);
uint8_t MBC1_readRom(uint16_t addr);
uint8_t MBC1_readRam(uint16_t addr);

void MBC2_writeToRom(uint16_t addr, uint8_t val);
void MBC2_writeRam(uint16_t addr, uint8_t val);
uint8_t MBC2_readRom(uint16_t addr);
uint8_t MBC2_readRam(uint16_t addr);

void MBC3_writeToRom(uint16_t addr, uint8_t val);
void MBC3_writeRam(uint16_t addr, uint8_t val);
uint8_t MBC3_readRom(uint16_t addr);
uint8_t MBC3_readRam(uint16_t addr);


void loadCartridge(char* path);


void oam_dma(uint8_t hi);

uint8_t readByte(uint16_t addr);
uint16_t readWord(uint16_t addr);

void writeByte (uint16_t addr, uint8_t val);
void writeWord(uint16_t  addr, uint16_t val);

uint16_t popWordStack();

void pushWordStack(uint16_t val);