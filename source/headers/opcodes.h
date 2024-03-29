#pragma once

#include "gb_cpu.h"
#include "gb_mmu.h"
#include "constants.h"

#define MAX_KNOWN_OPCODE 0xff

typedef uint8_t (*Operation)(void);

struct instruction {
    char* mnemonic;
    Operation execute;
    uint8_t nb_cycles;
    uint8_t size_operand; // in bytes
} const extern instructions[INSTRUCTIONS_SIZE];

const extern struct instruction cb_instructions[INSTRUCTIONS_SIZE];


// unknown opcode
void handleUnknownOp(uint8_t opcode);
uint8_t unknown_op();

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
uint8_t exe_rst00h();       // OK

uint8_t exe_retz();         // OK
uint8_t exe_ret();          // OK
uint8_t exe_jpza16();       // OK
uint8_t exe_cbprefix();     // TODO
uint8_t exe_callza16();     // OK
uint8_t exe_calla16();      // OK
uint8_t exe_adcad8();       // OK
uint8_t exe_rst08h();       // OK


// Oxd
uint8_t exe_retnc();        // OK
uint8_t exe_popde();        // OK
uint8_t exe_jpnca16();      // OK
uint8_t exe_callnca16();    // OK
uint8_t exe_pushde();       // OK
uint8_t exe_subad8();       // OK
uint8_t exe_rst10h();       // OK
uint8_t exe_retc();         // OK
uint8_t exe_reti();         // OK

uint8_t exe_jpca16();       // OK
uint8_t exe_callca16();     // OK
uint8_t exe_sbcad8();       // OK
uint8_t exe_rst18h();       // OK



// Oxe
uint8_t exe_ldhpa8a();      // OK
uint8_t exe_pophl();        // OK
uint8_t exe_ldpca();        // NOT SURE
uint8_t exe_pushhl();       // OK
uint8_t exe_andad8();       // 
uint8_t exe_rst20h();
uint8_t exe_addspr8();
uint8_t exe_jphl();

uint8_t exe_ldpa16a();
uint8_t exe_xorad8();
uint8_t exe_rst28h();


// 0xf
uint8_t exe_ldhapa8();
uint8_t exe_popaf();
uint8_t exe_ldapc();
uint8_t exe_di();
uint8_t exe_pushaf();
uint8_t exe_orad8();
uint8_t exe_rst30h();

uint8_t exe_ldhlspaddr8();
uint8_t exe_ldsphl();
uint8_t exe_ldapa16();
uint8_t exe_ei();
uint8_t exe_cpad8();
uint8_t exe_rst38h();



/* CP PREFIX OPCODES */
// 0x0
uint8_t exe_cb_rlcb();
uint8_t exe_cb_rlcc();
uint8_t exe_cb_rlcd();
uint8_t exe_cb_rlce();
uint8_t exe_cb_rlch();
uint8_t exe_cb_rlcl();
uint8_t exe_cb_rlcphl();
uint8_t exe_cb_rlca();

uint8_t exe_cb_rrcb();
uint8_t exe_cb_rrcc();
uint8_t exe_cb_rrcd();
uint8_t exe_cb_rrce();
uint8_t exe_cb_rrch();
uint8_t exe_cb_rrcl();
uint8_t exe_cb_rrcphl();
uint8_t exe_cb_rrca();

// 0x1
uint8_t exe_cb_rlb();
uint8_t exe_cb_rlc();
uint8_t exe_cb_rld();
uint8_t exe_cb_rle();
uint8_t exe_cb_rlh();
uint8_t exe_cb_rll();
uint8_t exe_cb_rlphl();
uint8_t exe_cb_rla();

uint8_t exe_cb_rrb();
uint8_t exe_cb_rrc();
uint8_t exe_cb_rrd();
uint8_t exe_cb_rre();
uint8_t exe_cb_rrh();
uint8_t exe_cb_rrl();
uint8_t exe_cb_rrphl();
uint8_t exe_cb_rra();

// 0x2
uint8_t exe_cb_slab();
uint8_t exe_cb_slac();
uint8_t exe_cb_slad();
uint8_t exe_cb_slae();
uint8_t exe_cb_slah();
uint8_t exe_cb_slal();
uint8_t exe_cb_slaphl();
uint8_t exe_cb_slaa();

uint8_t exe_cb_srab();
uint8_t exe_cb_srac();
uint8_t exe_cb_srad();
uint8_t exe_cb_srae();
uint8_t exe_cb_srah();
uint8_t exe_cb_sral();
uint8_t exe_cb_sraphl();
uint8_t exe_cb_sraa();

