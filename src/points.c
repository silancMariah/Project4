#include "graphics.h"
#include "points.h"

#define DIGIT_WIDTH 3
#define DIGIT_HEIGHT 5
#define DIGIT_COLOR 15

/* 3x5 representation av siffror 0-9 */
static const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = {
    {{1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {{0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0}},
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}},
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {{1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}},
    {{1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {{1, 0, 0},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {{1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 1, 0},
     {0, 1, 0}},
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}}};

void drawDigit(int digit, int x, int y)
{
    if (digit < 0 || digit > 9)
        return;

    for (int row = 0; row < DIGIT_HEIGHT; row++)
    {
        for (int col = 0; col < DIGIT_WIDTH; col++)
        {
            if (digits[digit][row][col])
            {
                putPixel(x + col, y + row, DIGIT_COLOR);
            }
        }
    }
}

void initScore(Score *score, int x, int y)
{
    if (!score)
        return;

    score->value = 0;
    score->x = x;
    score->y = y;
}

void updateScore(Score *score)
{
    if (!score)
        return;
    score->value++;
}

void drawScore(const Score *score)
{
    if (!score)
        return;

    int tens = (score->value / 10) % 10;
    int ones = score->value % 10;

    drawDigit(tens, score->x, score->y);
    drawDigit(ones, score->x + DIGIT_WIDTH + 1, score->y);
}
