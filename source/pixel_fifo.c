#include "headers/pixel_fifo.h"



void bgPixelFifo_init(PixelFifo* p) {
    p->head = -1;
    p->tail = -1;
    for (uint8_t i = 0; i < 16; i++) {
        p->queue[i] = 0;
    }
}

uint8_t dequeue(PixelFifo* p) {
    if (isEmpty(p))
        return 0;
    uint8_t tempVal = p->queue[p->tail];
    p->tail = (--p->tail) % 16;
    return tempVal;
}

void enqueue(PixelFifo* p, uint8_t pixel) {
    if (isFull(p))
        return;
    p->queue[p->head] = pixel;
    p->head = (++p->head) % 16;
    p->size++;
}


uint8_t isEmpty(PixelFifo* p) {
    if (p->size == 0) {
        return 1;
    }
    return 0;
}

uint8_t isFull(PixelFifo* p) {
    if (p->size >= 15)
        return 1;
    return 0;
}

uint8_t isAbove8Pixel(PixelFifo* p) {
    if (p->size > 7)
        return 1;
    return 0;
}
