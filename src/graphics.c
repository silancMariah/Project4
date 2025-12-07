/*
  graphics.c
  - Låg-nivå grafikfunktioner: putPixel, clearScreen, drawRect, samt
    högre nivå funktioner som drawPaddle och drawBall (om du placerar dem här).
  TODO:
  - Se till att publicera prototyper i include/graphics.h.
  - Implementera drawPaddle() och drawBall() eller flytta deras deklarationer
    till lämplig header.
*/

#include "ball.h"
#include "paddle.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
extern volatile unsigned short *vga_buffer;

#include "graphics.h"
#include <stddef.h>
#include <stdint.h>
#ifdef VGA_SIMULATION
#include <stdio.h>
#endif

/* Ritar ett binärt mönster (pattern är w*h element i rad-major).
   1 = rita color_on, 0 = hoppa eller rita color_off (använd 255 för transparent). */
void drawPattern(int x0, int y0, const int *pattern, int w, int h,
                 unsigned short color_on, unsigned short color_off)
{
    if (!pattern || w <= 0 || h <= 0) return;
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            int v = pattern[dy * w + dx];
            if (v)
                putPixel(x0 + dx, y0 + dy, color_on);
            else if (color_off != 0xFFFF)
                putPixel(x0 + dx, y0 + dy, color_off);
        }
    }
}

/* Låg-nivå: skriv en pixel i videobuffern */
void putPixel(int x, int y, unsigned short color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    vga_buffer[y * SCREEN_WIDTH + x] = color;
}

void clearScreen(unsigned short color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            putPixel(x, y, color);
        }
    }
}

void drawRect(int x, int y, int w, int h, unsigned short color) {
    if (w <= 0 || h <= 0) return;
    for (int dy = 0; dy < h; dy++) {
        for (int dx = 0; dx < w; dx++) {
            putPixel(x + dx, y + dy, color);
        }
    }
}

void drawPaddle(const Paddle *p, unsigned short color) {
    if (!p) return;
    drawRect(p->x, p->y, p->width, p->height, color);
}

/* Enkel testbild: lodräta färgränder över hela skärmen. */
void drawTestPattern(void) {
    static const unsigned short palette[16] = {
        0x0000, // svart
        0xF800, // röd
        0x07E0, // grön
        0x001F, // blå
        0xFFE0, // gul
        0xF81F, // magenta
        0x07FF, // cyan
        0xFFFF, // vit
        0x7BEF, // ljusgrå
        0x4208, // mörkgrå
        0xFC00, // orange-ish
        0x83E0, // oliv
        0x841F, // lila
        0x03E0, // ljusgrön
        0x0010, // mörkblå
        0x7C00  // mörkröd
    };
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            unsigned short color = palette[(x / 20) & 0xF];
            putPixel(x, y, color);
        }
    }
}

#ifdef VGA_SIMULATION
/* Enkel terminal-presenterare: sampelar ned bufferten och skriver ASCII. */
void presentFrame(void)
{
    static int first = 1;
    const int cellW = 4;
    const int cellH = 4;
    static const char shades[] = " .:-=+*#%@";
    const int shadeLevels = (int)(sizeof(shades) - 1);

    if (first)
    {
        printf("\033[2J");
        first = 0;
    }
    printf("\033[H");

    for (int y = 0; y < SCREEN_HEIGHT; y += cellH)
    {
        for (int x = 0; x < SCREEN_WIDTH; x += cellW)
        {
            int sum = 0;
            for (int dy = 0; dy < cellH; dy++)
            {
                for (int dx = 0; dx < cellW; dx++)
                {
                    unsigned short raw = vga_buffer[(y + dy) * SCREEN_WIDTH + (x + dx)];
                    int intensity = (raw & 0xFFFF) >> 8; // ta högre byte som luminans
                    if (intensity > 255)
                        intensity = 255;
                    sum += intensity;
                }
            }
            int avg = sum / (cellW * cellH);
            int idx = (avg * (shadeLevels - 1)) / 255;
            if (idx < 0) idx = 0;
            if (idx >= shadeLevels) idx = shadeLevels - 1;
            putchar(shades[idx]);
        }
        putchar('\n');
    }
    fflush(stdout);
}
#endif
