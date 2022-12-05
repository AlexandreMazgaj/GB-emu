#include "headers/opcodes.h"

const struct instruction instructions[INSTRUCTIONS_SIZE] = {
    // 0x0
    {"NOP", &exe_nop, 4, 0},                            // 0
    {"LD BC, 0x%X", &exe_ldbcd16, 12, 2},                // 1
    {"LD (BC), A", &exe_ldpbca, 8, 0},                  // 2
    {"INC BC", &exe_incbc, 8, 0},                       // 3
    {"INC B", &exe_incb, 4, 0},                         // 4
    {"DEC B", &exe_decb, 4, 0},                         // 5
    {"LD B, 0x%X", &exe_ldbd8, 8, 1},                     // 6
    {"RLCA", &exe_rlca, 4, 0},                          // 7
    {"LD (0x%X), SP", &exe_ldpa16sp, 20, 2},             // 8
    {"ADD HL, BC", &exe_addhlbc, 8, 0},                 // 9
    {"LD A, (BC)", &exe_ldapbc, 8, 0},                  // a
    {"DEC BC", &exe_decbc, 8, 0},                       // b
    {"INC C", &exe_incc, 4, 0},                         // c
    {"DEC C", &exe_decc, 4, 0},                         // d
    {"LD C, 0x%X", &exe_ldcd8, 8, 1},                     // e
    {"RRCA", &exe_rrca, 4, 0},                          // f
    // 0x1          
    {"STOP", &exe_stop, 4, 1},                          // 0
    {"LD DE, 0x%X", &exe_ldded16, 12, 2},                // 1
    {"LD (DE), A", &exe_ldpdea, 8, 0},                  // 2
    {"INC DE", &exe_incde, 8, 0},                       // 3
    {"INC D", &exe_incd, 4, 0},                         // 4
    {"DEC D", &exe_decd, 4, 0},                         // 5
    {"LD D, 0x%X", &exe_lddd8, 8, 1},                     // 6
    {"RLA", &exe_rla, 4, 0},                            // 7
    {"JR i8", &exe_jri8, 12, 1},                        // 8
    {"ADD HL, DE", &exe_addhlde, 8, 0},                 // 9
    {"LD A, (DE)", &exe_ldapde, 8, 0},                  // a
    {"DEC DE", &exe_decde, 8, 0},                       // b
    {"INC E", &exe_ince, 4, 0},                         // c
    {"DEC E", &exe_dece, 4, 0},                         // d
    {"LD E, 0x%X", &exe_lded8, 8, 1},                     // e
    {"RRA", &exe_rra, 4, 0},                            // f
    // 0x2
    {"JR NZ, 0x%X", &exe_jrnzr8, 8, 1},                   // 0
    {"LD HL, 0x%X", &exe_ldhld16, 12, 2},                // 1
    {"LD (HL+), A", &exe_ldphlia, 8, 0},                // 2
    {"INC HL", &exe_inchl, 8, 0},                       // 3
    {"INC H", &exe_inch, 4, 0},                         // 4
    {"DEC H", &exe_dech, 4, 0},                         // 5
    {"LD H, 0x%X", &exe_ldhd8, 8, 1},                     // 6
    {"DAA", &exe_daa, 4, 0},                            // 7
    {"JR z, 0x%X", &exe_jrzr8, 8, 1},                     // 8
    {"ADD HL, HL", &exe_addhlhl, 8, 0},                 // 9
    {"LD A, (HL+)", &exe_ldaphli, 8, 0},                // a
    {"DEC HL", &exe_dechl, 8, 0},                       // b
    {"INC L", &exe_incl, 4, 0},                         // c
    {"DEC L", &exe_decl, 4, 0},                         // d
    {"LD L, 0x%X", &exe_ldld8, 8, 1},                     // e
    {"CPL", &exe_cpl, 4, 0},                            // f
    // 0x3
    {"JR NC, 0x%X", &exe_jrncr8, 8, 1},                   // 0
    {"LD SP, 0x%X", &exe_ldspd16, 12, 2},                // 1
    {"LD (HL-), A", &exe_ldphlda, 8, 0},                // 2
    {"INC SP", &exe_incsp, 8, 0},                       // 3
    {"INC (HL)", &exe_incphl, 12, 0},                   // 4
    {"DEC (HL)", &exe_decphl, 12, 0},                   // 5
    {"LD (HL), 0x%X", &exe_ldphld8, 12, 0},               // 6
    {"SCF", &exe_scf, 4, 0},                            // 7
    {"JR C, 0x%X", &exe_jrcr8, 8, 1},                     // 8
    {"ADD HL, SP", &exe_addhlsp, 8, 0},                 // 9
    {"LD A, (HL-)", &exe_ldaphld, 8, 0},                // a
    {"DEC SP", &exe_decsp, 8, 0},                       // b
    {"INC A", &exe_inca, 4, 0},                         // c
    {"DEC A", &exe_deca, 4, 0},                         // d
    {"LD A, 0x%X", &exe_ldad8, 8, 1},                     // e
    {"CCF", &exe_ccf, 4, 0},                            // f
    // 0x4
    {"LD B, B", &exe_ldbb, 4, 0},                       // 0
    {"LD B, C", &exe_ldbc, 4, 0},                       // 1
    {"LD B, D", &exe_ldbd, 4, 0},                       // 2
    {"LD B, E", &exe_ldbe, 4, 0},                       // 3
    {"LD B, H", &exe_ldbh, 4, 0},                       // 4
    {"LD B, L", &exe_ldbl, 4, 0},                       // 5
    {"LD B, (HL)", &exe_ldbphl, 8, 0},                  // 6
    {"LD B, A", &exe_ldba, 4, 0},                       // 7
    {"LD C, B", &exe_ldcb, 4, 0},                       // 8
    {"LD C, C", &exe_ldcc, 4, 0},                       // 9
    {"LD C, D", &exe_ldcd, 4, 0},                       // a
    {"LD C, E", &exe_ldce, 4, 0},                       // b
    {"LD C, H", &exe_ldch, 4, 0},                       // c
    {"LD C, L", &exe_ldcl, 4, 0},                       // d
    {"LD C, (HL)", &exe_ldcphl, 8, 0},                  // e
    {"LD C, A", &exe_ldca, 4, 0},                       // f
    // 0x5
    {"LD D, B", &exe_lddb, 4, 0},                       // 0
    {"LD D, C", &exe_lddc, 4, 0},                       // 1
    {"LD D, D", &exe_lddd, 4, 0},                       // 2
    {"LD D, E", &exe_ldde, 4, 0},                       // 3
    {"LD D, H", &exe_lddh, 4, 0},                       // 4
    {"LD D, L", &exe_lddl, 4, 0},                       // 5
    {"LD D, (HL)", &exe_lddphl, 8, 0},                  // 6
    {"LD D, A", &exe_ldda, 4, 0},                       // 7
    {"LD E, B", &exe_ldeb, 4, 0},                       // 8
    {"LD E, C", &exe_ldec, 4, 0},                       // 9
    {"LD E, D", &exe_lded, 4, 0},                       // a
    {"LD E, E", &exe_ldee, 4, 0},                       // b
    {"LD E, H", &exe_ldeh, 4, 0},                       // c
    {"LD E, L", &exe_ldel, 4, 0},                       // d
    {"LD E, (HL)", &exe_ldephl, 8, 0},                  // e
    {"LD E, A", &exe_ldea, 4, 0},                       // f
    // 0x6
    {"LD H, B", &exe_ldhb, 4, 0},
    {"LD H, C", &exe_ldhc, 4, 0},
    {"LD H, D", &exe_ldhd, 4, 0},
    {"LD H, E", &exe_ldhe, 4, 0},
    {"LD H, H", &exe_ldhh, 4, 0},
    {"LD H, L", &exe_ldhl, 4, 0},
    {"LD H, (HL)", &exe_ldhphl, 8, 0},
    {"LD H, A", &exe_ldha, 4, 0},
    {"LD L, B", &exe_ldlb, 4, 0},
    {"LD L, C", &exe_ldlc, 4, 0},
    {"LD L, D", &exe_ldld, 4, 0},
    {"LD L, E", &exe_ldle, 4, 0},
    {"LD L, H", &exe_ldlh, 4, 0},
    {"LD L, L", &exe_ldll, 4, 0},
    {"LD L, (HL)", &exe_ldlphl, 8, 0},
    {"LD L, A", &exe_ldla, 4, 0},
    // 0x7
    {"LD (HL), B", &exe_ldphlb, 4, 0},
    {"LD (HL), C", &exe_ldphlc, 4, 0},
    {"LD (HL), D", &exe_ldphld, 4, 0},
    {"LD (HL), E", &exe_ldphle, 4, 0},
    {"LD (HL), H", &exe_ldphlh, 4, 0},
    {"LD (HL), L", &exe_ldphll, 4, 0},
    {"HALT", &exe_halt, 4, 0},
    {"LD (HL), A", &exe_ldphla, 4, 0},
    {"LD A, B", &exe_ldab, 4, 0},
    {"LD A, C", &exe_ldac, 4, 0},
    {"LD A, D", &exe_ldad, 4, 0},
    {"LD A, E", &exe_ldae, 4, 0},
    {"LD A, H", &exe_ldah, 4, 0},
    {"LD A, L", &exe_ldal, 4, 0},
    {"LD A, (HL)", &exe_ldaphl, 8, 0},
    {"LD A, A", &exe_ldaa, 4, 0},
    // 0x8
    {"ADD A, B", &exe_addab, 4, 0},
    {"ADD A, C", &exe_addac, 4, 0},
    {"ADD A, D", &exe_addad, 4, 0},
    {"ADD A, E", &exe_addae, 4, 0},
    {"ADD A, H", &exe_addah, 4, 0},
    {"ADD A, L", &exe_addal, 4, 0},
    {"ADD A, (HL)", &exe_addaphl, 8, 0},
    {"ADD A, A", &exe_addaa, 4, 0},
    {"ADC A, B", &exe_adcab, 4, 0},
    {"ADC A, C", &exe_adcac, 4, 0},
    {"ADC A, D", &exe_adcad, 4, 0},
    {"ADC A, E", &exe_adcae, 4, 0},
    {"ADC A, H", &exe_adcah, 4, 0},
    {"ADC A, L", &exe_adcal, 4, 0},
    {"ADC A, (HL)", &exe_adcaphl, 8, 0},
    {"ADC A, A", &exe_adcaa, 4, 0},
    // 0x9
    {"SUB A, B", &exe_subab, 4, 0},
    {"SUB A, C", &exe_subac, 4, 0},
    {"SUB A, D", &exe_subad, 4, 0},
    {"SUB A, E", &exe_subae, 4, 0},
    {"SUB A, H", &exe_subah, 4, 0},
    {"SUB A, L", &exe_subal, 4, 0},
    {"SUB A, (HL)", &exe_subaphl, 8, 0},
    {"SUB A, A", &exe_subaa, 4, 0},
    {"SBC A, B", &exe_sbcab, 4, 0},
    {"SBC A, C", &exe_sbcac, 4, 0},
    {"SBC A, D", &exe_sbcad, 4, 0},
    {"SBC A, E", &exe_sbcae, 4, 0},
    {"SBC A, H", &exe_sbcah, 4, 0},
    {"SBC A, L", &exe_sbcal, 4, 0},
    {"SBC A, (HL)", &exe_sbcaphl, 8, 0},
    {"SBC A, A", &exe_sbcaa, 4, 0},
    // 0xa
    {"AND A, B", &exe_andab, 4, 0},
    {"AND A, C", &exe_andac, 4, 0},
    {"AND A, D", &exe_andad, 4, 0},
    {"AND A, E", &exe_andae, 4, 0},
    {"AND A, H", &exe_andah, 4, 0},
    {"AND A, L", &exe_andal, 4, 0},
    {"AND A, (HL)", &exe_andaphl, 8, 0},
    {"AND A, A", &exe_andaa, 4, 0},
    {"XOR A, B", &exe_xorab, 4, 0},
    {"XOR A, C", &exe_xorac, 4, 0},
    {"XOR A, D", &exe_xorad, 4, 0},
    {"XOR A, E", &exe_xorae, 4, 0},
    {"XOR A, H", &exe_xorah, 4, 0},
    {"XOR A, L", &exe_xoral, 4, 0},
    {"XOR A, (HL)", &exe_xoraphl, 8, 0},
    {"XOR A, A", &exe_xoraa, 4, 0},
    // 0xb
    {"OR A, B", &exe_orab, 4, 0},
    {"OR A, C", &exe_orac, 4, 0},
    {"OR A, D", &exe_orad, 4, 0},
    {"OR A, E", &exe_orae, 4, 0},
    {"OR A, H", &exe_orah, 4, 0},
    {"OR A, L", &exe_oral, 4, 0},
    {"OR A, (HL)", &exe_oraphl, 8, 0},
    {"OR A, A", &exe_oraa, 4, 0},
    {"CP A, B", &exe_cpab, 4, 0},
    {"CP A, C", &exe_cpac, 4, 0},
    {"CP A, D", &exe_cpad, 4, 0},
    {"CP A, E", &exe_cpae, 4, 0},
    {"CP A, H", &exe_cpah, 4, 0},
    {"CP A, L", &exe_cpal, 4, 0},
    {"CP A, (HL)", &exe_cpaphl, 8, 0},
    {"CP A, A", &exe_cpaa, 4, 0},
    // 0xc
    {"RET NZ", &exe_retnz, 8, 0},
    {"POP BC", &exe_popbc, 12, 0},
    {"JP NZ, 0x%X", &exe_jpnza16, 12, 2},
    {"JP 0x%X", &exe_jpa16, 16, 2},
    {"CALL NZ, 0x%X", &exe_callnza16, 12, 2},
    {"PUSH BC", &exe_pushbc, 16, 0},
    {"ADD A, 0x%X", &exe_addad8, 8, 1},
    {"RST 00H", &exe_rst00h, 16, 0},
    {"RET Z", &exe_retz, 8, 0},
    {"RET", &exe_ret, 16, 0},
    {"JP Z, 0x%X", &exe_jpza16, 12, 2},
    {"PREFIX", &exe_cbprefix, 4, 0},
    {"CALL Z, 0x%X", &exe_callza16, 12, 2},
    {"CALL 0x%X", &exe_calla16, 24, 2},
    {"ADC A, 0x%X", &exe_adcad8, 8, 1},
    {"RST 08H", &exe_rst08h, 16, 0},
    // 0xd
    {"RET NC", &exe_retnc, 8, 0},
    {"POP DE", &exe_popde, 12, 0},
    {"JP NC, 0x%X", &exe_jpnca16, 12, 2},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"CALL NC, 0x%X", &exe_callnca16, 12, 2},
    {"PUSH DE", &exe_pushde, 16, 0},
    {"SUB 0x%X", &exe_subad8, 8, 1},
    {"RST 10H", &exe_rst10h, 16, 0},
    {"RET C", &exe_retc, 8, 0},
    {"RETI", &exe_reti, 16, 0},
    {"JP C, 0x%X", &exe_jpca16, 12, 2},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"CALL C, 0x%X", &exe_callca16, 12, 2},
    {"NOT A FUNCTION", 0, 0, 0},
    {"SBC A, 0x%X", &exe_sbcad8, 8, 1},
    {"RST 18H", &exe_rst18h, 16, 0},
    // 0xe
    {"LDH (0x%X), A", &exe_ldhpa8a, 12, 1},
    {"POP HL", &exe_pophl, 12, 0},
    {"LD (C), A", &exe_ldpca, 8, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"PUSH HL", &exe_pushhl, 16, 0},
    {"AND A, 0x%X", &exe_andad8, 8, 1},
    {"RST 20H", &exe_rst20h, 16, 0},
    {"ADD SP, 0x%X", &exe_addspr8, 16, 1},
    {"JP HL", &exe_jphl, 4, 0},
    {"LD (0x%X), A", &exe_ldpa16a, 16, 2},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"XOR A, 0x%X", &exe_xorad8, 8, 1},
    {"RST 28H", &exe_rst28h, 16, 0},
    // 0xf
    {"LDH A, (0x%X)", &exe_ldhapa8, 12, 1},
    {"POP AF", &exe_popaf, 12, 0},
    {"LD A, (C)", &exe_ldapc, 8, 0},
    {"DI", &exe_di, 4, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"PUSH AF", &exe_pushaf, 16, 0},
    {"OR A, 0x%X", &exe_orad8, 8, 1},
    {"RST 30H", &exe_rst30h, 16, 0},
    {"LD HL, SP + 0x%X", &exe_ldhlspaddr8, 12, 1},
    {"LD SP, HL", &exe_ldsphl, 8, 0},
    {"LD A, (0x%X)", &exe_ldapa16, 16, 2},
    {"EI", &exe_ei, 4, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"UNKNOWN OPCODE", &unknown_op, 0, 0},
    {"CP A, 0x%X", &exe_cpad8, 8, 1},
    {"RST 38H", &exe_rst38h, 16, 0}
};


