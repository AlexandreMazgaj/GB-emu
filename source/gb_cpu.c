#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include <stdio.h>

struct registers registers;
uint8_t IME;
uint8_t IE;
uint8_t IF;
uint8_t stopped;
uint8_t halted;
uint8_t cycle;
char dbg_msg[1024];
int msg_size;

void CPU_init() {
  registers.af = 0x01b0;
  // registers.af = 0x1180;
  // SETCFLAG(1);
  // SETHFLAG(1);
  registers.bc = 0x0013;
  // registers.bc = 0x0000;
  registers.de = 0x00d8;
  // registers.de = 0xff56;
  registers.hl = 0x014d;
  // registers.hl = 0x000d;
  registers.pc = 0x0100;
  registers.sp = 0xfffe;

  IME = 0;
  IE = 0;
  IF = 0;

  stopped = 0;
  halted = 0;

  for (int i = 0; i < 1024; i++)
    dbg_msg[i] = 0;
  msg_size = 0;

  writeByte(0xFF05, 0);
  writeByte(0xFF06, 0);
  writeByte(0xFF07, 0);
  writeByte(0xFF10, 0x80);
  writeByte(0xFF11, 0xBF);
  writeByte(0xFF12, 0xF3);
  writeByte(0xFF14, 0xBF);
  writeByte(0xFF16, 0x3F);
  writeByte(0xFF17, 0x00);
  writeByte(0xFF19, 0xBF);
  writeByte(0xFF1A, 0x7A);
  writeByte(0xFF1B, 0xFF);
  writeByte(0xFF1C, 0x9F);
  writeByte(0xFF1E, 0xBF);
  writeByte(0xFF20, 0xFF);
  writeByte(0xFF21, 0x00);
  writeByte(0xFF22, 0x00);
  writeByte(0xFF23, 0xBF);
  writeByte(0xFF24, 0x77);
  writeByte(0xFF25, 0xF3);
  writeByte(0xFF26, 0xF1);
  writeByte(0xFF40, 0x91);
  writeByte(0xFF42, 0x00);
  writeByte(0xFF43, 0x00);
  writeByte(0xFF45, 0x00);
  writeByte(0xFF47, 0xFC);
  writeByte(0xFF48, 0xFF);
  writeByte(0xFF49, 0xFF);
  writeByte(0xFF4A, 0x00);
  writeByte(0xFF4B, 0x00);
  writeByte(0xFFFF, 0x00);
}

// -------------
// CPU FUNCTIONS
// -------------
uint8_t CPU_clock() {

  checkInterrupts();

  // if we have finished the
  if (cycle == 0) {
    // uint8_t clock
    uint8_t op = readByte(registers.pc);

    // printf("PC: %X\n", registers.pc);
    if (op > MAX_KNOWN_OPCODE) {
      handleUnknownOp(op);
      registers.pc++;
      cycle = 1;
      return 0;
    }

    // we check if the op is a CB prefix
    struct instruction instr;
    // only used if we go through CB prefix operations
    uint8_t cb_cycle = 0;
    uint8_t cb_operand = 0;
    if (op == 0xCB) {
      uint8_t cb_op = readByte(registers.pc + 1);
      instr = cb_instructions[cb_op];
      cb_cycle = 4;
      cb_operand = 1;
    } else {
      instr = instructions[op];
    }

    // debugging
    // printRegisters();
    // printInstruction(instr);

    // printing to stderr, do ./GB 2> output.txt
    dprintf(2,
            "A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X "
            "PC:%04X "
            "PCMEM:%02X,%02X,%02X,%02X\n",
            registers.a, registers.f, registers.b, registers.c, registers.d,
            registers.e, registers.h, registers.l, registers.sp, registers.pc,
            readByte(registers.pc), readByte(registers.pc + 1),
            readByte(registers.pc + 2), readByte(registers.pc + 3));

    // serial
    dbg_update();
    dbg_print();

    // executing the instruction
    cycle = instr.nb_cycles + instr.execute() + cb_cycle;

    if (halted) {
      // printf("THE CPU IS HALTED\n");
      return 1;
    }

    if (instr.size_operand == 2)
      registers.pc += 2;
    else
      registers.pc++;

    registers.pc += cb_operand;

    // if (registers.pc == 0x020B) { // 0xC252 c772 call for c16b ret, then goes
    // to 100
    //     int i = 0;
    //     uint16_t addr = readWord(registers.pc+1);
    //     printf("l'addr de saut: %X\n", addr);
    //     printRegisters();
    //     return 220;
    // }

    return 1;
  }

  // if (cycle != 0)
  //     printf("Still doing the op\n");

  cycle--;

  return 0;
}

