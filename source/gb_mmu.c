#include "headers/gb_mmu.h"
#include "headers/gb_cpu.h"
#include "headers/gb_ppu.h"
#include "headers/serial.h"
#include <stdio.h>
#include <stdlib.h>

struct mmu mmu;

void MMU_init() {

  mmu.mbc_type = 0;
  mmu.mbc_hasRam = 0;
  mmu.mbc_isRamActive = 0;
  mmu.mbc_romBank = 1;

  serial.control = 0x0;
  serial.data = 0x0;

  srand(2022);

  for (int i = 0; i < MAX_CARTRIDGE_SIZE; i++) {
    mmu.rom[i] = 0;
  }

  for (int i = 0; i < RAM_SIZE; i++) {
    mmu.external_ram[i] = (uint8_t)rand() % 256;
  }

  for (int i = 0; i < RAM_SIZE; i++) {
    mmu.work_ram[i] = (uint8_t)rand() % 256;
  }

  for (int i = 0; i < HIGH_RAM_SIZE; i++) {
    mmu.high_ram[i] = (uint8_t)rand() % 256;
  }
}

// MBC 1 FUNCTIONS
// ---------------
void MBC1_writeToRom(uint16_t addr, uint8_t val) {
  if (addr >= 0x0000 && addr <= 0x1fff) {
    mmu.mbc_isRamActive = ((val & 0xf) == 0xa);
  } else if (addr >= 0x2000 && addr <= 0x3fff) {
    if ((val & 0xf) == 0)
      val += 1;

    mmu.mbc_romBank = (mmu.mbc_romBank & 0x60) | (0x1f & val);
  } else if (addr >= 0x4000 && addr <= 0x5fff) {
    if (mmu.mbc_ramMode) {
      mmu.mbc_ramBank = val & 0x03;
    } else {
      mmu.mbc_romBank = (mmu.mbc_romBank & 0x1f) | ((val & 0x03) << 5);
    }
  } else if (addr >= 0x6000 && addr <= 0x7fff) {
    mmu.mbc_ramMode = (val & 0x01);
  }
}

void MBC1_writeRam(uint16_t addr, uint8_t val) {
  if (!mmu.mbc_isRamActive)
    return;

  if (mmu.mbc_ramMode == 0) {
    mmu.external_ram[addr - 0xa000] = val;
    return;
  }

  mmu.external_ram[(addr - 0xa000) + (mmu.mbc_ramBank * 0x2000)] = val;
}

uint8_t MBC1_readRom(uint16_t addr) {
  // we mask the bank number to the number of banks available
  uint8_t bank = mmu.mbc_romBank & (mmu.mbc_nbRomBank + 1);

  return mmu.rom[(addr - 0x4000) + bank * 0x4000];
}

uint8_t MBC1_readRam(uint16_t addr) {
  if (!mmu.mbc_isRamActive)
    return 0;
  if (mmu.mbc_ramMode == 0) {
    return mmu.external_ram[addr - 0xa000];
  }

  return mmu.external_ram[(addr - 0xa000) + (mmu.mbc_ramBank * 0x2000)];
}

// MBC 2 FUNCTION
// --------------
void MBC2_writeToRom(uint16_t addr, uint8_t val) {
  printf("MBC2_writeToRom to implement\n");
}

void MBC2_writeRam(uint16_t addr, uint8_t val) {
  printf("MBC2_writeRam to implement\n");
}

uint8_t MBC2_readRom(uint16_t addr) {
  // the same than for MBC1
  return MBC1_readRom(addr);
}

uint8_t MBC2_readRam(uint16_t addr) {
  printf("MBC2_readRam to implement\n");
  return 0;
}

// MBC 3 FUNCTIONS
// ---------------
void MBC3_writeToRom(uint16_t addr, uint8_t val) {
  printf("MBC3_writeToRom to implement\n");
}

void MBC3_writeRam(uint16_t addr, uint8_t val) {
  printf("MBC3_writeRam to implement\n");
}

