/*
  game.c
  - Ansvarar för spel-logik: initiering av spelstate, hantera kollisioner,
    att uppdatera paddlar och boll, poängräkning och eventuellt meny/paus.
  TODO:
  - Implementera initGame(), updateGame(), handleInput() och eventuella
    hjälpfunktioner för kollisionsdetektion.
  - Anropa rendering via draw-funktioner (drawPaddle, drawBall) från main.c.
*/
#include "game.h"
#include "graphics.h"
#include <stdlib.h>

//Ökar poängen av varje spelare 
Score leftScore; 
Score rightScore; 

void initGameScore(){
  initScore(&leftScore,50,10);
  initScore(&rightScore,200,10);
}

/* Lägg bollen i mitten och sätt riktningen för nästa serve. direction>0 => höger, <0 => vänster */
static void resetBall(Ball *ball, int direction)
{
    if (!ball) return;

    ball->x = SCREEN_WIDTH / 2 - ball->size / 2;
    ball->y = SCREEN_HEIGHT / 2 - ball->size / 2;

    /* säkerställ ett rimligt fartvärde på x-axeln */
    int speedX = ball->dx == 0 ? 1 : abs(ball->dx);
    ball->dx = (direction >= 0) ? speedX : -speedX;

    /* lämna y-farten som positiv om den var noll så bollen alltid rör sig */
    if (ball->dy == 0) ball->dy = 1;
}

void handleScore(Ball *ball){
  if (!ball) return; 

  if (ball->x <= 0){
    updateScore(&rightScore);
    resetBall(ball, -1); // serva mot vänster efter poäng för höger
  }
  else if (ball->x + ball->size >= SCREEN_WIDTH){
    updateScore(&leftScore);
    resetBall(ball, 1); // serva mot höger efter poäng för vänster
  }

}
/* Returnerar 1 om bollen (b) överlappar paddeln (p), annars 0 */
//Denna funktion kontroller om bollen träffar paddlar 
int ballTouch(const Ball *b, const Paddle *p) {
    if (!b || !p) return 0;  // safety-check

    int bollVänster = b->x;
    int bollTopp = b->y;
    int bollHöger = b->x + b->size;
    int bollBotten = b->y + b->size;
  
//Samma sak för paddeln 
    int paddelVänster = p->x;
    int paddelTopp = p->y;
    int paddelHöger = p->x + p->width;
    int paddelBotten = p->y + p->height;

    if (bollHöger <= paddelVänster) return 0; // boll helt till vänster om paddel
    if (bollVänster >= paddelHöger) return 0; // boll helt till höger om paddel
    if (bollBotten <= paddelTopp) return 0; // boll helt ovanför paddel
    if (bollTopp >= paddelBotten) return 0; // boll helt under paddel

    return 1; // annars: överlapp
}

//Ändrar bollens riktningen när den träffar paddel
void updateCollision(Ball* ball, Paddle* left, Paddle* right){
  if (!ball || !left || !right)return; 
  
  if (ballTouch(ball, left)){
    ball->dx= -ball->dx; 
    ball->x = left->x + left->width; // flytta utanför paddeln för att undvika fastlåsning
  }

   if (ballTouch(ball,right)){
    ball->dx=-ball->dx; 
    ball->x = right->x - ball->size;
   }
}

int playerLost() {
    // välj max‐score (ex. först till 5 poäng)
    int MAX_SCORE = 5;

    if (leftScore.value >= MAX_SCORE) return 1;
    if (rightScore.value >= MAX_SCORE) return 1;

    return 0;
}
