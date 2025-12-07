#ifndef FLOWSTATE_H
#define FLOWSTATE_H

// enum för speltilstånd
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER
} GameState;

// Här säger vi att variabeln finns någonstans, men vi skapar den inte här!
extern GameState currentState;

// Funktioner som används överallt
void updateGame();
void renderGame();
void resetGame();

#endif