// 0x3
uint8_t exe_cb_swapb();
uint8_t exe_cb_swapc();
uint8_t exe_cb_swapd();
uint8_t exe_cb_swape();
uint8_t exe_cb_swaph();
uint8_t exe_cb_swapl();
uint8_t exe_cb_swapphl();
uint8_t exe_cb_swapa();

uint8_t exe_cb_srlb();
uint8_t exe_cb_srlc();
uint8_t exe_cb_srld();
uint8_t exe_cb_srle();
uint8_t exe_cb_srlh();
uint8_t exe_cb_srll();
uint8_t exe_cb_srlphl();
uint8_t exe_cb_srla();

// 0x4
uint8_t exe_cb_bit0b();
uint8_t exe_cb_bit0c();
uint8_t exe_cb_bit0d();
uint8_t exe_cb_bit0e();
uint8_t exe_cb_bit0h();
uint8_t exe_cb_bit0l();
uint8_t exe_cb_bit0phl();
uint8_t exe_cb_bit0a();

uint8_t exe_cb_bit1b();
uint8_t exe_cb_bit1c();
uint8_t exe_cb_bit1d();
uint8_t exe_cb_bit1e();
uint8_t exe_cb_bit1h();
uint8_t exe_cb_bit1l();
uint8_t exe_cb_bit1phl();
uint8_t exe_cb_bit1a();

// 0x5
uint8_t exe_cb_bit2b();
uint8_t exe_cb_bit2c();
uint8_t exe_cb_bit2d();
uint8_t exe_cb_bit2e();
uint8_t exe_cb_bit2h();
uint8_t exe_cb_bit2l();
uint8_t exe_cb_bit2phl();
uint8_t exe_cb_bit2a();

uint8_t exe_cb_bit3b();
uint8_t exe_cb_bit3c();
uint8_t exe_cb_bit3d();
uint8_t exe_cb_bit3e();
uint8_t exe_cb_bit3h();
uint8_t exe_cb_bit3l();
uint8_t exe_cb_bit3phl();
uint8_t exe_cb_bit3a();

// 0x6
uint8_t exe_cb_bit4b();
uint8_t exe_cb_bit4c();
uint8_t exe_cb_bit4d();
uint8_t exe_cb_bit4e();
uint8_t exe_cb_bit4h();
uint8_t exe_cb_bit4l();
uint8_t exe_cb_bit4phl();
uint8_t exe_cb_bit4a();

uint8_t exe_cb_bit5b();
uint8_t exe_cb_bit5c();
uint8_t exe_cb_bit5d();
uint8_t exe_cb_bit5e();
uint8_t exe_cb_bit5h();
uint8_t exe_cb_bit5l();
uint8_t exe_cb_bit5phl();
uint8_t exe_cb_bit5a();

// 0x7
uint8_t exe_cb_bit6b();
uint8_t exe_cb_bit6c();
uint8_t exe_cb_bit6d();
uint8_t exe_cb_bit6e();
uint8_t exe_cb_bit6h();
uint8_t exe_cb_bit6l();
uint8_t exe_cb_bit6phl();
uint8_t exe_cb_bit6a();

uint8_t exe_cb_bit7b();
uint8_t exe_cb_bit7c();
uint8_t exe_cb_bit7d();
uint8_t exe_cb_bit7e();
uint8_t exe_cb_bit7h();
uint8_t exe_cb_bit7l();
uint8_t exe_cb_bit7phl();
uint8_t exe_cb_bit7a();

// 0x8
uint8_t exe_cb_res0b();
uint8_t exe_cb_res0c();
uint8_t exe_cb_res0d();
uint8_t exe_cb_res0e();
uint8_t exe_cb_res0h();
uint8_t exe_cb_res0l();
uint8_t exe_cb_res0phl();
uint8_t exe_cb_res0a();

uint8_t exe_cb_res1b();
uint8_t exe_cb_res1c();
uint8_t exe_cb_res1d();
uint8_t exe_cb_res1e();
uint8_t exe_cb_res1h();
uint8_t exe_cb_res1l();
uint8_t exe_cb_res1phl();
uint8_t exe_cb_res1a();

// 0x9
uint8_t exe_cb_res2b();
uint8_t exe_cb_res2c();
uint8_t exe_cb_res2d();
uint8_t exe_cb_res2e();
uint8_t exe_cb_res2h();
uint8_t exe_cb_res2l();
uint8_t exe_cb_res2phl();
uint8_t exe_cb_res2a();

