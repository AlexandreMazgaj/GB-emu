#include <stdint.h>
#include "constants.h"

// Definition of macros for flags
#define SETZFLAG(value) (registers.f = registers.f | ((value) << 7))
#define SETNFLAG(value) (registers.f = registers.f | ((value) << 6))
#define SETHFLAG(value) (registers.f = registers.f | ((value) << 5))
#define SETCFLAG(value) (registers.f = registers.f | ((value) << 4))


#define GETZFLAG(value) (registers.f & (1 << 7))
#define GETNFLAG(value) (registers.f & (1 << 6))
#define GETHFlAG(value) (registers.f & (1 << 5))
#define GETCFLAG(value) (registers.f & (1 << 4))


// typedef uint8_t (*Operation)(void);



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

// struct {

// } const extern instructions[INSTRUCTIONS_SIZE];



void add_a(uint8_t reg);
void sub_a(uint8_t reg);

void adc_a(uint8_t reg);
void sbc_a(uint8_t reg);

