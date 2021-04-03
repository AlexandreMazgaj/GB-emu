#include <stdint.h>
#include "constants.h"

struct mmu {
    uint8_t rom_bank0[ROM_BANK_SIZE];
    uint8_t rom_bankn[ROM_BANK_SIZE];
    uint8_t video_ram[RAM_SIZE];
    uint8_t external_ram[RAM_SIZE];
    uint8_t work_ram[RAM_SIZE];
    uint8_t oam[OAM_SIZE];
    uint8_t high_ram[HIGH_RAM_SIZE];


} extern mmu;


uint8_t readByte(uint16_t addr);
uint16_t readWord(uint16_t addr);

void writeByte (uint16_t addr, uint8_t val);
void writeWord(uint16_t  addr, uint16_t val);
