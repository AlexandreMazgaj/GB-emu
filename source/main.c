#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"


int main() {

    CPU_init();

    SETCFLAG(0);

    registers.f = 0;

    registers.a = 0x7f;

    SETCFLAG(1);

    rotateLeftCarry(&registers.a);

    printf("reg: %x\n", registers.a);

    SETCFLAG(0);

    printRegFlags();


    printBinary(registers.f);

    // SETCFLAG(0);
    printBinary(registers.f);





    return 0;
}