void handleUnknownOp(uint8_t opcode) {
    printf("unknown opcode: %X\n", opcode);
}

uint8_t unknown_op() {
    // printf("This is an unknown operation\n");
    return 0;
}


// #######
// # 0x0 #
// #######

uint8_t exe_nop() {
    // registers.pc++;
    // asm("nop"::);
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



// #######
// # 0x1 #
// #######

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
    int8_t offset = (int8_t)readByte(++registers.pc); // we do not need to remove 1 because the offset is added to the address of the next operation
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
    // printf("DEC DE\n");
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


// #######
// # 0x2 #
// #######

// ALEX something is happening in this function were the af register is not updated properly, and I don't know why
uint8_t exe_jrnzr8() {
    if (!GETZFLAG()) {
        // printf("r8: %X\n", (int8_t)readByte(registers.pc + 1));
        registers.pc += (int8_t)readByte(registers.pc + 1) + 1; // we do not need to remove 1 because the offset is added to the address of the next operation
        return 4;
    }
    registers.pc++;

    return 0;
}

uint8_t exe_ldhld16() {
    registers.hl = readWord(++registers.pc);
    return 0;
}

uint8_t exe_ldphlia() {
    writeByte(registers.hl, registers.a);
    registers.hl++;
    return 0;
}

uint8_t exe_inchl() {
    registers.hl++;
    return 0;
}

uint8_t exe_inch() {
    inc8bReg(&registers.h);
    return 0;
}

uint8_t exe_dech() {
    dec8bReg(&registers.h);
    return 0;
}

uint8_t exe_ldhd8() {
    registers.h = readByte(++registers.pc);
    return 0;
}

// https://forums.nesdev.com/viewtopic.php?t=15944
uint8_t exe_daa() {
    if (!GETNFLAG()) {
        if (GETCFLAG() || registers.a > 0x99) { registers.a += 0x60; SETCFLAG(1); }
        if (GETHFlAG() || (registers.a & 0x0f) > 0x09) { registers.a += 0x6; }
    }
    else {
        if (GETCFLAG()) { registers.a -= 0x60; }
        if (GETHFlAG()) { registers.a -= 0x6; }
    }
    SETZFLAG(registers.a == 0);
    SETHFLAG(0);

    return 0;
}

uint8_t exe_jrzr8() {
    if (GETZFLAG()) {
        registers.pc += (int8_t)readByte(registers.pc + 1); // we do not need to remove 1 because the offset is added to the address of the next operation
        return 4; 
    }
    registers.pc++;
    return 0;
}

uint8_t exe_addhlhl() {
    add_hl(registers.hl);

    return 0;
}

uint8_t exe_ldaphli() {
    registers.a = readByte(registers.hl++);

    return 0;
}

uint8_t exe_dechl() {
    registers.hl--;
    return 0;
}

uint8_t exe_incl() {
    inc8bReg(&registers.l);
    return 0;
}

uint8_t exe_decl() {
    dec8bReg(&registers.l);
    return 0;
}

uint8_t exe_ldld8() {
    registers.l = readByte(++registers.pc);
    return 0;
}

uint8_t exe_cpl() {
    registers.a = ~registers.a;
    return 0;
}

// #######
// # 0x3 #
// #######

uint8_t exe_jrncr8() {
    if (!GETCFLAG()) {
        registers.pc += (int8_t)readByte(registers.pc+1) + 1;; // we do not need to remove 1 because the offset is added to the address of the next operation
        return 4; 
    }
    registers.pc++;
    return 0;
}

uint8_t exe_ldspd16() {
    registers.sp = readWord(++registers.pc);
    return 0;
}

uint8_t exe_ldphlda() {
    writeByte(registers.hl--, registers.a);
    return 0;
}

uint8_t exe_incsp() {
    registers.sp++;
    return 0;
}

uint8_t exe_incphl() {
    uint8_t val = readByte(registers.hl);
    val++;
    writeByte(registers.hl, val);
    return 0;
}

uint8_t exe_decphl() {
    uint8_t val = readByte(registers.hl);
    val--;
    writeByte(registers.hl, val);
    return 0;
}

uint8_t exe_ldphld8() {
    writeByte(registers.hl, readByte(++registers.pc));
    return 0;
}

uint8_t exe_scf() {
    SETCFLAG(1);
    SETHFLAG(0);
    SETNFLAG(0);
    return 0;
}

uint8_t exe_jrcr8() {
    if (GETCFLAG()) {
        registers.pc += (int8_t)readByte(registers.pc+1) + 1; // we do not need to remove 1 because the offset is added to the address of the next operation
        return 4; 
    }
    registers.pc++;
    return 0;
}

uint8_t exe_addhlsp() {
    add_hl(registers.sp);
    return 0;
}

uint8_t exe_ldaphld() {
    registers.a = readByte(registers.hl--);

    return 0;
}

uint8_t exe_decsp() {
    registers.sp--;
    return 0;
}

uint8_t exe_inca() {
    inc8bReg(&registers.a);
    return 0;
}

uint8_t exe_deca() {
    dec8bReg(&registers.a);
    return 0;
}

uint8_t exe_ldad8() {
    registers.a = readByte(++registers.pc);
    return 0;
}

uint8_t exe_ccf() {
    SETCFLAG(!GETCFLAG());
    SETHFLAG(0);
    SETNFLAG(0);

    return 0;
}

// #######
// # 0x4 #
// #######

uint8_t exe_ldbb() {
    return 0;
}

uint8_t exe_ldbc() {
    registers.b = registers.c;
    return 0;
}

uint8_t exe_ldbd() {
    registers.b = registers.d;
    return 0;
}

uint8_t exe_ldbe() {
    registers.b = registers.e;
    return 0;
}

uint8_t exe_ldbh() {
    registers.b = registers.h;
    return 0;
}

uint8_t exe_ldbl() {
    registers.b = registers.l;
    return 0;
}

uint8_t exe_ldbphl() {
    registers.b = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldba() {
    registers.b = registers.a;
    return 0;
}

uint8_t exe_ldcb() {
    registers.c = registers.b;
    return 0;
}

uint8_t exe_ldcc() {
    return 0;
}

uint8_t exe_ldcd() {
    registers.c = registers.d;
    return 0;
}

uint8_t exe_ldce() {
    registers.c = registers.e;
    return 0;
}

uint8_t exe_ldch() {
    registers.c = registers.h;
    return 0;
}

uint8_t exe_ldcl() {
    registers.c = registers.l;
    return 0;
}

uint8_t exe_ldcphl() {
    registers.c = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldca() {
    registers.c = registers.a;
    return 0;
}


// #######
// # 0x5 #
// #######

uint8_t exe_lddb() {
    registers.d = registers.b;
    return 0;
}

uint8_t exe_lddc() {
    registers.d = registers.c;
    return 0;
}

uint8_t exe_lddd() {
    return 0;
}

uint8_t exe_ldde() {
    registers.d = registers.e;
    return 0;
}

uint8_t exe_lddh() {
    registers.d = registers.h;
    return 0;
}

uint8_t exe_lddl() {
    registers.d = registers.l;
    return 0;
}

uint8_t exe_lddphl() {
    registers.d = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldda() {
    registers.d = registers.a;
    return 0;
}

uint8_t exe_ldeb() {
    registers.e = registers.b;
    return 0;
}

uint8_t exe_ldec() {
    registers.e = registers.c;
    return 0;
}

uint8_t exe_lded() {
    registers.e = registers.d;
    return 0;
}

uint8_t exe_ldee() {
    return 0;
}

uint8_t exe_ldeh() {
    registers.e = registers.h;
    return 0;
}

uint8_t exe_ldel() {
    registers.e = registers.l;
    return 0;
}

uint8_t exe_ldephl() {
    registers.e = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldea() {
    registers.e = registers.a;
    return 0;
}

// #######
// # 0x6 #
// #######

uint8_t exe_ldhb() {
    registers.h = registers.b;
    return 0;
}

uint8_t exe_ldhc() {
    registers.h = registers.c;
    return 0;
}

uint8_t exe_ldhd() {
    registers.h = registers.d;
    return 0;
}

uint8_t exe_ldhe() {
    registers.h = registers.e;
    return 0;
}

uint8_t exe_ldhh() {
    return 0;
}

uint8_t exe_ldhl() {
    registers.h = registers.l;
    return 0;
}

uint8_t exe_ldhphl() {
    registers.h = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldha() {
    registers.h = registers.a;
    return 0;
}

uint8_t exe_ldlb() {
    registers.l = registers.b;
    return 0;
}

uint8_t exe_ldlc() {
    registers.l = registers.c;
    return 0;
}

uint8_t exe_ldld() {
    registers.l = registers.d;
    return 0;
}

uint8_t exe_ldle() {
    registers.l = registers.e;
    return 0;
}

uint8_t exe_ldlh() {
    registers.l = registers.h;
    return 0;
}

uint8_t exe_ldll() {
    return 0;
}

uint8_t exe_ldlphl() {
    registers.l = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldla() {
    registers.l = registers.a;
    return 0;
}


// #######
// # 0x7 #
// #######

uint8_t exe_ldphlb() {
    writeByte(registers.hl, registers.b);
    return 0;
}

uint8_t exe_ldphlc() {
    writeByte(registers.hl, registers.c);
    return 0;
}

uint8_t exe_ldphld() {
    writeByte(registers.hl, registers.d);
    return 0;
}

uint8_t exe_ldphle() {
    writeByte(registers.hl, registers.e);
    return 0;
}

uint8_t exe_ldphlh() {
    writeByte(registers.hl, registers.h);
    return 0;
}

uint8_t exe_ldphll() {
    writeByte(registers.hl, registers.l);
    return 0;
}

uint8_t exe_halt() {
    halted = 1;
    return 0;
}

uint8_t exe_ldphla() {
    writeByte(registers.hl, registers.a);
    return 0;
}

uint8_t exe_ldab() {
    registers.a = registers.b;
    return 0;
}

uint8_t exe_ldac() {
    registers.a = registers.c;
    return 0;
}

uint8_t exe_ldad() {
    registers.a = registers.d;
    return 0;
}

uint8_t exe_ldae() {
    registers.a = registers.e;
    return 0;
}

uint8_t exe_ldah() {
    registers.a = registers.h;
    return 0;
}

uint8_t exe_ldal() {
    registers.a = registers.l;
    return 0;
}

uint8_t exe_ldaphl() {
    registers.a = readByte(registers.hl);
    return 0;
}

uint8_t exe_ldaa() {
    return 0;
}


// #######
// # 0x8 #
// #######

uint8_t exe_addab() {
    add_a(registers.b);
    return 0;
}

uint8_t exe_addac() {
    add_a(registers.c);
    return 0;
}

uint8_t exe_addad() {
    add_a(registers.d);
    return 0;
}

uint8_t exe_addae() {
    add_a(registers.e);
    return 0;
}

uint8_t exe_addah() {
    add_a(registers.h);
    return 0;
}

uint8_t exe_addal() {
    add_a(registers.l);
    return 0;
}

uint8_t exe_addaphl() {
    add_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_addaa() {
    add_a(registers.a);
    return 0;
}

uint8_t exe_adcab() {
    adc_a(registers.b);
    return 0;
}

uint8_t exe_adcac() {
    adc_a(registers.c);
    return 0;
}

uint8_t exe_adcad() {
    adc_a(registers.d);
    return 0;
}

uint8_t exe_adcae() {
    adc_a(registers.e);
    return 0;
}

uint8_t exe_adcah() {
    adc_a(registers.h);
    return 0;
}

uint8_t exe_adcal() {
    adc_a(registers.l);
    return 0;
}

uint8_t exe_adcaphl() {
    adc_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_adcaa() {
    adc_a(registers.a);
    return 0;
}


// #######
// # 0x9 #
// #######

uint8_t exe_subab() {
    sub_a(registers.b);
    return 0;
}

uint8_t exe_subac() {
    sub_a(registers.c);
    return 0;
}

uint8_t exe_subad() {
    sub_a(registers.d);
    return 0;
}

uint8_t exe_subae() {
    sub_a(registers.e);
    return 0;
}

uint8_t exe_subah() {
    sub_a(registers.h);
    return 0;
}

uint8_t exe_subal() {
    sub_a(registers.l);
    return 0;
}

uint8_t exe_subaphl() {
    sub_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_subaa() {
    sub_a(registers.a);
    return 0;
}

uint8_t exe_sbcab() {
    sbc_a(registers.b);
    return 0;
}

uint8_t exe_sbcac() {
    sbc_a(registers.c);
    return 0;
}

uint8_t exe_sbcad() {
    sbc_a(registers.d);
    return 0;
}

uint8_t exe_sbcae() {
    sbc_a(registers.e);
    return 0;
}

uint8_t exe_sbcah() {
    sbc_a(registers.h);
    return 0;
}

uint8_t exe_sbcal() {
    sbc_a(registers.l);
    return 0;
}

uint8_t exe_sbcaphl() {
    sbc_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_sbcaa() {
    sbc_a(registers.a);
    return 0;
}


// #######
// # 0xa #
// #######

uint8_t exe_andab() {
    and_a(registers.b);
    return 0;
}

uint8_t exe_andac() {
    and_a(registers.c);
    return 0;
}

uint8_t exe_andad() {
    and_a(registers.d);
    return 0;
}

uint8_t exe_andae() {
    and_a(registers.e);
    return 0;
}

uint8_t exe_andah() {
    and_a(registers.h);
    return 0;
}

uint8_t exe_andal() {
    and_a(registers.l);
    return 0;
}

uint8_t exe_andaphl() {
    and_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_andaa() {
    and_a(registers.a);
    return 0;
}

uint8_t exe_xorab() {
    xor_a(registers.b);
    return 0;
}

uint8_t exe_xorac() {
    xor_a(registers.c);
    return 0;
}

uint8_t exe_xorad() {
    xor_a(registers.d);
    return 0;
}

uint8_t exe_xorae() {
    xor_a(registers.e);
    return 0;
}

uint8_t exe_xorah() {
    xor_a(registers.h);
    return 0;
}

uint8_t exe_xoral() {
    xor_a(registers.l);
    return 0;
}

uint8_t exe_xoraphl() {
    xor_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_xoraa() {
    xor_a(registers.a);
    return 0;
}


// #######
// # 0xb #
// #######

uint8_t exe_orab() {
    or_a(registers.b);
    return 0;
}

uint8_t exe_orac() {
    or_a(registers.c);
    return 0;
}

uint8_t exe_orad() {
    or_a(registers.d);
    return 0;
}

uint8_t exe_orae() {
    or_a(registers.e);
    return 0;
}

uint8_t exe_orah() {
    or_a(registers.h);
    return 0;
}

uint8_t exe_oral() {
    or_a(registers.l);
    return 0;
}

uint8_t exe_oraphl() {
    or_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_oraa() {
    return 0;
}

uint8_t exe_cpab() {
    cp_a(registers.b);
    return 0;
}

uint8_t exe_cpac() {
    cp_a(registers.c);
    return 0;
}

uint8_t exe_cpad() {
    cp_a(registers.d);
    return 0;
}

uint8_t exe_cpae() {
    cp_a(registers.e);
    return 0;
}

uint8_t exe_cpah() {
    cp_a(registers.h);
    return 0;
}

uint8_t exe_cpal() {
    cp_a(registers.l);
    return 0;
}

uint8_t exe_cpaphl() {
    cp_a(readByte(registers.hl));
    return 0;
}

uint8_t exe_cpaa() {
    cp_a(registers.a);
    return 0;
}


// #######
// # 0xc #
// #######

uint8_t exe_retnz() {
    if (!GETZFLAG()) {
        registers.pc = popWordStack() - 1;
        return 12;
    }
    return 0;
}

uint8_t exe_popbc() {
    registers.bc = popWordStack();
    return 0;
}

uint8_t exe_jpnza16() {
    if (!GETZFLAG()) {
        registers.pc = readWord(registers.pc+1) - 2; // we remove 2 because it will be added at the end of the clock function
        return 4;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_jpa16() {
    registers.pc = readWord(++registers.pc) - 2; // we remove 2 because it will be added at the end of the clock function
    return 0;
}

uint8_t exe_callnza16() {
    if (!GETZFLAG()) {
        uint16_t addr = readWord(registers.pc+1);
        pushWordStack(registers.pc+3);
        registers.pc = addr - 2; // we remove 2 because it will be added at the end of the clock function
        return 12;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_pushbc() {
    pushWordStack(registers.bc);
    return 0;
}

uint8_t exe_addad8() {
    add_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst00h() {
    registers.pc = 0xffff;
    return 0;
}

uint8_t exe_retz() {
    if (GETZFLAG()) {
        registers.pc = popWordStack() - 1;
        return 12;
    }
    return 0;
}

uint8_t exe_ret() {
    uint16_t stack = popWordStack();
    // printf("returning to %X\n", stack-1);
    registers.pc = stack - 1;
    return 0;
}

uint8_t exe_jpza16() {
    if (GETZFLAG()) {
        registers.pc = readWord(registers.pc + 1) - 2; // we remove 2 because it will be added at the end of the clock function
        return 4;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_cbprefix() {
    // IMPLEMENT CB opcodes
    return 0;
}

uint8_t exe_callza16() {
    if (GETZFLAG()) {
        uint16_t addr = readWord(registers.pc+1);
        pushWordStack(registers.pc+3); // In order to skip 
        registers.pc = addr - 2; // we remove 2 because it will be added at the end of the clock function
        return 12;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_calla16() {
    uint16_t addr = readWord(++registers.pc);
    pushWordStack(registers.pc+2); // In order to skip 
    registers.pc = addr - 2; // we remove 2 because it will be added at the end of the clock function
    return 0;
}

uint8_t exe_adcad8() {
    adc_a(readByte(++registers.pc));

    return 0;
}

uint8_t exe_rst08h() {
    registers.pc = 0x08 -1;
    return 0;
}


// #######
// # 0xd #
// #######

uint8_t exe_retnc() {
    if (!GETCFLAG()) {
        registers.pc = popWordStack() - 1;
        return 12;
    }
    return 0;
}

uint8_t exe_popde() {
    registers.de = popWordStack();
    return 0;
}

uint8_t exe_jpnca16() {
    if (!GETCFLAG()) {
        registers.pc = readWord(registers.pc + 1) - 2; // we remove 2 because it will be added at the end of the clock function
        return 4;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_callnca16() {
    if (!GETCFLAG()) {
        uint16_t addr = readWord(registers.pc+1);
        pushWordStack(registers.pc+3); // In order to skip 
        registers.pc = addr - 2; // we remove 2 because it will be added at the end of the clock function
        return 12;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_pushde() {
    pushWordStack(registers.de);
    return 0;
}

uint8_t exe_subad8() {
    sub_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst10h() {
    registers.pc = 0x10 - 1;
    return 0;
}

uint8_t exe_retc() {
    if (GETCFLAG()) {
        registers.pc = popWordStack() - 1;
        return 12;
    }
    return 0;
}

uint8_t exe_reti() {
    registers.pc = popWordStack() - 1;
    IME = 1;
    return 0;
}

uint8_t exe_jpca16() {
    if (GETCFLAG()) {
        registers.pc = readWord(registers.pc + 1) - 2; // we remove 2 because it will be added at the end of the clock function
        return 4;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_callca16() {
    if (GETCFLAG()) {
        uint16_t addr = readWord(registers.pc+1);
        pushWordStack(registers.pc+3); // In order to skip 
        registers.pc = addr - 2; // we remove 2 because it will be added at the end of the clock function
        return 12;
    }
    registers.pc++;
    return 0;
}

uint8_t exe_sbcad8() {
    sbc_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst18h() {
    registers.pc = 0x18 - 1;
    return 0;
}


// #######
// # 0xe #
// #######


uint8_t exe_ldhpa8a() {
    writeByte(0xff00 + (uint16_t)readByte(++registers.pc), registers.a);
    return 0;
}

uint8_t exe_pophl() {
    registers.hl = popWordStack();
    return 0;
}

uint8_t exe_ldpca() {
    writeByte(0xff00 + (uint16_t)GETCFLAG(), registers.a);
    return 0;
}

uint8_t exe_pushhl() {
    pushWordStack(registers.hl);
    return 0;
}

uint8_t exe_andad8() {
    and_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst20h() {
    registers.pc = 0x20 - 1;
    return 0;
}

uint8_t exe_addspr8() {
    add_sp((int8_t)readByte(++registers.pc));
    return 0;
}

uint8_t exe_jphl() {
    registers.pc = registers.hl - 1; // We remove 1 because it will be added at the end of the clock function
    return 0;
}

uint8_t exe_ldpa16a() {
    writeByte(readWord(++registers.pc), registers.a);
    return 0;
}

uint8_t exe_xorad8() {
    xor_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst28h() {
    registers.pc = 0x28 - 1;
}


// #######
// # 0xf #
// #######

uint8_t exe_ldhapa8() {
    // printf(" addr ldhapa8 %X, %X ", (uint16_t)readByte(registers.pc+1), readByte(0xff00 + (uint16_t)readByte(registers.pc+1)));
    registers.a = readByte(0xff00 + (uint16_t)readByte(++registers.pc));
    return 0;
}

uint8_t exe_popaf() {
    registers.af = popWordStack();
    return 0;
}

uint8_t exe_ldapc() {
    registers.a = readByte(0xff00 + (uint16_t)GETCFLAG());
    return 0;
}

uint8_t exe_di() {
    IME = 0;
    return 0;
}

uint8_t exe_pushaf() {
    pushWordStack(registers.af);
    return 0;
}

uint8_t exe_orad8() {
    or_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst30h() {
    registers.pc = 0x30 - 1;
    return 0;
}

uint8_t exe_ldhlspaddr8() {
    uint16_t temp = registers.sp;
    add_sp(readByte(++registers.pc));
    registers.hl = registers.sp;
    registers.sp = temp;
    return 0;
}

uint8_t exe_ldsphl() {
    registers.sp = registers.hl;
    return 0;
}

uint8_t exe_ldapa16() {
    registers.a = readByte(readWord(++registers.pc));
    return 0;
}

uint8_t exe_ei() {
    IME = 1;
    return 0;
}

uint8_t exe_cpad8() {
    cp_a(readByte(++registers.pc));
    return 0;
}

uint8_t exe_rst38h() {
    registers.pc = 0x38 - 1;
    return 0;
}