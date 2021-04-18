#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"


int main() {

    CPU_init();


    registers.f = 0;

    registers.a = 0x7f;

    SETCFLAG(1);

    printf("%x",GETCFLAG());

    printBinary(registers.a);

    rotateRightCarry(&registers.a);

    printf("%x",GETCFLAG());
    printBinary(registers.a);


    printRegFlags();


    rotateRightCarry(&registers.a);
    printf("%x",GETCFLAG());
    printBinary(registers.a);
    printRegFlags();





    return 0;
}