/*
  paddle.c
  - Innehåller implementationer för Paddle-relaterade funktioner.
  TODO:
  - movePaddle() finns här; lägg till eventuella helpers som clampPaddlePosition().
  - Om drawPaddle() finns, fundera på att implementera här eller i graphics.c.
*/
#include "paddle.h"
#include "graphics.h"

/* Flytta paddeln med delta pixlar (positivt = ner, negativt = upp).
   Funktionen uppdaterar bara position och håller paddeln inom skärmen. */
void movePaddle(Paddle *p, int delta)
{
    if (!p)
        return;

    p->y += delta;

    /* Klampa inom skärmen */
    if (p->y < 0)
    {
        p->y = 0;
    }
    if (p->y > SCREEN_HEIGHT - p->height)
    {
        p->y = SCREEN_HEIGHT - p->height;
    }
}


}
