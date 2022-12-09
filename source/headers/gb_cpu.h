#pragma once

#include <stdint.h>
#include "constants.h"
#include "opcodes.h"

// Definition of macros for flags
#define SETZFLAG(value) (registers.f = ((value==0)?registers.f & (~(1 << 7)): registers.f | (1 << 7)))
#define SETNFLAG(value) (registers.f = ((value==0)?registers.f & (~(1 << 6)): registers.f | (1 << 6)))
#define SETHFLAG(value) (registers.f = ((value==0)?registers.f & (~(1 << 5)): registers.f | (1 << 5)))
#define SETCFLAG(value) (registers.f = ((value==0)?registers.f & (~(1 << 4)): registers.f | (1 << 4)))

#define GETZFLAG() ((registers.f & (1 << 7)) >> 7)
#define GETNFLAG() ((registers.f & (1 << 6)) >> 6)
#define GETHFlAG() ((registers.f & (1 << 5)) >> 5)
#define GETCFLAG() ((registers.f & (1 << 4)) >> 4)


// Definition of macros for interrupts
#define REQUEST_INTERRUPT(bit) (IF |= (uint8_t)bit)

#define VBLANK_BIT (1 << 0)
#define LCD_STAT_BIT (1 << 1)
#define TIMER_BIT (1 << 2)
#define SERIAL_BIT (1 << 3)
#define JOYPAD_BIT (1 << 4)

#define VBLANK_ADDR (0x40)
#define LCD_STAT_ADDR (0x48)
#define TIMER_ADDR (0x50)
#define SERIAL_ADDR (0x58)
#define JOYPAD_ADDR (0x60)


// used for the debugging roms
extern char dbg_msg[1024];
extern int msg_size;




// Interrupt Master enable flag
extern uint8_t IME;
// interrupt enable
extern uint8_t IE;
// interrupt request
extern uint8_t IF;


// stop CPU flag
extern uint8_t stopped;
extern uint8_t halted;




struct registers {
    union {
        struct {
            uint8_t f;
            uint8_t a;
        };
        uint16_t af;
    };

    union {
        struct {
            uint8_t c;
            uint8_t b;
        };
        uint16_t bc;
    };

    union {
        struct {
            uint8_t e;
            uint8_t d;
        };
        uint16_t de;
    };

    union {
        struct {
            uint8_t l;
            uint8_t h;
        };
        uint16_t hl;
    };

    uint16_t pc;
    uint16_t sp;



} extern registers;

void CPU_init();



// CPU functions and attributes
uint8_t CPU_clock();
extern uint8_t cycle;

// interrupt functions
void checkInterrupts();



// Math functions
// --------------

// a = a + reg
void add_a(uint8_t reg);
// a = a - reg
void sub_a(uint8_t reg);

// a = a + reg + carry
void adc_a(uint8_t reg);
// a = a - reg - carry
void sbc_a(uint8_t reg);

// hl = hl + reg
void add_hl(uint16_t reg);

// sp = sp + signed value
void add_sp(int8_t val);

void inc8bReg(uint8_t* reg);
void dec8bReg(uint8_t* reg);



// Logic functions
// ---------------

// logical AND between the reg passed in parameter and register a, the value is stored in a
void and_a(uint8_t reg);
// logical XOR between the reg passed in parameter and register a, the value is stored in a
void xor_a(uint8_t reg);
// logical OR between the reg passed in parameter and register a, the value is stored in a
void or_a(uint8_t reg);
// comparison (a - reg) between register a and reg passed in parameter
void cp_a(uint8_t reg);

void rotateLeft(uint8_t* reg);
void rotateRight(uint8_t* reg);

void rotateLeftCarry(uint8_t* reg);
void rotateRightCarry(uint8_t* reg);

void shiftLeft(uint8_t* reg);
void shiftRight(uint8_t* reg);
void shiftRightMSB(uint8_t* reg);

// bit manipulation
void swap(uint8_t* reg);
void checkBit(uint8_t* reg, uint8_t bit);
void reset(uint8_t* reg, uint8_t bit);
void set(uint8_t* reg, uint8_t bit);



// Debug functions
void printRegFlags();
void printBinary(uint8_t hex);
void printRegisters();
void printInstruction(struct instruction intr);