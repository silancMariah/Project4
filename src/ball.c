/*
  ball.c
  - Implementera bollens uppföljning: updateBall(), kollisionshantering,
    studs mot paddlar och väggar.
  TODO:
  - Använd Ball-strukturen från include/ball.h.
  - Uppdatera dx/dy vid kollision och hantera poäng när bollen passerar ändarna.
*/

#include "ball.h"
#include "graphics.h"

const int pat[16]= {
    1,0,0,1,
    0,1,1,0,
    0,1,1,0,
    1,0,0,1
};    

void drawBallPattern(int x, int y){
    /* använd de faktiska parametrarna x,y så varningsfri */
    drawPattern(x, y, pat, 4, 4, 7 /*on*/, 0 /*off*/); 
}

void updateBall(Ball* b) {
    if (!b) return;

    b->x += b->dx;
    b->y += b->dy;

    if (b->y <= 0 || b->y + b->size >= SCREEN_HEIGHT) {
        b->dy = -b->dy;
    }

    if (b->x <= 0 || b->x + b->size >= SCREEN_WIDTH) {
        b->dx = -b->dx;
    }
}