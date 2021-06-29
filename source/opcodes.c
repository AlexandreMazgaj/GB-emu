#include "headers/opcodes.h"

const struct instruction instructions[INSTRUCTIONS_SIZE] = {
    // 0x0
    {"NOP", &exe_nop, 4, 0},
    {"LD BC, d16", &exe_ldbcd16, 12, 2},
    {"LD (BC), A", &exe_ldpbca, 8, 0},
    {"INC BC", &exe_incbc, 8, 0},
    {"INC B", &exe_incb, 4, 0},
    {"DEC B", &exe_decb, 4, 0},
    {"LD B, d8", &exe_ldbd8, 8, 1},
    {"RLCA", &exe_rlca, 4, 0},
    {"LD (a16), SP", &exe_ldpa16sp, 20, 2},
    {"ADD HL, BC", &exe_addhlbc, 8, 0},
    {"LD A, (BC)", &exe_ldapbc, 8, 0},
    {"DEC BC", &exe_decbc, 8, 0},
    {"INC C", &exe_incc, 4, 0},
    {"DEC C", &exe_decc, 4, 0},
    {"LD C, d8", &exe_ldcd8, 8, 1},
    {"RRCA", &exe_rrca, 4, 0},
    // 0x1
    {"STOP", &exe_stop, 4, 1},
    {"LD DE, d16", &exe_ldded16, 12, 2},
    {"LD (DE), A", &exe_ldpdea, 8, 0},
    {"INC DE", &exe_incde, 8, 0},
    {"INC D", &exe_incd, 4, 0},
    {"DEC D", &exe_decd, 4, 0},
    {"LD D, d8", &exe_lddd8, 8, 1},
    {"RLA", &exe_rla, 4, 0},
    {"JR i8", &exe_jri8, 12, 1},
    {"ADD HL, DE", &exe_addhlde, 8, 0},
    {"LD A, (DE)", &exe_ldapde, 8, 0},
    {"DEC DE", &exe_decde, 8, 0},
    {"INC E", &exe_ince, 4, 0},
    {"DEC E", &exe_dece, 4, 0},
    {"LD E, d8", &exe_lded8, 8, 1},
    {"RRA", &exe_rra, 4, 0},
    //0x2
    {"JR NZ, R8", &exe_jrnzr8, 8, 1},
    {"LD HL, d16", &exe_ldhld16, 12, 2}
};


void handleUnknownOp(uint8_t opcode) {
    printf("unknown opcode: %X\n", opcode);
}



uint8_t exe_nop() {
    // registers.pc++;
    asm("nop"::);
    return 0;
}


uint8_t exe_ldbcd16() {
    registers.bc = readWord(++registers.pc);
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

uint8_t exe_stop() {
    stopped = 1;
    return 0;
}

uint8_t exe_ldded16() {
    registers.de = readWord(++registers.pc);
    return 0;
}

uint8_t exe_ldpdea() {
    writeByte(registers.de, registers.a);
    return 0;
}

uint8_t exe_incde() {
    registers.de++;
    return 0;
}

uint8_t exe_incd() {
    inc8bReg(&registers.d);
    return 0;
}

uint8_t exe_decd() {
    dec8bReg(&registers.d);
    return 0;
}

uint8_t exe_lddd8() {
    registers.d = readByte(++registers.pc);
    return 0;
}

uint8_t exe_rla() {
    rotateLeftCarry(&registers.a);
    return 0;
}

uint8_t exe_jri8() {
    uint8_t offset = readByte(++registers.pc);
    registers.pc += offset;
    return 0;
}

uint8_t exe_addhlde() {
    add_hl(registers.de);
    return 0;
}


uint8_t exe_ldapde() {
    registers.a = readByte(registers.de);
    return 0;
}

uint8_t exe_decde() {
    registers.de--;
    return 0;
}

uint8_t exe_ince() {
    inc8bReg(&registers.e);
    return 0;
}

uint8_t exe_dece() {
    dec8bReg(&registers.e);
    return 0;
}

uint8_t exe_lded8() {
    registers.e = readByte(++registers.pc);
    return 0;
}

uint8_t exe_rra() {
    rotateRightCarry(&registers.a);
    return 0;
}

uint8_t exe_jrnzr8() {
    if (!GETZFLAG()) {
        registers.pc += readByte(++registers.pc);
        return 4;
    }
    return 0;
}

uint8_t exe_ldhld16() {
    registers.hl = readWord(++registers.pc);
    return 0;
}

uint8_t exe_ldphlpa() {

}

uint8_t exe_inchl() {

}