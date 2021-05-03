#include "headers/gb_ppu.h"


struct ppu ppu;


void writePPU(uint16_t addr, uint8_t val) {
    if (addr == 0xff40) { ppu.reg_lcdc = val; return; }
    if (addr == 0xff41) { ppu.reg_stat = val; return; }
    if (addr == 0xff42) { ppu.scrollY = val; return; }
    if (addr == 0xff43) { ppu.scrollX = val; return; }
    // if (addr == 0xff44) { ppu.LY = val; return; }
    if (addr == 0xff45) { ppu.LYC = val; return; }
    if (addr == 0xff4a) { ppu.WY = val; return; }
    if (addr == 0xff4b) { ppu.WX = val; return; }
}