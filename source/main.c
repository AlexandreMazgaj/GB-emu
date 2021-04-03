#include <stdio.h>
#include "headers/gb_cpu.h"


int main() {

    CPU_init();

    registers.a = 0x0f;


    add_a(0x01);


    printf("reg a = %X\n", 0x10 & 0x10);
    printf("FLAG H = %X\n", GETHFlAG());

    return 0;
}