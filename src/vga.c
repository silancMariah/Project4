/*
  vga.c
  - Definierar pekaren till videominnet (vga_buffer).
  - På värdmaskin använder vi en allokerad buffer så programmet kan köras
    utan verklig VGA-hårdvara. På riktig hårdvara: definiera USE_REAL_VGA
    och sätt rätt basadress (VGA_BASE_ADDR).
*/
#include "graphics.h"

#ifndef VGA_BASE_ADDR
#define VGA_BASE_ADDR 0xA0000
#endif

#ifdef USE_REAL_VGA
volatile unsigned char *vga_buffer = (volatile unsigned char*)VGA_BASE_ADDR; // byt vid behov
#else
static unsigned char host_vga_buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
volatile unsigned char *vga_buffer = host_vga_buffer;
#endif
