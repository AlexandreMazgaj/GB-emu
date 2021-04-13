#pragma once

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

uint8_t exe_rlca() {
    rotateLeft(&registers.a);
    return 0;
}

uint8_t exe_ldpa16sp() {
    uint16_t addr = readWord(++registers.pc);
    writeWord(addr, registers.sp);
    return 0;
}

uint8_t exe_addhlbc() {
   add_hl(registers.bc);
   return 0; 
}

uint8_t exe_ldapbc() {
    registers.a = readByte(registers.bc);
    return 0;
}

uint8_t exe_decbc() {
    registers.bc--;
    return 0;
}

uint8_t exe_incc() {
    inc8bReg(&registers.c);
    return 0;
}

uint8_t exe_decc() {
    dec8bReg(&registers.c);
    return 0;
}

uint8_t exe_ldcd8() {
    registers.c = readByte(++registers.pc);
    return 0;
}

uint8_t exe_rrca() {
    rotateRight(&registers.a);
    return 0;
}