// -------------------
// INTERRUPT FUNCTIONS
// -------------------
void checkInterrupts() {
  // printf("Checking for interrupts\n");
  IE = readByte(0xffff);
  IF = readByte(0xff0f);

  if (IME || halted == 1) {
    // this means that at least one interrupt has been triggered
    if (IE & IF) {
      // printf("THE CPU IS NOT HALTED\n");
      halted = 0;
    }
    // Checking if VBLANK enabled and if requested
    if ((IE & VBLANK_BIT) == VBLANK_BIT && (IF & VBLANK_BIT) == VBLANK_BIT) {
      pushWordStack(registers.pc);
      registers.pc = VBLANK_ADDR;
      // reset the IME
      IME = 0;
      // reset the IF flag for the interrupt
      IF ^= VBLANK_BIT;
      printf("The request for the VBLANK!\n");
    }
    // Checking if LCD_STAT enabled and if requested
    if ((IE & LCD_STAT_BIT) == LCD_STAT_BIT &&
        (IF & LCD_STAT_BIT) == LCD_STAT_BIT) {
      // printf("LCD Stat interrupt\n");
      pushWordStack(registers.pc);
      registers.pc = LCD_STAT_ADDR;
      // reset the IME
      IME = 0;
      // reset the IF flag for the interrupt
      // printf("Before lcd stat reset %X\n", IF);
      IF ^= LCD_STAT_BIT;
      // printf("After the lcd stat reset %X\n", IF);
    }
    // Checking if TIMER enabled and if requested
    if ((IE & TIMER_BIT) == TIMER_BIT && (IF & TIMER_BIT) == TIMER_BIT) {
      // printf("Timer interrupt\n");
      pushWordStack(registers.pc);
      registers.pc = TIMER_ADDR;
      // reset the IME
      IME = 0;
      // reset the IF flag for the interrupt
      IF ^= TIMER_BIT;
    }
    // Checking if SERIAL enabled and if requested
    if ((IE & SERIAL_BIT) == SERIAL_BIT && (IF & SERIAL_BIT) == SERIAL_BIT) {
      pushWordStack(registers.pc);
      registers.pc = SERIAL_ADDR;
      // reset the IME
      IME = 0;
      // reset the IF flag for the interrupt
      IF ^= SERIAL_BIT;
    }
    // Checking if JOYPAD enabled and if requested
    if ((IE & JOYPAD_BIT) == JOYPAD_BIT && (IF & JOYPAD_BIT) == JOYPAD_BIT) {
      pushWordStack(registers.pc);
      registers.pc = JOYPAD_ADDR;
      // reset the IME
      IME = 0;
      // reset the IF flag for the interrupt
      IF ^= JOYPAD_BIT;
    }
    // we reset the interrupt request flags
    writeByte(0xff0f, IF);
  }
}

// --------------
// MATH FUNCTIONS
// --------------
void add_a(uint8_t reg) {
  uint16_t temp = (uint16_t)registers.a + (uint16_t)reg;
  SETZFLAG((temp & 0x00ff) == 0);
  SETCFLAG(temp > 255);
  SETNFLAG(0);

  SETHFLAG((((registers.a & 0xf) + (reg & 0xf)) & 0x10) == 0x10);

  registers.a = (uint8_t)(temp & 0x00ff);
}

void sub_a(uint8_t reg) {
  int8_t temp = registers.a - reg;
  SETZFLAG(temp == 0);
  SETCFLAG(registers.a < reg);
  SETNFLAG(1);
  // SETHFLAG((((registers.a & 0xf) - (reg & 0xf)) & 0x10) == 0x10);
  SETHFLAG((reg & 0xf) > (registers.a & 0xf));

  registers.a = registers.a - reg;
}

