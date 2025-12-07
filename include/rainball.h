#ifndef RAINBALL_H
#define RAINBALL_H

typedef struct {
    int x;
    int y;
    int speed;
} RainBall;

void initRain();      // skapa flera bollar
void updateRain();    // flytta bollarna
void drawRain();      // rita dem

#endif
