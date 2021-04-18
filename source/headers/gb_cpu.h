#pragma once

#include <stdint.h>
#include "constants.h"

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




// Interrupt Master enable flag
extern uint8_t IME;
// interrupt enable
extern uint8_t IE;
// interrupt request
extern uint8_t IF;


// stop CPU flag
extern uint8_t stopped;



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



// CPU functions
void clock();


// interrupt functions
void checkInterrupts();



// Math functions
void add_a(uint8_t reg);
void sub_a(uint8_t reg);

void adc_a(uint8_t reg);
void sbc_a(uint8_t reg);

void add_hl(uint16_t reg);

void inc8bReg(uint8_t* reg);
void dec8bReg(uint8_t* reg);

void rotateLeft(uint8_t* reg);
void rotateRight(uint8_t* reg);

void rotateLeftCarry(uint8_t* reg);
void rotateRightCarry(uint8_t* reg);



// Debug functions
void printRegFlags();
void printBinary(uint8_t hex);