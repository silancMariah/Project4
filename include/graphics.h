/*
  graphics.h
  - Publika prototyper för grafikfunktioner (putPixel, clearScreen, drawRect,
    drawPaddle, drawBall).
  TODO:
  - Fyll i prototyper så andra filer kan inkludera denna header.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ball.h"
#include "paddle.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
extern volatile unsigned short *vga_buffer;
void vga_init_dma(void);

void putPixel(int x, int y, unsigned short color);
void clearScreen(unsigned short color);
void drawRect(int x, int y, int w, int h, unsigned short color);
void drawPattern(int x0, int y0, const int *pattern, int w, int h,
                 unsigned short color_on, unsigned short color_off);
void drawBall(const Ball *b, unsigned short color);
void drawPaddle(const Paddle *p, unsigned short color);
void drawTestPattern(void);

#ifdef VGA_SIMULATION
void presentFrame(void);
#endif
#endif
