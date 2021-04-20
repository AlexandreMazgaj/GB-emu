#pragma once

#include "gb_cpu.h"
#include "gb_mmu.h"
#include "constants.h"

#define MAX_KNOWN_OPCODE 0x1f

typedef uint8_t (*Operation)(void);

struct instruction {
    char* mnemonic;
    Operation execute;
    uint8_t nb_cycles;
    uint8_t size_operand; // in bytes
} const extern instructions[INSTRUCTIONS_SIZE];


// unknown opcode
void handleUnknownOp(uint8_t opcode);

// 0x0
uint8_t exe_nop();

uint8_t exe_ldbcd16();

uint8_t exe_ldpbca();

uint8_t exe_incbc();

uint8_t exe_incb();

uint8_t exe_decb();

uint8_t exe_ldbd8();

uint8_t exe_rlca();

uint8_t exe_ldpa16sp();

uint8_t exe_addhlbc();

uint8_t exe_ldapbc();

uint8_t exe_decbc();

uint8_t exe_incc();

uint8_t exe_decc();

uint8_t exe_ldcd8();

uint8_t exe_rrca();


// 0x1
uint8_t exe_stop();

uint8_t exe_ldded16();

uint8_t exe_ldpdea();

uint8_t exe_incde();

uint8_t exe_incd();

uint8_t exe_decd();

uint8_t exe_lddd8();

uint8_t exe_rla();

uint8_t exe_jri8();

uint8_t exe_addhlde();

uint8_t exe_ldapde();

uint8_t exe_decde();

uint8_t exe_ince();

uint8_t exe_dece();

uint8_t exe_lded8();

uint8_t exe_rra();


// 0x2