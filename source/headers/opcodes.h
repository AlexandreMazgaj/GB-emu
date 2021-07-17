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
uint8_t exe_nop();          // OK

uint8_t exe_ldbcd16();      // OK

uint8_t exe_ldpbca();       // OK

uint8_t exe_incbc();        // OK

uint8_t exe_incb();         // OK

uint8_t exe_decb();         // OK

uint8_t exe_ldbd8();        // OK

uint8_t exe_rlca();         // OK

uint8_t exe_ldpa16sp();     // OK

uint8_t exe_addhlbc();      // OK

uint8_t exe_ldapbc();       // OK

uint8_t exe_decbc();        // OK

uint8_t exe_incc();         // OK

uint8_t exe_decc();         // OK

uint8_t exe_ldcd8();        // OK

uint8_t exe_rrca();         // OK


// 0x1
uint8_t exe_stop();         // OK

uint8_t exe_ldded16();      // OK

uint8_t exe_ldpdea();       // OK

uint8_t exe_incde();        // OK

uint8_t exe_incd();         // OK

uint8_t exe_decd();         // OK

uint8_t exe_lddd8();        // OK

uint8_t exe_rla();          // OK

uint8_t exe_jri8();         // OK

uint8_t exe_addhlde();      // OK

uint8_t exe_ldapde();       // OK

uint8_t exe_decde();        // OK

uint8_t exe_ince();         // OK

uint8_t exe_dece();         // OK

uint8_t exe_lded8();        // OK

uint8_t exe_rra();          // OK


// 0x2
uint8_t exe_jrnzr8();       // OK

uint8_t exe_ldhld16();      // OK

uint8_t exe_ldphlia();      // OK

uint8_t exe_inchl();        // OK

uint8_t exe_inch();         // OK  

uint8_t exe_dech();         // OK

uint8_t exe_ldhd8();        // OK

uint8_t exe_daa();          // TO SEE

uint8_t exe_jrzr8();        // OK

uint8_t exe_addhlhl();      // OK

uint8_t exe_ldaphli();      // OK

uint8_t exe_dechl();        // OK

uint8_t exe_incl();         // OK

uint8_t exe_decl();         // OK

uint8_t exe_ldld8();        // OK

uint8_t exe_cpl();          // OK


// 0x3
uint8_t exe_jrncr8();       // OK

uint8_t exe_ldspd16();      // OK

uint8_t exe_ldphlda();      // OK

uint8_t exe_incsp();        // OK

uint8_t exe_incphl();       // OK

uint8_t exe_decphl();       // OK

uint8_t exe_ldphld8();      // OK

uint8_t exe_scf();          // OK

uint8_t exe_jrcr8();        // OK

uint8_t exe_addhlsp();      // OK

uint8_t exe_ldaphld();      // OK

uint8_t exe_decsp();        // OK

uint8_t exe_inca();         // OK

uint8_t exe_deca();         // OK

uint8_t exe_ldad8();        // OK

uint8_t exe_ccf();          // OK


// 0x4
uint8_t exe_ldbb();         // OK

uint8_t exe_ldbc();         // OK

uint8_t exe_ldbd();         // OK

uint8_t exe_ldbe();         // OK

uint8_t exe_ldbh();         // OK

uint8_t exe_ldbl();         // OK

uint8_t exe_ldbphl();       // OK

uint8_t exe_ldba();         // OK

uint8_t exe_ldcb();         // OK

uint8_t exe_ldcc();         // OK

uint8_t exe_ldcd();         // OK

uint8_t exe_ldce();         // OK

uint8_t exe_ldch();         // OK

uint8_t exe_ldcl();         // OK

uint8_t exe_ldcphl();       // OK

uint8_t exe_ldca();         // OK


// 0x5
uint8_t exe_lddb();         // OK

uint8_t exe_lddc();         // OK

uint8_t exe_lddd();         // OK

uint8_t exe_ldde();         // OK

uint8_t exe_lddh();         // OK

uint8_t exe_lddl();         // OK

uint8_t exe_lddphl();       // OK

uint8_t exe_ldda();         // OK

uint8_t exe_ldeb();         // OK

uint8_t exe_ldec();         // OK

uint8_t exe_lded();         // OK

uint8_t exe_ldee();         // OK

uint8_t exe_ldeh();         // OK   

uint8_t exe_ldel();         // OK

uint8_t exe_ldephl();       // OK

uint8_t exe_ldea();         // OK


// 0x6
uint8_t exe_ldhb();         // OK

uint8_t exe_ldhc();         // OK

uint8_t exe_ldhd();         // OK

uint8_t exe_ldhe();         // OK

uint8_t exe_ldhh();         // OK

uint8_t exe_ldhl();         // OK

uint8_t exe_ldhphl();       // OK

uint8_t exe_ldha();         // OK

uint8_t exe_ldlb();         // OK

uint8_t exe_ldlc();         // OK

