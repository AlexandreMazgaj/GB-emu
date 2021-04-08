#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"

struct registers registers;
uint8_t IME;
uint8_t IE;
uint8_t IF;

void CPU_init() {
    registers.af = 0x01b0;
    registers.bc = 0x0013;
    registers.de = 0x00d8;
    registers.hl = 0x014d;
    registers.pc = 0x0100;
    registers.sp = 0xfffe;

    IME = 0;
    IE = 0;
    IF = 0;

}


// -------------
// CPU FUNCTIONS
// -------------
void clock() {
    checkInterrupts();

    // uint8_t clock
    uint8_t op = readByte(registers.pc);

}



// -------------------
// INTERRUPT FUNCTIONS
// -------------------
void checkInterrupts() {
    uint8_t IE = readByte(0xffff);
    uint8_t IF = readByte(0xff0f);

    printf("Sorting right after the write ie = %X, if = %X\n", IE, IF);
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
            printf("LCD Stat interrupt\n");
            pushWordStack(registers.pc);
            registers.pc = LCD_STAT_ADDR;
            // reset the IME
            IME = 0;
            // reset the IF flag for the interrupt
            printf("Before lcd stat reset %X\n", IF);
            IF ^= LCD_STAT_BIT; 
            printf("After the lcd stat reset %X\n", IF);
        }
        // Checking if TIMER enabled and if requested
        if ((IE & TIMER_BIT) == TIMER_BIT && (IF & TIMER_BIT) == TIMER_BIT) {
            printf("Timer interrupt\n");
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
    SETZFLAG(temp == 0);
    SETCFLAG(temp > 255);
    SETNFLAG(0);
        printf("f: %X\n", registers.f);

    SETHFLAG(((registers.a & 0xf) + (reg & 0xf)) == 0x10);


    printf("f: %X\n", registers.f);

    registers.a = (uint8_t)(temp & 0x00ff);
}

void sub_a(uint8_t reg) {
    int8_t temp = registers.a - reg;
    SETZFLAG(temp == 0);
    SETCFLAG(temp < 0);
    SETNFLAG(1);
    SETHFLAG(((registers.a & 0xf) - (reg & 0xf)) & 0x10 == 0x10);

    registers.a = registers.a - reg;
}

void adc_a(uint8_t reg) {
    uint16_t temp = (uint16_t)registers.a + (uint16_t)reg + (uint16_t)GETCFLAG();
    SETZFLAG(temp == 0);
    SETCFLAG(temp > 255);
    SETNFLAG(0);
    SETHFLAG(((registers.a & 0xf) + (reg & 0xf) + (GETCFLAG() & 0xf)) & 0x10 == 0x10);

    registers.a = (uint8_t)(temp & 0x00ff);
}

void sbc_a(uint8_t reg) {
    int8_t temp = registers.a - reg - GETCFLAG();
    SETZFLAG(temp == 0);
    SETCFLAG(temp < 0);
    SETNFLAG(1);
    SETHFLAG(((registers.a & 0xf) - (reg & 0xf) - (GETCFLAG() & 0xf)) & 0x10 == 0x10);

    registers.a = registers.a - reg - GETCFLAG();
}