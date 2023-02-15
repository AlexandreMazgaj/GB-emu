#include "headers/opcodes.h"
#include <stdio.h>

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
    {"JR 0x%X", &exe_jri8, 12, 1},                        // 8
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


const struct instruction cb_instructions[INSTRUCTIONS_SIZE] = {
    // 0x0
    {"RLC B", &exe_cb_rlcb, 8, 0},
    {"RLC C", &exe_cb_rlcc, 8, 0},
    {"RLC D", &exe_cb_rlcd, 8, 0},
    {"RLC E", &exe_cb_rlce, 8, 0},
    {"RLC H", &exe_cb_rlch, 8, 0},
    {"RLC L", &exe_cb_rlcl, 8, 0},
    {"RLC (HL)", &exe_cb_rlcphl, 16, 0},
    {"RLC A", &exe_cb_rlca, 8, 0},
    {"RRC B", &exe_cb_rrcb, 8, 0},
    {"RRC C", &exe_cb_rrcc, 8, 0},
    {"RRC D", &exe_cb_rrcd, 8, 0},
    {"RRC E", &exe_cb_rrce, 8, 0},
    {"RRC H", &exe_cb_rrch, 8, 0},
    {"RRC L", &exe_cb_rrcl, 8, 0},
    {"RRC (HL)", &exe_cb_rrcphl, 16, 0},
    {"RRC A", &exe_cb_rrca, 8, 0},
    // 0x1
    {"RL B", &exe_cb_rlb, 8, 0},
    {"RL C", &exe_cb_rlc, 8, 0},
    {"RL D", &exe_cb_rld, 8, 0},
    {"RL E", &exe_cb_rle, 8, 0},
    {"RL H", &exe_cb_rlh, 8, 0},
    {"RL L", &exe_cb_rll, 8, 0},
    {"RL (HL)", &exe_cb_rlphl, 16, 0},
    {"RL A", &exe_cb_rla, 8, 0},
    {"RR B", &exe_cb_rrb, 8, 0},
    {"RR C", &exe_cb_rrc, 8, 0},
    {"RR D", &exe_cb_rrd, 8, 0},
    {"RR E", &exe_cb_rre, 8, 0},
    {"RR H", &exe_cb_rrh, 8, 0},
    {"RR L", &exe_cb_rrl, 8, 0},
    {"RR (HL)", &exe_cb_rrphl, 16, 0},
    {"RR A", &exe_cb_rra, 8, 0},
    // 0x2
    {"SLA B", &exe_cb_slab, 8, 0},
    {"SLA C", &exe_cb_slac, 8, 0},
    {"SLA D", &exe_cb_slad, 8, 0},
    {"SLA E", &exe_cb_slae, 8, 0},
    {"SLA H", &exe_cb_slah, 8, 0},
    {"SLA L", &exe_cb_slal, 8, 0},
    {"SLA (HL)", &exe_cb_slaphl, 16, 0},
    {"SLA A", &exe_cb_slaa, 8, 0},
    {"SRA B", &exe_cb_srab, 8, 0},
    {"SRA C", &exe_cb_srac, 8, 0},
    {"SRA D", &exe_cb_srad, 8, 0},
    {"SRA E", &exe_cb_srae, 8, 0},
    {"SRA H", &exe_cb_srah, 8, 0},
    {"SRA L", &exe_cb_sral, 8, 0},
    {"SRA (HL)", &exe_cb_sraphl, 16, 0},
    {"SRA A", &exe_cb_sraa, 8, 0},
    // 0x3
    {"SWAP B", &exe_cb_swapb, 8, 0},
    {"SWAP C", &exe_cb_swapc, 8, 0},
    {"SWAP D", &exe_cb_swapd, 8, 0},
    {"SWAP E", &exe_cb_swape, 8, 0},
    {"SWAP H", &exe_cb_swaph, 8, 0},
    {"SWAP L", &exe_cb_swapl, 8, 0},
    {"SWAP (HL)", &exe_cb_swapphl, 16, 0},
    {"SWAP A", &exe_cb_swapa, 8, 0},
    {"SRL B", &exe_cb_srlb, 8, 0},
    {"SRL C", &exe_cb_srlc, 8, 0},
    {"SRL D", &exe_cb_srld, 8, 0},
    {"SRL E", &exe_cb_srle, 8, 0},
    {"SRL H", &exe_cb_srlh, 8, 0},
    {"SRL L", &exe_cb_srll, 8, 0},
    {"SRL (HL)", &exe_cb_srlphl, 16, 0},
    {"SRL A", &exe_cb_srla, 8, 0},
    // 0x4
    {"BIT0 B", &exe_cb_bit0b, 8, 0},
    {"BIT0 C", &exe_cb_bit0c, 8, 0},
    {"BIT0 D", &exe_cb_bit0d, 8, 0},
    {"BIT0 E", &exe_cb_bit0e, 8, 0},
    {"BIT0 H", &exe_cb_bit0h, 8, 0},
    {"BIT0 L", &exe_cb_bit0l, 8, 0},
    {"BIT0 (HL)", &exe_cb_bit0phl, 12, 0},
    {"BIT0 A", &exe_cb_bit0a, 8, 0},
    {"BIT1 B", &exe_cb_bit1b, 8, 0},
    {"BIT1 C", &exe_cb_bit1c, 8, 0},
    {"BIT1 D", &exe_cb_bit1d, 8, 0},
    {"BIT1 E", &exe_cb_bit1e, 8, 0},
    {"BIT1 H", &exe_cb_bit1h, 8, 0},
    {"BIT1 L", &exe_cb_bit1l, 8, 0},
    {"BIT1 (HL)", &exe_cb_bit1phl, 12, 0},
    {"BIT1 A", &exe_cb_bit1a, 8, 0},
    // 0x5
    {"BIT2 B", &exe_cb_bit2b, 8, 0},
    {"BIT2 C", &exe_cb_bit2c, 8, 0},
    {"BIT2 D", &exe_cb_bit2d, 8, 0},
    {"BIT2 E", &exe_cb_bit2e, 8, 0},
    {"BIT2 H", &exe_cb_bit2h, 8, 0},
    {"BIT2 L", &exe_cb_bit2l, 8, 0},
    {"BIT2 (HL)", &exe_cb_bit2phl, 12, 0},
    {"BIT2 A", &exe_cb_bit2a, 8, 0},
    {"BIT3 B", &exe_cb_bit3b, 8, 0},
    {"BIT3 C", &exe_cb_bit3c, 8, 0},
    {"BIT3 D", &exe_cb_bit3d, 8, 0},
    {"BIT3 E", &exe_cb_bit3e, 8, 0},
    {"BIT3 H", &exe_cb_bit3h, 8, 0},
    {"BIT3 L", &exe_cb_bit3l, 8, 0},
    {"BIT3 (HL)", &exe_cb_bit3phl, 12, 0},
    {"BIT3 A", &exe_cb_bit3a, 8, 0},
    // 0x6
    {"BIT4 B", &exe_cb_bit4b, 8, 0},
    {"BIT4 C", &exe_cb_bit4c, 8, 0},
    {"BIT4 D", &exe_cb_bit4d, 8, 0},
    {"BIT4 E", &exe_cb_bit4e, 8, 0},
    {"BIT4 H", &exe_cb_bit4h, 8, 0},
    {"BIT4 L", &exe_cb_bit4l, 8, 0},
    {"BIT4 (HL)", &exe_cb_bit4phl, 12, 0},
    {"BIT4 A", &exe_cb_bit4a, 8, 0},
    {"BIT5 B", &exe_cb_bit5b, 8, 0},
    {"BIT5 C", &exe_cb_bit5c, 8, 0},
    {"BIT5 D", &exe_cb_bit5d, 8, 0},
    {"BIT5 E", &exe_cb_bit5e, 8, 0},
    {"BIT5 H", &exe_cb_bit5h, 8, 0},
    {"BIT5 L", &exe_cb_bit5l, 8, 0},
    {"BIT5 (HL)", &exe_cb_bit5phl, 12, 0},
    {"BIT5 A", &exe_cb_bit5a, 8, 0},
    // 0x7
    {"BIT6 B", &exe_cb_bit6b, 8, 0},
    {"BIT6 C", &exe_cb_bit6c, 8, 0},
    {"BIT6 D", &exe_cb_bit6d, 8, 0},
    {"BIT6 E", &exe_cb_bit6e, 8, 0},
    {"BIT6 H", &exe_cb_bit6h, 8, 0},
    {"BIT6 L", &exe_cb_bit6l, 8, 0},
    {"BIT6 (HL)", &exe_cb_bit6phl, 12, 0},
    {"BIT6 A", &exe_cb_bit6a, 8, 0},
    {"BIT7 B", &exe_cb_bit7b, 8, 0},
    {"BIT7 C", &exe_cb_bit7c, 8, 0},
    {"BIT7 D", &exe_cb_bit7d, 8, 0},
    {"BIT7 E", &exe_cb_bit7e, 8, 0},
    {"BIT7 H", &exe_cb_bit7h, 8, 0},
    {"BIT7 L", &exe_cb_bit7l, 8, 0},
    {"BIT7 (HL)", &exe_cb_bit7phl, 12, 0},
    {"BIT7 A", &exe_cb_bit7a, 8, 0},
    // 0x8
    {"RES0 B", &exe_cb_res0b, 8, 0},
    {"RES0 C", &exe_cb_res0c, 8, 0},
    {"RES0 D", &exe_cb_res0d, 8, 0},
    {"RES0 E", &exe_cb_res0e, 8, 0},
    {"RES0 H", &exe_cb_res0h, 8, 0},
    {"RES0 L", &exe_cb_res0l, 8, 0},
    {"RES0 (HL)", &exe_cb_res0phl, 16, 0},
    {"RES0 A", &exe_cb_res0a, 8, 0},
    {"RES1 B", &exe_cb_res1b, 8, 0},
    {"RES1 C", &exe_cb_res1c, 8, 0},
    {"RES1 D", &exe_cb_res1d, 8, 0},
    {"RES1 E", &exe_cb_res1e, 8, 0},
    {"RES1 H", &exe_cb_res1h, 8, 0},
    {"RES1 L", &exe_cb_res1l, 8, 0},
    {"RES1 (HL)", &exe_cb_res1phl, 16, 0},
    {"RES1 A", &exe_cb_res1a, 8, 0},
    // 0x9
    {"RES2 B", &exe_cb_res2b, 8, 0},
    {"RES2 C", &exe_cb_res2c, 8, 0},
    {"RES2 D", &exe_cb_res2d, 8, 0},
    {"RES2 E", &exe_cb_res2e, 8, 0},
    {"RES2 H", &exe_cb_res2h, 8, 0},
    {"RES2 L", &exe_cb_res2l, 8, 0},
    {"RES2 (HL)", &exe_cb_res2phl, 16, 0},
    {"RES2 A", &exe_cb_res2a, 8, 0},
    {"RES3 B", &exe_cb_res3b, 8, 0},
    {"RES3 C", &exe_cb_res3c, 8, 0},
    {"RES3 D", &exe_cb_res3d, 8, 0},
    {"RES3 E", &exe_cb_res3e, 8, 0},
    {"RES3 H", &exe_cb_res3h, 8, 0},
    {"RES3 L", &exe_cb_res3l, 8, 0},
    {"RES3 (HL)", &exe_cb_res3phl, 16, 0},
    {"RES3 A", &exe_cb_res3a, 8, 0},
    // 0xA
    {"RES4 B", &exe_cb_res4b, 8, 0},
    {"RES4 C", &exe_cb_res4c, 8, 0},
    {"RES4 D", &exe_cb_res4d, 8, 0},
    {"RES4 E", &exe_cb_res4e, 8, 0},
    {"RES4 H", &exe_cb_res4h, 8, 0},
    {"RES4 L", &exe_cb_res4l, 8, 0},
    {"RES4 (HL)", &exe_cb_res4phl, 16, 0},
    {"RES4 A", &exe_cb_res4a, 8, 0},
    {"RES5 B", &exe_cb_res5b, 8, 0},
    {"RES5 C", &exe_cb_res5c, 8, 0},
    {"RES5 D", &exe_cb_res5d, 8, 0},
    {"RES5 E", &exe_cb_res5e, 8, 0},
    {"RES5 H", &exe_cb_res5h, 8, 0},
    {"RES5 L", &exe_cb_res5l, 8, 0},
    {"RES5 (HL)", &exe_cb_res5phl, 16, 0},
    {"RES5 A", &exe_cb_res5a, 8, 0},
    // 0xB
    {"RES6 B", &exe_cb_res6b, 8, 0},
    {"RES6 C", &exe_cb_res6c, 8, 0},
    {"RES6 D", &exe_cb_res6d, 8, 0},
    {"RES6 E", &exe_cb_res6e, 8, 0},
    {"RES6 H", &exe_cb_res6h, 8, 0},
    {"RES6 L", &exe_cb_res6l, 8, 0},
    {"RES6 (HL)", &exe_cb_res6phl, 16, 0},
    {"RES6 A", &exe_cb_res6a, 8, 0},
    {"RES7 B", &exe_cb_res7b, 8, 0},
    {"RES7 C", &exe_cb_res7c, 8, 0},
    {"RES7 D", &exe_cb_res7d, 8, 0},
    {"RES7 E", &exe_cb_res7e, 8, 0},
    {"RES7 H", &exe_cb_res7h, 8, 0},
    {"RES7 L", &exe_cb_res7l, 8, 0},
    {"RES7 (HL)", &exe_cb_res7phl, 16, 0},
    {"RES7 A", &exe_cb_res7a, 8, 0},
    // 0xC
    {"SET0 B", &exe_cb_set0b, 8, 0},
    {"SET0 C", &exe_cb_set0c, 8, 0},
    {"SET0 D", &exe_cb_set0d, 8, 0},
    {"SET0 E", &exe_cb_set0e, 8, 0},
    {"SET0 H", &exe_cb_set0h, 8, 0},
    {"SET0 L", &exe_cb_set0l, 8, 0},
    {"SET0 (HL)", &exe_cb_set0phl, 16, 0},
    {"SET0 A", &exe_cb_set0a, 8, 0},
    {"SET1 B", &exe_cb_set1b, 8, 0},
    {"SET1 C", &exe_cb_set1c, 8, 0},
    {"SET1 D", &exe_cb_set1d, 8, 0},
    {"SET1 E", &exe_cb_set1e, 8, 0},
    {"SET1 H", &exe_cb_set1h, 8, 0},
    {"SET1 L", &exe_cb_set1l, 8, 0},
    {"SET1 (HL)", &exe_cb_set1phl, 16, 0},
    {"SET1 A", &exe_cb_set1a, 8, 0},
    // 0xD
    {"SET2 B", &exe_cb_set2b, 8, 0},
    {"SET2 C", &exe_cb_set2c, 8, 0},
    {"SET2 D", &exe_cb_set2d, 8, 0},
    {"SET2 E", &exe_cb_set2e, 8, 0},
    {"SET2 H", &exe_cb_set2h, 8, 0},
    {"SET2 L", &exe_cb_set2l, 8, 0},
    {"SET2 (HL)", &exe_cb_set2phl, 16, 0},
    {"SET2 A", &exe_cb_set2a, 8, 0},
    {"SET3 B", &exe_cb_set3b, 8, 0},
    {"SET3 C", &exe_cb_set3c, 8, 0},
    {"SET3 D", &exe_cb_set3d, 8, 0},
    {"SET3 E", &exe_cb_set3e, 8, 0},
    {"SET3 H", &exe_cb_set3h, 8, 0},
    {"SET3 L", &exe_cb_set3l, 8, 0},
    {"SET3 (HL)", &exe_cb_set3phl, 16, 0},
    {"SET3 A", &exe_cb_set3a, 8, 0},
    // 0xE
    {"SET4 B", &exe_cb_set4b, 8, 0},
    {"SET4 C", &exe_cb_set4c, 8, 0},
    {"SET4 D", &exe_cb_set4d, 8, 0},
    {"SET4 E", &exe_cb_set4e, 8, 0},
    {"SET4 H", &exe_cb_set4h, 8, 0},
    {"SET4 L", &exe_cb_set4l, 8, 0},
    {"SET4 (HL)", &exe_cb_set4phl, 16, 0},
    {"SET4 A", &exe_cb_set4a, 8, 0},
    {"SET5 B", &exe_cb_set5b, 8, 0},
    {"SET5 C", &exe_cb_set5c, 8, 0},
    {"SET5 D", &exe_cb_set5d, 8, 0},
    {"SET5 E", &exe_cb_set5e, 8, 0},
    {"SET5 H", &exe_cb_set5h, 8, 0},
    {"SET5 L", &exe_cb_set5l, 8, 0},
    {"SET5 (HL)", &exe_cb_set5phl, 16, 0},
    {"SET5 A", &exe_cb_set5a, 8, 0},
    // 0xF
    {"SET6 B", &exe_cb_set6b, 8, 0},
    {"SET6 C", &exe_cb_set6c, 8, 0},
    {"SET6 D", &exe_cb_set6d, 8, 0},
    {"SET6 E", &exe_cb_set6e, 8, 0},
    {"SET6 H", &exe_cb_set6h, 8, 0},
    {"SET6 L", &exe_cb_set6l, 8, 0},
    {"SET6 (HL)", &exe_cb_set6phl, 16, 0},
    {"SET6 A", &exe_cb_set6a, 8, 0},
    {"SET7 B", &exe_cb_set7b, 8, 0},
    {"SET7 C", &exe_cb_set7c, 8, 0},
    {"SET7 D", &exe_cb_set7d, 8, 0},
    {"SET7 E", &exe_cb_set7e, 8, 0},
    {"SET7 H", &exe_cb_set7h, 8, 0},
    {"SET7 L", &exe_cb_set7l, 8, 0},
    {"SET7 (HL)", &exe_cb_set7phl, 16, 0},
    {"SET7 A", &exe_cb_set7a, 8, 0}
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
    SETZFLAG(0);
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
    SETZFLAG(0);
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
    SETZFLAG(0);
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
    SETZFLAG(0);
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
        if (GETHFLAG() || ((registers.a & 0x0f) > 0x09)) { registers.a += 0x6; }
    }
    else {
        if (GETCFLAG()) { registers.a -= 0x60; SETCFLAG(1); }
        if (GETHFLAG()) { registers.a -= 0x6; }
    }
    SETZFLAG(registers.a == 0);
    SETHFLAG(0);

    // SETCFLAG(registers.a >= 0x100);


    // uint8_t a = registers.a;
    // uint8_t adjust;
    // if (GETCFLAG())
    //     adjust = 0x60;
    // else
    //     adjust = 0;

    // if (GETHFLAG()) adjust |= 0x06;

    // if (!GETNFLAG()) {
    //     if (a & 0x0f > 0x09) adjust |= 0x06;
    //     if (a > 0x99) adjust |= 0x60;
    //     a += adjust;
    // }
    // else {
    //     a -= adjust;
    // }

    // SETCFLAG(adjust >= 0x60);
    // SETHFLAG(0);
    // SETZFLAG(a == 0);

    // registers.a = a;


    return 0;
}

