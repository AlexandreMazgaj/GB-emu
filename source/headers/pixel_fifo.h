#include <stdint.h>

typedef struct PixelFifo {
  uint16_t queue[16];
  int8_t head;
  int8_t tail;
  uint8_t size;

} PixelFifo;

void pixelFifo_init(PixelFifo *p);

uint8_t dequeue(PixelFifo *p);
void enqueue(PixelFifo *p, uint16_t pixel);
uint8_t isEmpty(PixelFifo *p);
uint8_t isFull(PixelFifo *p);

uint8_t isAbove8Pixel(PixelFifo *p);
