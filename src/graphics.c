/*
  graphics.c
  - Låg-nivå grafikfunktioner: putPixel, clearScreen, drawRect, samt
    högre nivå funktioner som drawPaddle och drawBall (om du placerar dem här).
  TODO:
  - Se till att publicera prototyper i include/graphics.h.
  - Implementera drawPaddle() och drawBall() eller flytta deras deklarationer
    till lämplig header.
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ball.h"
#include "paddle.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
extern volatile unsigned char *vga_buffer;

#include "graphics.h"
#include <stddef.h>

/* Ritar ett binärt mönster (pattern är w*h element i rad-major).
   1 = rita color_on, 0 = hoppa eller rita color_off (använd 255 för transparent). */
void drawPattern(int x0, int y0, const int *pattern, int w, int h,
                 unsigned char color_on, unsigned char color_off)
{
    if (!pattern || w <= 0 || h <= 0) return;
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            int v = pattern[dy * w + dx];
            if (v)
                putPixel(x0 + dx, y0 + dy, color_on);
            else if (color_off != 255)
                putPixel(x0 + dx, y0 + dy, color_off);
        }
    }
}

/* Låg-nivå: skriv en pixel i videobuffern */
void putPixel(int x, int y, unsigned char color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    vga_buffer[y * SCREEN_WIDTH + x] = color;
}

void clearScreen(unsigned char color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            putPixel(x, y, color);
        }
    }
}

void drawRect(int x, int y, int w, int h, unsigned char color) {
    if (w <= 0 || h <= 0) return;
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            putPixel(x + dx, y + dy, color);
        }
    }
}

void drawBall(const Ball *b, unsigned char color) {
    if (!b) return;
    drawRect(b->x, b->y, b->size, b->size, color);
}

void drawPaddle(const Paddle *p, unsigned char color) {
    if (!p) return;
    drawRect(p->x, p->y, p->width, p->height, color);
}

#endif