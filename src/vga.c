/*
  vga.c
  - Definierar pekaren till videominnet (vga_buffer).
  - Använder faktisk VGA-adress som standard, men har ett simuleringsläge
    där en intern buffer används.
*/
#include "graphics.h"

#ifndef VGA_BASE_ADDR
#define VGA_BASE_ADDR 0x08000000
#endif

#ifdef VGA_SIMULATION
static unsigned char vga_memory[SCREEN_WIDTH * SCREEN_HEIGHT];
volatile unsigned char *vga_buffer = vga_memory;
#else
volatile unsigned char *vga_buffer = (volatile unsigned char *)VGA_BASE_ADDR;
#endif
