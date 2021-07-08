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
uint8_t exe_jrnzr8();

uint8_t exe_ldhld16();

uint8_t exe_ldphlia();

uint8_t exe_inchl();

uint8_t exe_inch();

uint8_t exe_dech();

uint8_t exe_ldhd8();

uint8_t exe_daa();

uint8_t exe_jrzr8();

uint8_t exe_addhlhl();

uint8_t exe_ldaphli();

uint8_t exe_dechl();

uint8_t exe_incl();

uint8_t exe_decl();

uint8_t exe_ldld8();

uint8_t exe_cpl();


// 0x3
uint8_t exe_jrncr8();

uint8_t exe_ldspd16();

uint8_t exe_ldphlda();

uint8_t exe_incsp();

uint8_t exe_incphl();

uint8_t exe_decphl();

uint8_t exe_ldphld8();

uint8_t exe_scf();

uint8_t exe_jrcr8();

uint8_t exe_addhlsp();

uint8_t exe_ldaphld();

uint8_t exe_decsp();

uint8_t exe_inca();

uint8_t exe_deca();

uint8_t exe_ldad8();

uint8_t exe_ccf();


// 0x4
uint8_t exe_ldbb();

uint8_t exe_ldbc();

uint8_t exe_ldbd();

uint8_t exe_ldbe();

uint8_t exe_ldbh();

uint8_t exe_ldbl();

uint8_t exe_ldbphl();

uint8_t exe_ldba();

uint8_t exe_ldcb();

uint8_t exe_ldcc();

uint8_t exe_ldcd();

uint8_t exe_ldce();

uint8_t exe_ldch();

uint8_t exe_ldcl();

uint8_t exe_ldcphl();

uint8_t exe_ldca();


// 0x5
uint8_t exe_lddb();

uint8_t exe_lddc();

uint8_t exe_lddd();

uint8_t exe_ldde();

uint8_t exe_lddh();

uint8_t exe_lddl();

uint8_t exe_lddphl();

uint8_t exe_ldda();

uint8_t exe_ldeb();

uint8_t exe_ldec();

uint8_t exe_lded();

uint8_t exe_ldee();

uint8_t exe_ldeh();

uint8_t exe_ldel();

uint8_t exe_ldephl();

uint8_t exe_ldea();


// 0x6
uint8_t exe_ldhb();

uint8_t exe_ldhc();

uint8_t exe_ldhd();

uint8_t exe_ldhe();

uint8_t exe_ldhh();

uint8_t exe_ldhl();

uint8_t exe_ldhphl();

uint8_t exe_ldha();

uint8_t exe_ldlb();

uint8_t exe_ldlc();

uint8_t exe_ldld();

uint8_t exe_ldle();

uint8_t exe_ldlh();

uint8_t exe_ldll();

uint8_t exe_ldlphl();

uint8_t exe_ldla();


// 0x7
uint8_t exe_ldphlb();

uint8_t exe_ldphlc();

uint8_t exe_ldphld();

uint8_t exe_ldphle();

uint8_t exe_ldphlh();

uint8_t exe_ldphll();

uint8_t exe_halt();

uint8_t exe_ldphla();

uint8_t exe_ldab();

uint8_t exe_ldac();

uint8_t exe_ldad();

uint8_t exe_ldae();

uint8_t exe_ldah();

uint8_t exe_ldal();

uint8_t exe_ldaphl();

uint8_t exe_ldaa();


// 0x8
uint8_t exe_addab();

uint8_t exe_addac();

uint8_t exe_addad();

uint8_t exe_addae();

uint8_t exe_addah();

uint8_t exe_addal();

uint8_t exe_addaphl();

uint8_t exe_addaa();

uint8_t exe_adcab();

uint8_t exe_adcac();

uint8_t exe_adcad();

uint8_t exe_adcae();

uint8_t exe_adcah();

uint8_t exe_adcal();

uint8_t exe_adcaphl();

uint8_t exe_adcaa();


// 0x9
uint8_t exe_subab();

uint8_t exe_subac();

uint8_t exe_subad();

uint8_t exe_subae();

uint8_t exe_subah();

uint8_t exe_subal();

uint8_t exe_subaphl();

uint8_t exe_subaa();

uint8_t exe_sbcab();

uint8_t exe_sbcac();

uint8_t exe_sbcad();

uint8_t exe_sbcae();

uint8_t exe_sbcah();

uint8_t exe_sbcal();

uint8_t exe_sbcaphl();

uint8_t exe_sbcaa();


// 0xa
uint8_t exe_andab();

uint8_t exe_andac();

uint8_t exe_andad();

uint8_t exe_andae();

uint8_t exe_andah();

uint8_t exe_andal();

uint8_t exe_andaphl();

uint8_t exe_andaa();

uint8_t exe_xorab();

uint8_t exe_xorac();

uint8_t exe_xorad();

uint8_t exe_xorae();

uint8_t exe_xorah();

uint8_t exe_xoral();

uint8_t exe_xoraphl();

uint8_t exe_xoraa();


// 0xb
uint8_t exe_orab();

uint8_t exe_orac();

uint8_t exe_orad();

uint8_t exe_orae();

uint8_t exe_orah();

uint8_t exe_oral();

uint8_t exe_oraphl();

uint8_t exe_oraa();

uint8_t exe_cpab();

uint8_t exe_cpac();

uint8_t exe_cpad();

uint8_t exe_cpae();

uint8_t exe_cpah();

uint8_t exe_cpal();

uint8_t exe_cpaphl();

uint8_t exe_cpaa();