uint8_t exe_cb_res3b();
uint8_t exe_cb_res3c();
uint8_t exe_cb_res3d();
uint8_t exe_cb_res3e();
uint8_t exe_cb_res3h();
uint8_t exe_cb_res3l();
uint8_t exe_cb_res3phl();
uint8_t exe_cb_res3a();

// 0xA
uint8_t exe_cb_res4b();
uint8_t exe_cb_res4c();
uint8_t exe_cb_res4d();
uint8_t exe_cb_res4e();
uint8_t exe_cb_res4h();
uint8_t exe_cb_res4l();
uint8_t exe_cb_res4phl();
uint8_t exe_cb_res4a();

uint8_t exe_cb_res5b();
uint8_t exe_cb_res5c();
uint8_t exe_cb_res5d();
uint8_t exe_cb_res5e();
uint8_t exe_cb_res5h();
uint8_t exe_cb_res5l();
uint8_t exe_cb_res5phl();
uint8_t exe_cb_res5a();

// 0xB
uint8_t exe_cb_res6b();
uint8_t exe_cb_res6c();
uint8_t exe_cb_res6d();
uint8_t exe_cb_res6e();
uint8_t exe_cb_res6h();
uint8_t exe_cb_res6l();
uint8_t exe_cb_res6phl();
uint8_t exe_cb_res6a();

uint8_t exe_cb_res7b();
uint8_t exe_cb_res7c();
uint8_t exe_cb_res7d();
uint8_t exe_cb_res7e();
uint8_t exe_cb_res7h();
uint8_t exe_cb_res7l();
uint8_t exe_cb_res7phl();
uint8_t exe_cb_res7a();

// 0xC
uint8_t exe_cb_set0b();
uint8_t exe_cb_set0c();
uint8_t exe_cb_set0d();
uint8_t exe_cb_set0e();
uint8_t exe_cb_set0h();
uint8_t exe_cb_set0l();
uint8_t exe_cb_set0phl();
uint8_t exe_cb_set0a();

uint8_t exe_cb_set1b();
uint8_t exe_cb_set1c();
uint8_t exe_cb_set1d();
uint8_t exe_cb_set1e();
uint8_t exe_cb_set1h();
uint8_t exe_cb_set1l();
uint8_t exe_cb_set1phl();
uint8_t exe_cb_set1a();

// 0xD
uint8_t exe_cb_set2b();
uint8_t exe_cb_set2c();
uint8_t exe_cb_set2d();
uint8_t exe_cb_set2e();
uint8_t exe_cb_set2h();
uint8_t exe_cb_set2l();
uint8_t exe_cb_set2phl();
uint8_t exe_cb_set2a();

uint8_t exe_cb_set3b();
uint8_t exe_cb_set3c();
uint8_t exe_cb_set3d();
uint8_t exe_cb_set3e();
uint8_t exe_cb_set3h();
uint8_t exe_cb_set3l();
uint8_t exe_cb_set3phl();
uint8_t exe_cb_set3a();

// 0xE
uint8_t exe_cb_set4b();
uint8_t exe_cb_set4c();
uint8_t exe_cb_set4d();
uint8_t exe_cb_set4e();
uint8_t exe_cb_set4h();
uint8_t exe_cb_set4l();
uint8_t exe_cb_set4phl();
uint8_t exe_cb_set4a();

uint8_t exe_cb_set5b();
uint8_t exe_cb_set5c();
uint8_t exe_cb_set5d();
uint8_t exe_cb_set5e();
uint8_t exe_cb_set5h();
uint8_t exe_cb_set5l();
uint8_t exe_cb_set5phl();
uint8_t exe_cb_set5a();

// 0xF
uint8_t exe_cb_set6b();
uint8_t exe_cb_set6c();
uint8_t exe_cb_set6d();
uint8_t exe_cb_set6e();
uint8_t exe_cb_set6h();
uint8_t exe_cb_set6l();
uint8_t exe_cb_set6phl();
uint8_t exe_cb_set6a();

uint8_t exe_cb_set7b();
uint8_t exe_cb_set7c();
uint8_t exe_cb_set7d();
uint8_t exe_cb_set7e();
uint8_t exe_cb_set7h();
uint8_t exe_cb_set7l();
uint8_t exe_cb_set7phl();
uint8_t exe_cb_set7a();