uint8_t exe_jrzr8() {
    if (GETZFLAG()) {
        registers.pc += (int8_t)readByte(registers.pc + 1) + 1; // we do not need to remove 1 because the offset is added to the address of the next operation
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
    // printf("register a: %X, register hl: %X\n",registers.a, registers.hl);
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
    or_a(registers.a);
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
    return 0;
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
    registers.af = registers.af & 0xfff0; // only the upper bits (7 5 6 4) are relevant for register f, the rest is discarded
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




/* CP PREFIX OPCODES*/

// 0x0
uint8_t exe_cb_rlcb() {
    rotateLeft(&registers.b);
    return 0;
}

uint8_t exe_cb_rlcc() {
    rotateLeft(&registers.c);
    return 0;
}

uint8_t exe_cb_rlcd() {
    rotateLeft(&registers.d);
    return 0;
}

uint8_t exe_cb_rlce() {
    rotateLeft(&registers.e);
    return 0;
}

uint8_t exe_cb_rlch() {
    rotateLeft(&registers.h);
    return 0;
}

uint8_t exe_cb_rlcl() {
    rotateLeft(&registers.l);
    return 0;
}

uint8_t exe_cb_rlcphl() {
    uint8_t temp = readByte(registers.hl);
    rotateLeft(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_rlca() {
    rotateLeft(&registers.a);
    return 0;
}

uint8_t exe_cb_rrcb() {
    rotateRight(&registers.b);
    return 0;
}

uint8_t exe_cb_rrcc() {
    rotateRight(&registers.c);
    return 0;
}

uint8_t exe_cb_rrcd() {
    rotateRight(&registers.d);
    return 0;
}

uint8_t exe_cb_rrce() {
    rotateRight(&registers.e);
    return 0;
}

uint8_t exe_cb_rrch() {
    rotateRight(&registers.h);
    return 0;
}

uint8_t exe_cb_rrcl() {
    rotateRight(&registers.l);
    return 0;
}

uint8_t exe_cb_rrcphl() {
    uint8_t temp = readByte(registers.hl);
    rotateRight(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_rrca() {
    rotateRight(&registers.a);
    return 0;
}


// 0x1
uint8_t exe_cb_rlb() {
    rotateLeftCarry(&registers.b);
    return 0;
}

uint8_t exe_cb_rlc() {
    rotateLeftCarry(&registers.c);
    return 0;
}

uint8_t exe_cb_rld() {
    rotateLeftCarry(&registers.d);
    return 0;
}

uint8_t exe_cb_rle() {
    rotateLeftCarry(&registers.e);
    return 0;
}
uint8_t exe_cb_rlh() {
    rotateLeftCarry(&registers.h);
    return 0;
}

uint8_t exe_cb_rll() {
    rotateLeftCarry(&registers.l);
    return 0;
}

uint8_t exe_cb_rlphl() {
    uint8_t temp = readByte(registers.hl);
    rotateLeftCarry(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_rla() {
    rotateLeftCarry(&registers.a);
    return 0;
}

uint8_t exe_cb_rrb() {
    rotateRightCarry(&registers.b);
    return 0;
}

uint8_t exe_cb_rrc() {
    rotateRightCarry(&registers.c);
    return 0;
}

uint8_t exe_cb_rrd() {
    rotateRightCarry(&registers.d);
    return 0;
}

uint8_t exe_cb_rre() {
    rotateRightCarry(&registers.e);
    return 0;
}

uint8_t exe_cb_rrh() {
    rotateRightCarry(&registers.h);
    return 0;
}

uint8_t exe_cb_rrl() {
    rotateRightCarry(&registers.l);
    return 0;
}

uint8_t exe_cb_rrphl() {
    uint8_t temp = readByte(registers.hl);
    rotateRightCarry(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_rra() {
    rotateRightCarry(&registers.a);
    return 0;
}


// 0x2
uint8_t exe_cb_slab() {
    shiftLeft(&registers.b);
    return 0;
}

uint8_t exe_cb_slac() {
    shiftLeft(&registers.c);
    return 0;
}

uint8_t exe_cb_slad() {
    shiftLeft(&registers.d);
    return 0;
}

uint8_t exe_cb_slae() {
    shiftLeft(&registers.e);
    return 0;
}

uint8_t exe_cb_slah() {
    shiftLeft(&registers.h);
    return 0;
}

uint8_t exe_cb_slal() {
    shiftLeft(&registers.l);
    return 0;
}

uint8_t exe_cb_slaphl() {
    uint8_t temp = readByte(registers.hl);
    shiftLeft(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_slaa() {
    shiftLeft(&registers.a);
    return 0;
}

uint8_t exe_cb_srab() {
    shiftRightMSB(&registers.b);
    return 0;
}

uint8_t exe_cb_srac() {
    shiftRightMSB(&registers.c);
    return 0;
}

uint8_t exe_cb_srad() {
    shiftRightMSB(&registers.d);
    return 0;
}

uint8_t exe_cb_srae() {
    shiftRightMSB(&registers.e);
    return 0;
}

uint8_t exe_cb_srah() {
    shiftRightMSB(&registers.h);
    return 0;
}

uint8_t exe_cb_sral() {
    shiftRightMSB(&registers.l);
    return 0;
}

uint8_t exe_cb_sraphl() {
    uint8_t temp = readByte(registers.hl);
    shiftRightMSB(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_sraa() {
    shiftRightMSB(&registers.l);
    return 0;
}


// 0x3
uint8_t exe_cb_swapb() {
    swap(&registers.b);
    return 0;
}

uint8_t exe_cb_swapc() {
    swap(&registers.c);
    return 0;
}

uint8_t exe_cb_swapd() {
    swap(&registers.d);
    return 0;
}

uint8_t exe_cb_swape() {
    swap(&registers.e);
    return 0;
}

uint8_t exe_cb_swaph() {
    swap(&registers.h);
    return 0;
}

uint8_t exe_cb_swapl() {
    swap(&registers.l);
    return 0;
}

uint8_t exe_cb_swapphl() {
    uint8_t temp = readByte(registers.hl);
    swap(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_swapa() {
    swap(&registers.a);
    return 0;
}

uint8_t exe_cb_srlb() {
    shiftRight(&registers.b);
    return 0;
}

uint8_t exe_cb_srlc() {
    shiftRight(&registers.c);
    return 0;
}

uint8_t exe_cb_srld() {
    shiftRight(&registers.d);
    return 0;
}

uint8_t exe_cb_srle() {
    shiftRight(&registers.e);
    return 0;
}

uint8_t exe_cb_srlh() {
    shiftRight(&registers.h);
    return 0;
}

uint8_t exe_cb_srll() {
    shiftRight(&registers.l);
    return 0;
}

uint8_t exe_cb_srlphl() {
    uint8_t temp = readByte(registers.hl);
    shiftRight(&temp);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_srla() {
    shiftRight(&registers.a);
    return 0;
}


// 0x4

uint8_t exe_cb_bit0b() {
    checkBit(&registers.b, 0);
    return 0;
}

uint8_t exe_cb_bit0c() {
    checkBit(&registers.c, 0);
    return 0;
}

uint8_t exe_cb_bit0d() {
    checkBit(&registers.d, 0);
    return 0;
}

uint8_t exe_cb_bit0e() {
    checkBit(&registers.e, 0);
    return 0;
}

uint8_t exe_cb_bit0h() {
    checkBit(&registers.h, 0);
    return 0;
}

uint8_t exe_cb_bit0l() {
    checkBit(&registers.l, 0);
    return 0;
}

uint8_t exe_cb_bit0phl() {
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 0);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit0a() {
    checkBit(&registers.a, 0);
    return 0;
}

uint8_t exe_cb_bit1b() {
    checkBit(&registers.b, 1);
    return 0;
}

uint8_t exe_cb_bit1c() {
    checkBit(&registers.c, 1);
    return 0;
}

uint8_t exe_cb_bit1d() {
    checkBit(&registers.d, 1);
    return 0;
}

uint8_t exe_cb_bit1e() {
    checkBit(&registers.e, 1);
    return 0;
}

uint8_t exe_cb_bit1h() {
    checkBit(&registers.h, 1);
    return 0;
}

uint8_t exe_cb_bit1l() {
    checkBit(&registers.l, 1);
    return 0;
}

uint8_t exe_cb_bit1phl() {
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 1);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit1a() {
    checkBit(&registers.a, 1);
    return 0;
}

// 0x5
uint8_t exe_cb_bit2b(){
    checkBit(&registers.b, 2);
    return 0;
}

uint8_t exe_cb_bit2c(){
    checkBit(&registers.c, 2);
    return 0;
}

uint8_t exe_cb_bit2d(){
    checkBit(&registers.d, 2);
    return 0;
}

uint8_t exe_cb_bit2e(){
    checkBit(&registers.e, 2);
    return 0;
}

uint8_t exe_cb_bit2h(){
    checkBit(&registers.h, 2);
    return 0;
}

uint8_t exe_cb_bit2l(){
    checkBit(&registers.l, 2);
    return 0;
}

uint8_t exe_cb_bit2phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 2);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit2a(){
    checkBit(&registers.a, 2);
    return 0;
}

uint8_t exe_cb_bit3b(){
    checkBit(&registers.b, 3);
    return 0;
}

uint8_t exe_cb_bit3c(){
    checkBit(&registers.c, 3);
    return 0;
}

uint8_t exe_cb_bit3d(){
    checkBit(&registers.d, 3);
    return 0;
}

uint8_t exe_cb_bit3e(){
    checkBit(&registers.e, 3);
    return 0;
}

uint8_t exe_cb_bit3h(){
    checkBit(&registers.h, 3);
    return 0;
}

uint8_t exe_cb_bit3l(){
    checkBit(&registers.l, 3);
    return 0;
}

uint8_t exe_cb_bit3phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 3);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit3a(){
    checkBit(&registers.a, 3);
    return 0;
}


// 0x6
uint8_t exe_cb_bit4b(){
    checkBit(&registers.b, 4);
    return 0;
}

uint8_t exe_cb_bit4c(){
    checkBit(&registers.c, 4);
    return 0;
}

uint8_t exe_cb_bit4d(){
    checkBit(&registers.d, 4);
    return 0;
}

uint8_t exe_cb_bit4e(){
    checkBit(&registers.e, 4);
    return 0;
}

uint8_t exe_cb_bit4h(){
    checkBit(&registers.h, 4);
    return 0;
}

uint8_t exe_cb_bit4l(){
    checkBit(&registers.l, 4);
    return 0;
}

uint8_t exe_cb_bit4phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 4);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit4a(){
    checkBit(&registers.a, 4);
    return 0;
}

uint8_t exe_cb_bit5b(){
    checkBit(&registers.b, 5);
    return 0;
}

uint8_t exe_cb_bit5c(){
    checkBit(&registers.c, 5);
    return 0;
}

uint8_t exe_cb_bit5d(){
    checkBit(&registers.d, 5);
    return 0;
}

uint8_t exe_cb_bit5e(){
    checkBit(&registers.e, 5);
    return 0;
}

uint8_t exe_cb_bit5h(){
    checkBit(&registers.h, 5);
    return 0;
}

uint8_t exe_cb_bit5l(){
    checkBit(&registers.l, 5);
    return 0;
}

uint8_t exe_cb_bit5phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 5);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit5a(){
    checkBit(&registers.a, 5);
    return 0;
}


// 0x7
uint8_t exe_cb_bit6b(){
    checkBit(&registers.b, 6);
    return 0;
}

uint8_t exe_cb_bit6c(){
    checkBit(&registers.c, 6);
    return 0;
}

uint8_t exe_cb_bit6d(){
    checkBit(&registers.d, 6);
    return 0;
}

uint8_t exe_cb_bit6e(){
    checkBit(&registers.e, 6);
    return 0;
}

uint8_t exe_cb_bit6h(){
    checkBit(&registers.h, 6);
    return 0;
}

uint8_t exe_cb_bit6l(){
    checkBit(&registers.l, 6);
    return 0;
}

uint8_t exe_cb_bit6phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 6);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit6a(){
    checkBit(&registers.a, 6);
    return 0;
}

uint8_t exe_cb_bit7b(){
    checkBit(&registers.b, 7);
    return 0;
}

uint8_t exe_cb_bit7c(){
    checkBit(&registers.c, 7);
    return 0;
}

uint8_t exe_cb_bit7d(){
    checkBit(&registers.d, 7);
    return 0;
}

uint8_t exe_cb_bit7e(){
    checkBit(&registers.e, 7);
    return 0;
}

uint8_t exe_cb_bit7h(){
    checkBit(&registers.h, 7);
    return 0;
}

uint8_t exe_cb_bit7l(){
    checkBit(&registers.l, 7);
    return 0;
}

uint8_t exe_cb_bit7phl(){
    uint8_t temp = readByte(registers.hl);
    checkBit(&temp, 7);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_bit7a(){
    checkBit(&registers.a, 7);
    return 0;
}

// 0x8
uint8_t exe_cb_res0b(){
    reset(&registers.b, 0);
    return 0;
}

uint8_t exe_cb_res0c(){
    reset(&registers.c, 0);
    return 0;
}

uint8_t exe_cb_res0d(){
    reset(&registers.d, 0);
    return 0;
}

uint8_t exe_cb_res0e(){
    reset(&registers.e, 0);
    return 0;
}

uint8_t exe_cb_res0h(){
    reset(&registers.h, 0);
    return 0;
}

uint8_t exe_cb_res0l(){
    reset(&registers.l, 0);
    return 0;
}

uint8_t exe_cb_res0phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 0);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res0a() {
    reset(&registers.a, 0);
    return 0;
}

uint8_t exe_cb_res1b(){
    reset(&registers.b, 1);
    return 0;
}

uint8_t exe_cb_res1c(){
    reset(&registers.c, 1);
    return 0;
}

uint8_t exe_cb_res1d(){
    reset(&registers.d, 1);
    return 0;
}

uint8_t exe_cb_res1e(){
    reset(&registers.e, 1);
    return 0;
}

uint8_t exe_cb_res1h(){
    reset(&registers.h, 1);
    return 0;
}

uint8_t exe_cb_res1l(){
    reset(&registers.l, 1);
    return 0;
}

uint8_t exe_cb_res1phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 1);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res1a() {
    reset(&registers.a, 1);
    return 0;
}

// 0x9
uint8_t exe_cb_res2b(){
    reset(&registers.b, 2);
    return 0;
}

uint8_t exe_cb_res2c(){
    reset(&registers.c, 2);
    return 0;
}

uint8_t exe_cb_res2d(){
    reset(&registers.d, 2);
    return 0;
}

uint8_t exe_cb_res2e(){
    reset(&registers.e, 2);
    return 0;
}

uint8_t exe_cb_res2h(){
    reset(&registers.h, 2);
    return 0;
}

uint8_t exe_cb_res2l(){
    reset(&registers.l, 2);
    return 0;
}

uint8_t exe_cb_res2phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 2);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res2a() {
    reset(&registers.a, 2);
    return 0;
}

uint8_t exe_cb_res3b(){
    reset(&registers.b, 3);
    return 0;
}

uint8_t exe_cb_res3c(){
    reset(&registers.c, 3);
    return 0;
}

uint8_t exe_cb_res3d(){
    reset(&registers.d, 3);
    return 0;
}

uint8_t exe_cb_res3e(){
    reset(&registers.e, 3);
    return 0;
}

uint8_t exe_cb_res3h(){
    reset(&registers.h, 3);
    return 0;
}

uint8_t exe_cb_res3l(){
    reset(&registers.l, 3);
    return 0;
}

uint8_t exe_cb_res3phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 3);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res3a() {
    reset(&registers.a, 3);
    return 0;
}


// 0xA
uint8_t exe_cb_res4b(){
    reset(&registers.b, 4);
    return 0;
}

uint8_t exe_cb_res4c(){
    reset(&registers.c, 4);
    return 0;
}

uint8_t exe_cb_res4d(){
    reset(&registers.d, 4);
    return 0;
}

uint8_t exe_cb_res4e(){
    reset(&registers.e, 4);
    return 0;
}

uint8_t exe_cb_res4h(){
    reset(&registers.h, 4);
    return 0;
}

uint8_t exe_cb_res4l(){
    reset(&registers.l, 4);
    return 0;
}

uint8_t exe_cb_res4phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 4);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res4a() {
    reset(&registers.a, 4);
    return 0;
}

uint8_t exe_cb_res5b(){
    reset(&registers.b, 5);
    return 0;
}

uint8_t exe_cb_res5c(){
    reset(&registers.c, 5);
    return 0;
}

uint8_t exe_cb_res5d(){
    reset(&registers.d, 5);
    return 0;
}

uint8_t exe_cb_res5e(){
    reset(&registers.e, 5);
    return 0;
}

uint8_t exe_cb_res5h(){
    reset(&registers.h, 5);
    return 0;
}

uint8_t exe_cb_res5l(){
    reset(&registers.l, 5);
    return 0;
}

uint8_t exe_cb_res5phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 5);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res5a() {
    reset(&registers.a, 5);
    return 0;
}

// 0xB
uint8_t exe_cb_res6b(){
    reset(&registers.b, 6);
    return 0;
}

uint8_t exe_cb_res6c(){
    reset(&registers.c, 6);
    return 0;
}

uint8_t exe_cb_res6d(){
    reset(&registers.d, 6);
    return 0;
}

uint8_t exe_cb_res6e(){
    reset(&registers.e, 6);
    return 0;
}

uint8_t exe_cb_res6h(){
    reset(&registers.h, 6);
    return 0;
}

uint8_t exe_cb_res6l(){
    reset(&registers.l, 6);
    return 0;
}

uint8_t exe_cb_res6phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 6);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res6a() {
    reset(&registers.a, 6);
    return 0;
}

uint8_t exe_cb_res7b(){
    reset(&registers.b, 7);
    return 0;
}

uint8_t exe_cb_res7c(){
    reset(&registers.c, 7);
    return 0;
}

uint8_t exe_cb_res7d(){
    reset(&registers.d, 7);
    return 0;
}

uint8_t exe_cb_res7e(){
    reset(&registers.e, 7);
    return 0;
}

uint8_t exe_cb_res7h(){
    reset(&registers.h, 7);
    return 0;
}

uint8_t exe_cb_res7l(){
    reset(&registers.l, 7);
    return 0;
}

uint8_t exe_cb_res7phl() {
    uint8_t temp = readByte(registers.hl);
    reset(&temp, 7);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_res7a() {
    reset(&registers.a, 7);
    return 0;
}


// 0xC
uint8_t exe_cb_set0b(){
    set(&registers.b, 0);
    return 0;
}

uint8_t exe_cb_set0c(){
    set(&registers.c, 0);
    return 0;
}

uint8_t exe_cb_set0d(){
    set(&registers.d, 0);
    return 0;
}

uint8_t exe_cb_set0e(){
    set(&registers.e, 0);
    return 0;
}

uint8_t exe_cb_set0h(){
    set(&registers.h, 0);
    return 0;
}

uint8_t exe_cb_set0l(){
    set(&registers.l, 0);
    return 0;
}

uint8_t exe_cb_set0phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 0);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set0a() {
    set(&registers.a, 0);
    return 0;
}

uint8_t exe_cb_set1b(){
    set(&registers.b, 1);
    return 0;
}

uint8_t exe_cb_set1c(){
    set(&registers.c, 1);
    return 0;
}

uint8_t exe_cb_set1d(){
    set(&registers.d, 1);
    return 0;
}

uint8_t exe_cb_set1e(){
    set(&registers.e, 1);
    return 0;
}

uint8_t exe_cb_set1h(){
    set(&registers.h, 1);
    return 0;
}

uint8_t exe_cb_set1l(){
    set(&registers.l, 1);
    return 0;
}

uint8_t exe_cb_set1phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 1);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set1a() {
    set(&registers.a, 1);
    return 0;
}


// 0xD
uint8_t exe_cb_set2b(){
    set(&registers.b, 2);
    return 0;
}

uint8_t exe_cb_set2c(){
    set(&registers.c, 2);
    return 0;
}

uint8_t exe_cb_set2d(){
    set(&registers.d, 2);
    return 0;
}

uint8_t exe_cb_set2e(){
    set(&registers.e, 2);
    return 0;
}

uint8_t exe_cb_set2h(){
    set(&registers.h, 2);
    return 0;
}

uint8_t exe_cb_set2l(){
    set(&registers.l, 2);
    return 0;
}

uint8_t exe_cb_set2phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 2);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set2a() {
    set(&registers.a, 2);
    return 0;
}

uint8_t exe_cb_set3b(){
    set(&registers.b, 3);
    return 0;
}

uint8_t exe_cb_set3c(){
    set(&registers.c, 3);
    return 0;
}

uint8_t exe_cb_set3d(){
    set(&registers.d, 3);
    return 0;
}

uint8_t exe_cb_set3e(){
    set(&registers.e, 3);
    return 0;
}

uint8_t exe_cb_set3h(){
    set(&registers.h, 3);
    return 0;
}

uint8_t exe_cb_set3l(){
    set(&registers.l, 3);
    return 0;
}

uint8_t exe_cb_set3phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 3);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set3a() {
    set(&registers.a, 3);
    return 0;
}


// 0xE
uint8_t exe_cb_set4b(){
    set(&registers.b, 4);
    return 0;
}

uint8_t exe_cb_set4c(){
    set(&registers.c, 4);
    return 0;
}

uint8_t exe_cb_set4d(){
    set(&registers.d, 4);
    return 0;
}

uint8_t exe_cb_set4e(){
    set(&registers.e, 4);
    return 0;
}

uint8_t exe_cb_set4h(){
    set(&registers.h, 4);
    return 0;
}

uint8_t exe_cb_set4l(){
    set(&registers.l, 4);
    return 0;
}

uint8_t exe_cb_set4phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 4);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set4a() {
    set(&registers.a, 4);
    return 0;
}

uint8_t exe_cb_set5b(){
    set(&registers.b, 5);
    return 0;
}

uint8_t exe_cb_set5c(){
    set(&registers.c, 5);
    return 0;
}

uint8_t exe_cb_set5d(){
    set(&registers.d, 5);
    return 0;
}

uint8_t exe_cb_set5e(){
    set(&registers.e, 5);
    return 0;
}

uint8_t exe_cb_set5h(){
    set(&registers.h, 5);
    return 0;
}

uint8_t exe_cb_set5l(){
    set(&registers.l, 5);
    return 0;
}

uint8_t exe_cb_set5phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 5);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set5a() {
    set(&registers.a, 5);
    return 0;
}

// 0xF
uint8_t exe_cb_set6b(){
    set(&registers.b, 5);
    return 0;
}

uint8_t exe_cb_set6c(){
    set(&registers.c, 6);
    return 0;
}

uint8_t exe_cb_set6d(){
    set(&registers.d, 6);
    return 0;
}

uint8_t exe_cb_set6e(){
    set(&registers.e, 6);
    return 0;
}

uint8_t exe_cb_set6h(){
    set(&registers.h, 6);
    return 0;
}

uint8_t exe_cb_set6l(){
    set(&registers.l, 6);
    return 0;
}

uint8_t exe_cb_set6phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 6);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set6a() {
    set(&registers.a, 6);
    return 0;
}

uint8_t exe_cb_set7b(){
    set(&registers.b, 7);
    return 0;
}

uint8_t exe_cb_set7c(){
    set(&registers.c, 7);
    return 0;
}

uint8_t exe_cb_set7d(){
    set(&registers.d, 7);
    return 0;
}

uint8_t exe_cb_set7e(){
    set(&registers.e, 7);
    return 0;
}

uint8_t exe_cb_set7h(){
    set(&registers.h, 7);
    return 0;
}

uint8_t exe_cb_set7l(){
    set(&registers.l, 7);
    return 0;
}

uint8_t exe_cb_set7phl() {
    uint8_t temp = readByte(registers.hl);
    set(&temp, 7);
    writeByte(registers.hl, temp);
    return 0;
}

uint8_t exe_cb_set7a() {
    set(&registers.a, 7);
    return 0;
}