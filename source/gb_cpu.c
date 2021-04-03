#include "headers/gb_cpu.h"

struct registers registers;

void CPU_init() {
    registers.af = 0;
    registers.bc = 0;
    registers.de = 0;
    registers.hl = 0;
    registers.pc = 0;
    registers.sp = 0;

}


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