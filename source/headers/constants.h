#pragma once

#define INSTRUCTIONS_SIZE 256
#define RAM_SIZE 8 * 1024
#define ROM_BANK_SIZE 32 * 1024
#define OAM_SIZE 256
#define HIGH_RAM_SIZE 256
#define MAX_CARTRIDGE_SIZE 8 * 1024 * 1024 + ROM_BANK_SIZE // 8Mibs + 32Kibs
#define MAX_RAM_SIZE 32 * 1024
#define SCREEN_HEIGHT 144
#define SCREEN_WIDTH 160
#define VIDEO_RAM_SIZE 16 * 1024
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64
#define TICKS 60

// definitions for conditional compilation for logs
#define SERIAL_PRINT 0
#define INSTRUCTION_PRINT 0
