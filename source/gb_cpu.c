#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"

struct registers registers;
uint8_t IME;
uint8_t IE;
uint8_t IF;
uint8_t stopped;
uint8_t cycle;

void CPU_init() {
    // registers.af = 0x01b0;
    registers.af = 0x1180;
    // registers.bc = 0x0013;]
    registers.bc = 0x0000;
    // registers.de = 0x00d8
    registers.de = 0xff56;
    // registers.hl = 0x014d;
    registers.hl = 0x000d;
    registers.pc = 0x0100;
    registers.sp = 0xfffe;

    IME = 0;
    IE = 0;
    IF = 0;

    stopped = 0;

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
        // printRegisters();

        if (op > MAX_KNOWN_OPCODE) {
            handleUnknownOp(op);
            registers.pc++;
            cycle = 1;
            return 0;
        }

        struct instruction instr = instructions[op];

        printf("pc: %X instruction: %s\n", registers.pc, instr.mnemonic);
        // fflush(stdout);



        cycle = instr.nb_cycles + instr.execute();

        if (instr.size_operand == 2)
            registers.pc += 2;
        else
            registers.pc++;
        

        if (registers.pc == 0x020B) { // 0xC252 c772 call for c16b ret, then goes to 100
            int i = 0;
            uint16_t addr = readWord(registers.pc+1);
            printf("l'addr de saut: %X\n", addr);
            printRegisters();
            return 220;
        }


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
    uint8_t IE = readByte(0xffff);
    uint8_t IF = readByte(0xff0f);

    if (IME) {
        // Checking if VBLANK enabled and if requested
        if ((IE & VBLANK_BIT) == VBLANK_BIT && (IF & VBLANK_BIT) == VBLANK_BIT) {
            pushWordStack(registers.pc);
            registers.pc = VBLANK_ADDR;
            // reset the IME
            IME = 0;
            // reset the IF flag for the interrupt
            IF ^= VBLANK_BIT; 
        }
        // Checking if LCD_STAT enabled and if requested
        if ((IE & LCD_STAT_BIT) == LCD_STAT_BIT && (IF & LCD_STAT_BIT) == LCD_STAT_BIT) {
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
    SETCFLAG(temp < 0);
    SETNFLAG(1);
    SETHFLAG((((registers.a & 0xf) - (reg & 0xf)) & 0x10) == 0x10);

    registers.a = registers.a - reg;
}

void adc_a(uint8_t reg) {
    uint16_t temp = (uint16_t)registers.a + (uint16_t)reg + (uint16_t)GETCFLAG();
    SETZFLAG((temp & 0x00ff) == 0);
    SETCFLAG(temp > 255);
    SETNFLAG(0);
    SETHFLAG((((registers.a & 0xf) + (reg & 0xf) + (GETCFLAG() & 0xf)) & 0x10) == 0x10);

    registers.a = (uint8_t)(temp & 0x00ff);
}

void sbc_a(uint8_t reg) {
    int8_t temp = registers.a - reg - GETCFLAG();
    SETZFLAG(temp == 0);
    SETCFLAG(temp < 0);
    SETNFLAG(1);
    SETHFLAG((((registers.a & 0xf) - (reg & 0xf) - (GETCFLAG() & 0xf)) & 0x10) == 0x10);

    registers.a = registers.a - reg - GETCFLAG();
}


void add_hl(uint16_t reg) {
    uint32_t temp = (uint32_t)registers.hl + (uint32_t)reg;
    SETCFLAG(temp > 0xffff);
    SETNFLAG(0);
    SETHFLAG(((registers.hl & 0x07ff) + (reg & 0x07ff)) > 0x07ff);

    registers.hl = (uint16_t)(temp & 0x0000ffff);
}


void add_sp(int8_t val) {
    int32_t temp = registers.sp + (int32_t)val;
    SETZFLAG(0);
    SETNFLAG(0);
    SETCFLAG((temp & 0xffff) > 255);
    if (val >= 0)
        SETHFLAG((((registers.sp & 0xf) + (val & 0xf)) & 0x10) == 0x10);
    else
        SETHFLAG((((registers.sp & 0xf) - ((uint8_t)val & 0xf)) & 0x10) == 0x10);

    registers.sp = (uint32_t)temp;
}


void inc8bReg(uint8_t* reg) {
    SETZFLAG((uint8_t)((*reg) + 1) == 0);
    SETNFLAG(0);
    SETHFLAG(((((*reg) & 0xf) + (1 & 0xf)) & 0x10) == 0x10);

    (*reg)++;
}


void dec8bReg(uint8_t* reg) {
    SETZFLAG((uint8_t)((*reg) - 1) == 0);
    SETNFLAG(0);
    SETHFLAG(((((*reg) & 0xf) - (1 & 0xf)) & 0x10) == 0x10);

    (*reg)--;
}


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
    int cp_val = registers.a - reg;

    SETZFLAG(cp_val == 0);
    SETNFLAG(1);
    SETHFLAG((((registers.a & 0xf) + (reg & 0xf) + (GETCFLAG() & 0xf)) & 0x10) == 0x10);
    SETCFLAG(cp_val < 0);
}


void rotateLeft(uint8_t* reg) {
    uint8_t hiBit = ((*reg) >> 7) & 1;
    SETNFLAG(0);
    SETHFLAG(0);
    SETZFLAG(0);
    (*reg) = ((*reg) << 1) | hiBit;
    SETCFLAG((*reg) & 1);
}

void rotateRight(uint8_t* reg) {
    uint8_t loBit = (*reg) & 1;
    SETNFLAG(0);
    SETHFLAG(0);
    SETZFLAG(0);
    (*reg) = ((*reg) >> 1) | (loBit << 7);
    SETCFLAG(((*reg) & 0x80) >> 7);
}

void rotateLeftCarry(uint8_t* reg) {
    SETNFLAG(0);
    SETHFLAG(0);
    SETZFLAG(0);
    uint8_t hiBit = ((*reg) >> 7) & 1;
    (*reg) = ((*reg) << 1) | GETCFLAG();
    SETCFLAG(hiBit);
}

void rotateRightCarry(uint8_t* reg) {
    uint8_t loBit = (*reg) & 1;
    SETNFLAG(0);
    SETHFLAG(0);
    SETZFLAG(0);
    (*reg) = ((*reg) >> 1) | (GETCFLAG() << 7);
    SETCFLAG(loBit);
}



// ---------------
// DEBUG FUNCTIONS
// ---------------

void printRegFlags() {
    printf("Z flag: %X\n", GETZFLAG());
    printf("N flag: %X\n", GETNFLAG());
    printf("H flag: %X\n", GETHFlAG());
    printf("C flag: %X\n", GETCFLAG());
}


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
    printf("af: %X; ", registers.af);
    printf("bc: %X; ", registers.bc);
    printf("de: %X; ", registers.de);
    printf("hl: %X\n", registers.hl);
}