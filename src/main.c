/*
  main.c
  - Programstart: initiera spelobjekt, loopa game-update och rendering.
  TODO:
  - Flytta så lite logik som möjligt från main: använd game.c för uppdateringar
    och graphics.c för rendering.
  - Hantera input via input.c och anropa movePaddle().
*/
#include "graphics.h"
#include "paddle.h"
#include "ball.h"
#include "game.h"
#include "points.h"
#include "klocka.h"
#include "timer.h"
/* drawBallPattern finns i ball.c men deklareras inte i ball.h */
void drawBallPattern(int x, int y);

/* Minimal delay så man kan se rörelser (justera vid behov) */
static void delay(void)
{
  for (volatile int i = 0; i < 200000; i++)
  { /* enkel busy-wait */
  }
}

int main(void)
{
  Paddle left = {20, 200, 10, 60};
  Paddle right = {290, 200, 10, 60};
  Ball ball = {160, 120, 1, 1, 5};
  TimerDisplay timer;
  Tid(); // initialisera timern
  StartaTid();
  initTimerDisplay(&timer, 10, 10); // position på skärmen

  while (1)
  {
    clearScreen(0);       // rensa skärmen
    drawPaddle(&left, 7); // rita paddlar med färg 7
    drawPaddle(&right, 7);
    drawBallPattern(ball.x, ball.y); // rita bollmönstret
    updateBall(&ball);
    updateCollision(&ball, &left, &right);
    handleScore(&ball);
    drawScore(&leftScore);
    drawScore(&rightScore);
    drawTimerDisplay(&timer);
    // uppdatera bollens position
    delay();
    if (TestaTimer()))
      {
        break;
      }
  }

  return 0;
}