uint8_t MBC3_readRom(uint16_t addr) {
  printf("MBC3_readRom to implement\n");
  return 0;
}

uint8_t MBC3_readRam(uint16_t addr) {
  printf("MBC3_readRam to implement\n");
  return 0;
}

// MEMORY UNIT FUNCTIONS
// ---------------------

uint8_t loadCartridge(char *path) {
  FILE *cartridgePtr;

  cartridgePtr = fopen(path, "rb"); // b is for binary

  if (cartridgePtr == NULL) {
    printf("Could not open the file\n");
    return 1;
  }

  fseek(cartridgePtr, 0, SEEK_END);

  size_t size = ftell(cartridgePtr);

  printf("File size: %d\n", size);

  rewind(cartridgePtr);

  fread(mmu.rom, size, 1, cartridgePtr);

  // getchar();

  // for (unsigned int i = 0; i < size; ++i) {
  //     printf("rom[%d]: %X\n", i, mmu.rom[i]);
  // }

  fclose(cartridgePtr);

  // we check the mbc type
  uint8_t mbc_type = mmu.rom[0x0147];
  switch (mbc_type) {
  case 0x00:
    mmu.mbc_type = 0;
    printf("No memory bank\n");
    break;
  case 0x01:
    mmu.mbc_type = 1;
    printf("Memory bank type 1\n");
    break;
  case 0x02:
    mmu.mbc_type = 1;
    printf("Memory bank type 1 with ram\n");
    mmu.mbc_hasRam = 1;
    break;
  case 0x05:
    mmu.mbc_type = 2;
    printf("Memory bank type 2\n");
    break;
  default:
    printf("You should implement more memory banks\n");
    break;
  }

  // we get the number of rom banks
  uint8_t romSizeType = mmu.rom[0x0148];
  switch (romSizeType) {
  case 0x00:
    mmu.mbc_nbRomBank = 0;
    printf("0 memory bank\n");
    break; // no extra rom
  case 0x01:
    mmu.mbc_nbRomBank = 2;
    printf("2 memory banks\n");
    break; // 32kib more --> 2 banks extra
  case 0x02:
    mmu.mbc_nbRomBank = 6;
    printf("6 memory banks\n");
    break; // 96kib more --> 6 banks extra
  case 0x03:
    mmu.mbc_nbRomBank = 14;
    printf("14 memory banks\n");
    break; // 224kib more --> 14 banks extra
  case 0x04:
    mmu.mbc_nbRomBank = 30;
    printf("30 memory banks\n");
    break; // 480kib more --> 30 banks extra
  }
  return 0;
}

void oam_dma(uint8_t hi) {
  printf("should be going here\n");
  for (uint16_t i = 0x00; i < 0x9f + 1; i++) {
    uint16_t readAddr = ((uint16_t)hi << 8) | i;
    uint16_t oamAddr = ((uint16_t)0xfe << 8) | i;
    writeByte(oamAddr, readByte(readAddr));
  }
}

// TODO Finish readByte function
uint8_t readByte(uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0x3fff) {
    return mmu.rom[addr];
  } else if (addr >= 0x4000 && addr <= 0x7fff) {
    if (mmu.mbc_type == 1)
      return MBC1_readRom(addr);
    if (mmu.mbc_type == 2)
      return MBC2_readRom(addr);
    if (mmu.mbc_type == 3)
      return MBC3_readRom(addr);

    // if no memory bank, then we just read from rom with no switch
    return mmu.rom[addr];
  } else if (addr >= 0x8000 && addr <= 0x9fff) {
    return ppu.video_ram[addr - 0x8000];
  } else if (addr >= 0xa000 && addr <= 0xbfff) {
    if (mmu.mbc_type == 1)
      return MBC1_readRam(addr);
  } else if (addr >= 0xc000 && addr <= 0xdfff) {
    return mmu.work_ram[addr - 0xc000];
  } else if (addr >= 0xfe00 && addr <= 0xfe9f) {
    return ppu.oam[addr - 0xfe00];
  }
  // 0xff00 controller
  // 0xff01 - 02 communication
  else if (addr == 0xff01) {
    printf("Returning %X from serial\n", serial.data);
    return serial.data;
  } else if (addr == 0xff02) {
    // printf("READING FROM SERIAL %X\n", serial.control);
    return serial.control;
  }
  // 0xff04 - 07 Divider and timer
  //
  else if (addr >= 0xff40 && addr <= 0xff69) {
    // return 0;
    return readPPU(addr);
  } else if (addr >= 0xff80 && addr <= 0xfffe) {
    return mmu.high_ram[addr - 0xff80];
  } else if (addr == 0xff0f) {
    return IF;
  } else if (addr == 0xffff) {
    return IE;
  }
}

