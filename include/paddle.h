/*
  paddle.h
  - Definition av Paddle-strukturen och publika paddle-funktioner.
  TODO:
  - Lägg till include guards om inte redan där, och deklarera alla publika
    funktioner (drawPaddle om du implementerar den externt).
*/

#ifndef PADDLE_H
#define PADDLE_H
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Paddle;

void movePaddle(Paddle* p, int delta);

#endif