uint8_t exe_ldld();         // OK

uint8_t exe_ldle();         // OK

uint8_t exe_ldlh();         // OK

uint8_t exe_ldll();         // OK

uint8_t exe_ldlphl();       // OK

uint8_t exe_ldla();         // OK


// 0x7
uint8_t exe_ldphlb();       // OK

uint8_t exe_ldphlc();       // OK

uint8_t exe_ldphld();       // OK

uint8_t exe_ldphle();       // OK

uint8_t exe_ldphlh();       // OK

uint8_t exe_ldphll();       // OK

uint8_t exe_halt();         // OK

uint8_t exe_ldphla();       // OK

uint8_t exe_ldab();         // OK

uint8_t exe_ldac();         // OK

uint8_t exe_ldad();         // OK

uint8_t exe_ldae();         // OK

uint8_t exe_ldah();         // OK

uint8_t exe_ldal();         // OK

uint8_t exe_ldaphl();       // OK

uint8_t exe_ldaa();         // OK


// 0x8
uint8_t exe_addab();        // OK

uint8_t exe_addac();        // OK

uint8_t exe_addad();        // OK

uint8_t exe_addae();        // OK

uint8_t exe_addah();        // OK

uint8_t exe_addal();        // OK

uint8_t exe_addaphl();      // OK

uint8_t exe_addaa();        // OK

uint8_t exe_adcab();        // OK

uint8_t exe_adcac();        // OK

uint8_t exe_adcad();        // OK

uint8_t exe_adcae();        // OK

uint8_t exe_adcah();        // OK

uint8_t exe_adcal();        // OK

uint8_t exe_adcaphl();      // OK

uint8_t exe_adcaa();        // OK


// 0x9
uint8_t exe_subab();        // OK

uint8_t exe_subac();        // OK

uint8_t exe_subad();        // OK

uint8_t exe_subae();        // OK

uint8_t exe_subah();        // OK

uint8_t exe_subal();        // OK

uint8_t exe_subaphl();      // OK

uint8_t exe_subaa();        // OK

uint8_t exe_sbcab();        // OK

uint8_t exe_sbcac();        // OK

uint8_t exe_sbcad();        // OK

uint8_t exe_sbcae();        // OK

uint8_t exe_sbcah();        // OK

uint8_t exe_sbcal();        // OK

uint8_t exe_sbcaphl();      // OK

uint8_t exe_sbcaa();        // OK


// 0xa
uint8_t exe_andab();        // OK

uint8_t exe_andac();        // OK

uint8_t exe_andad();        // OK

uint8_t exe_andae();        // OK

uint8_t exe_andah();        // OK

uint8_t exe_andal();        // OK

uint8_t exe_andaphl();      // OK

uint8_t exe_andaa();        // OK

uint8_t exe_xorab();        // OK

uint8_t exe_xorac();        // OK

uint8_t exe_xorad();        // OK

uint8_t exe_xorae();        // OK

uint8_t exe_xorah();        // OK

uint8_t exe_xoral();        // OK

uint8_t exe_xoraphl();      // OK

uint8_t exe_xoraa();        // OK


// 0xb
uint8_t exe_orab();         // OK

uint8_t exe_orac();         // OK

uint8_t exe_orad();         // OK

uint8_t exe_orae();         // OK

uint8_t exe_orah();         // OK

uint8_t exe_oral();         // OK

uint8_t exe_oraphl();       // OK

uint8_t exe_oraa();         // OK

uint8_t exe_cpab();         // OK

uint8_t exe_cpac();         // OK

uint8_t exe_cpad();         // OK

uint8_t exe_cpae();         // OK

uint8_t exe_cpah();         // OK

uint8_t exe_cpal();         // OK

uint8_t exe_cpaphl();       // OK

uint8_t exe_cpaa();         // OK



// 0xc
uint8_t exe_retnz();        // OK

uint8_t exe_popbc();        // OK

uint8_t exe_jpnza16();      // OK

uint8_t exe_jpa16();        // OK

uint8_t exe_callnza16();    // OK

uint8_t exe_pushbc();       // OK

uint8_t exe_addad8();       // OK

uint8_t exe_rst00h();

uint8_t exe_retz();

uint8_t exe_ret();

uint8_t exe_jpza16();

uint8_t exe_cbprefix();

uint8_t exe_callza16();

uint8_t exe_calla16();

uint8_t exe_adcad8();

uint8_t exe_rst08h();


// Oxd
uint8_t exe_retnc();

uint8_t exe_popde();

uint8_t exe_jpnca16();

uint8_t exe_callnca16();

uint8_t exe_pushde();

uint8_t exe_subad8();

uint8_t exe_rst10h();

uint8_t exe_retc();

uint8_t exe_reti();

uint8_t exe_jpca16();

uint8_t exe_callca16();

uint8_t exe_sbcad8();

uint8_t exe_rst18h();