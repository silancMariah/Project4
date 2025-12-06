#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "paddle.h"
#include "points.h"

extern Score leftScore;
extern Score rightScore;

void initGameScore(void);
void handleScore(Ball *ball);
int ballTouch(const Ball *b, const Paddle *p);
void updateCollision(Ball *ball, Paddle *left, Paddle *right);

#endif
