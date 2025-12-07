/*
  vga.c
  - Definierar pekaren till videominnet (vga_buffer).
  - På värdmaskin använder vi en allokerad buffer så programmet kan köras
    utan verklig VGA-hårdvara. På riktig hårdvara: definiera USE_REAL_VGA
    och sätt rätt basadress (VGA_BASE_ADDR).
*/
#include <stdint.h>
#include "graphics.h"

#ifndef VGA_BASE_ADDR
/* Standard basadress för University Program Pixel Buffer (SDRAM) på DE*-kort. */
#define VGA_BASE_ADDR 0x08000000
#endif

#ifdef USE_REAL_VGA
volatile unsigned short *vga_buffer = (volatile unsigned short*)VGA_BASE_ADDR; // byt vid behov
#else
static unsigned short host_vga_buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
volatile unsigned short *vga_buffer = host_vga_buffer;
#endif

/* Pixel Buffer DMA (University Program) register-mappning. */
#define VGA_DMA_BASE   0x04000100u
#define VGA_DMA_STAT   (*(volatile uint32_t*)(VGA_DMA_BASE + 0x00))
#define VGA_DMA_CTRL   (*(volatile uint32_t*)(VGA_DMA_BASE + 0x04))
#define VGA_DMA_BACK   (*(volatile uint32_t*)(VGA_DMA_BASE + 0x08))
#define VGA_DMA_RES    (*(volatile uint32_t*)(VGA_DMA_BASE + 0x0C))

void vga_init_dma(void) {
#ifdef USE_REAL_VGA
    VGA_DMA_RES  = (240u << 16) | 320u;   // H<<16 | W
    VGA_DMA_BACK = VGA_BASE_ADDR;         // back/front buffer start
    VGA_DMA_CTRL = 0x1;                   // trigger buffer swap (GO)
    while (VGA_DMA_STAT & 0x1) { /* wait for swap */ }
#endif
}
