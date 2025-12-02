/*
  game.c
  - Ansvarar för spel-logik: initiering av spelstate, hantera kollisioner,
    att uppdatera paddlar och boll, poängräkning och eventuellt meny/paus.
  TODO:
  - Implementera initGame(), updateGame(), handleInput() och eventuella
    hjälpfunktioner för kollisionsdetektion.
  - Anropa rendering via draw-funktioner (drawPaddle, drawBall) från main.c.
*/
#include "graphics.h"
#include "paddle.h"
#include "ball.h"

/* Returnerar 1 om bollen (b) överlappar paddeln (p), annars 0 */
int ballTouch(const Ball *b, const Paddle *p) {
    if (!b || !p) return 0;  // safety-check

    int bx1 = b->x;
    int by1 = b->y;
    int bx2 = b->x + b->size;
    int by2 = b->y + b->size;

    int px1 = p->x;
    int py1 = p->y;
    int px2 = p->x + p->width;
    int py2 = p->y + p->height;

    if (bx2 <= px1) return 0; // boll helt till vänster om paddel
    if (bx1 >= px2) return 0; // boll helt till höger om paddel
    if (by2 <= py1) return 0; // boll helt ovanför paddel
    if (by1 >= py2) return 0; // boll helt under paddel

    return 1; // annars: överlapp
}

