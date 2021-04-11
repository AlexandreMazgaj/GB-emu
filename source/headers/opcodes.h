#include "gb_cpu.h"
#include "gb_mmu.h"
#include "constants.h"


typedef uint8_t (*Operation)(void);

struct instructions {
    char* mnemonic;
    Operation execute;
    uint8_t nb_cycle;
} const extern instructions[INSTRUCTIONS_SIZE];



uint8_t exe_nop() {
    registers.pc++;
    return 0;
}


uint8_t exe_ldbcd16() {
    uint16_t data = readWord(++registers.pc);
    registers.bc = data;
    return 0;
}

uint8_t exe_ldpbca() {
    writeByte(registers.bc, registers.a);
    return 0;
}

uint8_t exe_incbc() {
    registers.bc++;
    return 0;
}

uint8_t exe_incb() {
    inc8bReg(&registers.b);
    return 0;
}

uint8_t exe_decb() {
    dec8bReg(&registers.b);
    return 0;
}

uint8_t exe_ldbd8() {
    registers.b = readByte(++registers.pc);
    return 0;
}