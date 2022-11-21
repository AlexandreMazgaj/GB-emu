#pragma once

#include <stdint.h>

struct serial {
    uint8_t data;
    uint8_t control;
    uint8_t interrupt;
} extern serial;