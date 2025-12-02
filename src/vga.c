/*
  vga.c
  - Definierar pekaren till videominnet (vga_buffer).
  TODO:
  - Se över rätt adress/initialisering för din målplattform.
  - Håll den som extern i headers där grafikfunktioner behöver den.
*/
volatile unsigned char *vga_buffer = (volatile unsigned char*)0xA0000; // eller rätt adress/initialisering för ditt system