/*
  ball.h
  - Definition av Ball och publika funktioner som updateBall().
  TODO:
  - Lägg till include guards (finns redan) och eventuella helpers.
*/
#ifndef BALL_H
#define BALL_H

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int size;
} Ball;

void updateBall(Ball* b);
void drawBallPattern(int x, int y);
void printBall();


#endif
