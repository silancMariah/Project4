#ifndef POINTS_H
#define POINTS_H

typedef struct {
    int value; 
    int x;
    int y;
} Score;

void drawDigits(int digit, int x, int y);
void initScore(Score* score, int x, int y);
void updateScore(Score* score);
void drawScore(const Score* score);
#endif