void adc_a(uint8_t reg) {
  uint16_t temp = (uint16_t)registers.a + (uint16_t)reg + (uint16_t)GETCFLAG();
  SETZFLAG((temp & 0x00ff) == 0);
  SETCFLAG(temp > 255);
  SETNFLAG(0);
  SETHFLAG((((registers.a & 0xf) + (reg & 0xf) + (GETCFLAG() & 0xf)) & 0x10) ==
           0x10);

  registers.a = (uint8_t)(temp & 0x00ff);
}

void sbc_a(uint8_t reg) {
  int8_t temp = registers.a - reg - GETCFLAG();
  SETZFLAG(temp == 0);
  SETCFLAG(registers.a < reg);
  SETNFLAG(1);
  // SETHFLAG((((registers.a & 0xf) - (reg & 0xf) - (GETCFLAG() & 0xf)) & 0x10)
  // == 0x10);
  SETHFLAG((reg & 0xf) > (registers.a & 0xf));

  registers.a = registers.a - reg - GETCFLAG();
}

void add_hl(uint16_t reg) {
  uint32_t temp = (uint32_t)registers.hl + (uint32_t)reg;
  SETCFLAG(temp > 0xffff);
  SETNFLAG(0);
  SETHFLAG(((registers.hl & 0x0fff) + (reg & 0x0fff)) > 0x1000);

  registers.hl = (uint16_t)(temp & 0x0000ffff);
}

void add_sp(int8_t val) {
  int32_t temp = (uint32_t)registers.sp + (int32_t)val;
  SETZFLAG(0);
  SETNFLAG(0);
  SETCFLAG(temp > 0xffff);
  if (val >= 0)
    SETHFLAG((((registers.sp & 0xf) + (val & 0xf)) & 0x10) == 0x10);
  else
    SETHFLAG((((registers.sp & 0xf) - ((uint8_t)val & 0xf)) & 0x10) == 0x10);

  registers.sp = (uint32_t)temp;
}

void inc8bReg(uint8_t *reg) {
  SETZFLAG((uint8_t)((*reg) + 1) == 0);
  SETNFLAG(0);
  SETHFLAG(((((*reg) & 0xf) + (1 & 0xf)) & 0x10) == 0x10);

  (*reg)++;
}

void dec8bReg(uint8_t *reg) {
  SETZFLAG((uint8_t)((*reg) - 1) == 0);
  SETNFLAG(1);
  SETHFLAG(((((*reg) & 0xf) - (1 & 0xf)) & 0x10) == 0x10);

  (*reg)--;
}

// ---------------
// LOGIC FUNCTIONS
// ---------------

void and_a(uint8_t reg) {
  registers.a &= reg;

  SETZFLAG(registers.a == 0);
  SETNFLAG(0);
  SETHFLAG(1);
  SETCFLAG(0);
}

void xor_a(uint8_t reg) {
  registers.a ^= reg;

  SETZFLAG(registers.a == 0);
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(0);
}

void or_a(uint8_t reg) {
  registers.a |= reg;

  SETZFLAG(registers.a == 0);
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(0);
}

void cp_a(uint8_t reg) {
  int cp_val = registers.a - reg; //- GETCFLAG();

  SETZFLAG(cp_val == 0);
  SETNFLAG(1);
  SETCFLAG(cp_val < 0);
  // SETHFLAG((((registers.a & 0xf) + (reg & 0xf) + (GETCFLAG() & 0xf)) & 0x10)
  // == 0x10);
  SETHFLAG((reg & 0xf) > (registers.a & 0xf));
}

void rotateLeft(uint8_t *reg) {
  uint8_t hiBit = ((*reg) >> 7) & 1;
  SETNFLAG(0);
  SETHFLAG(0);
  (*reg) = ((*reg) << 1) | hiBit;
  SETCFLAG((*reg) & 1);
  SETZFLAG((*reg) == 0);
}

void rotateRight(uint8_t *reg) {
  uint8_t loBit = (*reg) & 1;
  SETNFLAG(0);
  SETHFLAG(0);
  (*reg) = ((*reg) >> 1) | (loBit << 7);
  SETCFLAG(((*reg) & 0x80) >> 7);
  SETZFLAG((*reg) == 0);
}