uint16_t readWord(uint16_t addr) {
  return ((uint16_t)readByte(addr) | (uint16_t)(readByte(addr + 1) << 8));
}

// TODO finish writeByte function
void writeByte(uint16_t addr, uint8_t val) {
  // printf("writing addr: %X, val: %X\n", addr, val);

  // BEGIN ROM
  // should not be able to write here

  if (addr >= 0x0000 && addr <= 0x7fff) {
    if (mmu.mbc_type == 1) {
      MBC1_writeToRom(addr, val);
    } else if (mmu.mbc_type == 2) {
      MBC2_writeToRom(addr, val);
    } else if (mmu.mbc_type == 3) {
      MBC3_writeToRom(addr, val);
    }
  } else if (addr >= 0x8000 && addr <= 0x9fff) {
    // printf("write to the ppu addr: %X, val: %X\n", addr, val);
    ppu.video_ram[addr - 0x8000] = val;
  } else if (addr >= 0xa000 && addr <= 0xbfff) {
    if (mmu.mbc_type == 1)
      MBC1_writeRam(addr, val);
    if (mmu.mbc_type == 2)
      MBC2_writeRam(addr, val);
    if (mmu.mbc_type == 3)
      MBC3_writeRam(addr, val);
  } else if (addr >= 0xc000 && addr <= 0xdfff) {
    mmu.work_ram[addr - 0xc000] = val;
  } else if (addr >= 0xfe00 && addr <= 0xfe9f) {
    ppu.oam[addr - 0xfe00] = val;
  }
  // 0xff00 controller
  // 0xff01 - 02 communication
  else if (addr == 0xff01) {
    // printf("Writing %X to serial\n", val);
    serial.data = val;
  } else if (addr == 0xff02) {
    // printf("WRITING TO SERIAL %X\n", val);

    serial.control = val;
    if (serial.control == 0x81) {
      // serial.data = val;
      serial.interrupt = 0x8;
    }
  }
  // 0xff04 - 07 Divider and timer
  //
  else if (addr >= 0xff40 && addr <= 0xff69) {
    // OAM DMA
    if (addr == 0xff46) {
      // printf("DOING A DMA TRANSFER\n");
      oam_dma(val);
    } else {
      // printf("WRITING TO THE PPU\n");
      writePPU(addr, val);
    }
  } else if (addr >= 0xff80 && addr <= 0xfffe) {
    // if (addr == 0xff80) {
    //     printf("WRITING: %X at ff80\n", val);
    // }
    // else if (addr == 0xff83) {
    //     printf("Writing: %X at 0xff83\n", val);
    // }
    mmu.high_ram[addr - 0xff80] = val;
  } else if (addr == 0xff0f) {
    IF = val;
  } else if (addr == 0xffff) {
    IE = val;
  }
}

void writeWord(uint16_t addr, uint16_t val) {
  uint8_t hi = ((uint8_t)(val >> 8));
  uint8_t lo = ((uint8_t)val);

  writeByte(addr, lo);
  writeByte(addr + 1, hi);
}

uint16_t popWordStack() {
  uint16_t val = readWord(registers.sp);
  registers.sp += 2;
  return val;
}

void pushWordStack(uint16_t val) {
  if (val == 0x3040)
    printf("PUSHING 0x3040\n");
  registers.sp -= 2;
  writeWord(registers.sp, val);
}