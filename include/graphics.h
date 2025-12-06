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
extern volatile unsigned char *vga_buffer;

void putPixel(int x, int y, unsigned char color);
void clearScreen(unsigned char color);
void drawRect(int x, int y, int w, int h, unsigned char color);
void drawPattern(int x0, int y0, const int *pattern, int w, int h,
                 unsigned char color_on, unsigned char color_off);
void drawBall(const Ball *b, unsigned char color);
void drawPaddle(const Paddle *p, unsigned char color);

#ifdef VGA_SIMULATION
void presentFrame(void);
#endif

#endif