void rotateLeftCarry(uint8_t *reg) {
  SETNFLAG(0);
  SETHFLAG(0);
  uint8_t hiBit = ((*reg) >> 7) & 1;
  (*reg) = ((*reg) << 1) | GETCFLAG();
  SETCFLAG(hiBit);
  SETZFLAG((*reg) == 0);
}

void rotateRightCarry(uint8_t *reg) {
  uint8_t loBit = (*reg) & 1;
  SETNFLAG(0);
  SETHFLAG(0);
  (*reg) = ((*reg) >> 1) | (GETCFLAG() << 7);
  SETCFLAG(loBit);
  SETZFLAG((*reg) == 0);
}

void shiftLeft(uint8_t *reg) {
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(((*reg) & 0x80) == 0x80);
  (*reg) = ((*reg) << 1);
  SETZFLAG((*reg) == 0);
}

void shiftRightMSB(uint8_t *reg) {
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(((*reg) & 0x01) == 0x01);
  (*reg) = ((*reg) >> 1) | ((*reg) & 0x80);
  SETZFLAG((*reg) == 0);
}

void shiftRight(uint8_t *reg) {
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(((*reg) & 0x01) == 0x01);
  (*reg) = ((*reg) >> 1);
  SETZFLAG((*reg) == 0);
}

// bit manipulation

void swap(uint8_t *reg) {
  SETNFLAG(0);
  SETHFLAG(0);
  SETCFLAG(0);
  SETZFLAG((*reg) == 0);
  uint8_t lowerBits = (*reg) & 0x0f;
  (*reg) = ((*reg) >> 4) | (lowerBits << 4);
}

void checkBit(uint8_t *reg, uint8_t bit) {
  SETNFLAG(0);
  SETHFLAG(1);
  SETZFLAG((((*reg) >> bit) & 1) == 0);
}

void reset(uint8_t *reg, uint8_t bit) { (*reg) = (*reg) & (0xff ^ (1 << bit)); }

void set(uint8_t *reg, uint8_t bit) { (*reg) = (*reg) | (1 << bit); }

// ---------------
// DEBUG FUNCTIONS
// ---------------

void printBinary(uint8_t hex) {
  printf("%x", (hex >> 7) & 1);
  printf("%x", (hex >> 6) & 1);
  printf("%x", (hex >> 5) & 1);
  printf("%x", (hex >> 4) & 1);
  printf("%x", (hex >> 3) & 1);
  printf("%x", (hex >> 2) & 1);
  printf("%x", (hex >> 1) & 1);
  printf("%x\n", hex & 1);
}

void printRegisters() {
  printf("A: %X; ", registers.a);
  printf("F: ");
  if (GETZFLAG())
    printf("Z");
  else
    printf("-");
  if (GETNFLAG())
    printf("N");
  else
    printf("-");
  if (GETHFLAG())
    printf("H");
  else
    printf("-");
  if (GETCFLAG())
    printf("C; ");
  else
    printf("-; ");
  printf("BC: %X; ", registers.bc);
  printf("DE: %X; ", registers.de);
  printf("HL: %X; ", registers.hl);
  printf("SP: %X; ", registers.sp);
}

void dbg_update() {
  if (readByte(0xFF02) == 0x81) {
    char c = (char)readByte(0xFF01);
    dbg_msg[msg_size++] = c;

    writeByte(0xFF02, 0);
  }
}

void dbg_print() {
  if (dbg_msg[0]) {
    printf("DBG: %s\n", dbg_msg);
  }
}

void printInstruction(struct instruction instr) {
  if (instr.size_operand == 0) {
    printf("pc: %X instruction: %s\n", registers.pc, instr.mnemonic);
  } else if (instr.size_operand == 1) {
    char mnemonic_with_data[256];
    snprintf(mnemonic_with_data, sizeof(mnemonic_with_data), instr.mnemonic,
             readByte(registers.pc + 1));
    printf("pc: %X instruction: %s\n", registers.pc, mnemonic_with_data);
  } else if (instr.size_operand == 2) {
    char mnemonic_with_data[256];
    snprintf(mnemonic_with_data, sizeof(mnemonic_with_data), instr.mnemonic,
             ((uint16_t)readByte(registers.pc + 2) << 8) |
                 (uint16_t)readByte(registers.pc + 1));
    printf("pc: %X instruction: %s\n", registers.pc, mnemonic_with_data);
  }
}