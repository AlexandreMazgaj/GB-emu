#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"


int main() {

    CPU_init();
    registers.f = 0;


    SETCFLAG(0);

    registers.a = 0xff;

    printf("%X", GETCFLAG());
    printBinary(registers.a);

    exe_rra();
    printf("%X", GETCFLAG());
    printBinary(registers.a);



    return 0;
}