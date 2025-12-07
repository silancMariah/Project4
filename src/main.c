#include "graphics.h"
#include "paddle.h"
#include "ball.h"
#include "game.h"
#include "gameover.h"
#include "points.h"
#include "klocka.h"
#include "timer.h"
#include <stdint.h>

/* Enkel delay för att synas på hårdvara. Justera vid behov. */
static void delay(void) {
  for (volatile int i = 0; i < 200000; i++) { }
}

/* Enkel AI som följer bollen vertikalt. */
static void trackBall(Paddle *p, const Ball *ball, int speed) {
  if (!p || !ball) return;
  int center = p->y + p->height / 2;
  if (ball->y > center) {
    movePaddle(p, speed);
  } else if (ball->y < center) {
    movePaddle(p, -speed);
  }
}

int main(void) {
  Paddle left = {10, SCREEN_HEIGHT / 2 - 30, 6, 60};
  Paddle right = {SCREEN_WIDTH - 16, SCREEN_HEIGHT / 2 - 30, 6, 60};
  Ball ball = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 1, 8};
  TimerDisplay timer;

  Tid();
  StartaTid();
  vga_init_dma();                /* initiera VGA-DMA på hårdvara */
  initTimerDisplay(&timer, 0, SCREEN_WIDTH / 2 - 6, 4);
  initGameScore();

  while (1) {
    clearScreen(0);              /* svart bakgrund */

    /* Rita objekt */
    drawPaddle(&left, 0xFFFF);
    drawPaddle(&right, 0xFFFF);
    drawBallPattern(ball.x, ball.y);
    drawScore(&leftScore);
    drawScore(&rightScore);
    updateTimerDisplay(&timer);
    drawTimerDisplay(&timer);

    /* Uppdatera spelstate */
    updateBall(&ball);
    updateCollision(&ball, &left, &right);
    handleScore(&ball);
    trackBall(&left, &ball, 2);
    trackBall(&right, &ball, 2);

#ifdef VGA_SIMULATION
    presentFrame();
#endif
    delay();
  }
  return 0;
}
