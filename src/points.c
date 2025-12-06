#include "graphics.h"
#include "points.h"

/* Pixelmasker för siffrorna 0-9 (5 rader x 3 kolumner). */
static const int digits[10][5][3] = {
    {{1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}}, // 0
    {{0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0}}, // 1
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}}, // 2
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}, // 3
    {{1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}}, // 4
    {{1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}, // 5
    {{1, 0, 0},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}}, // 6
    {{1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 1, 0},
     {1, 0, 0}}, // 7
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}}, // 8
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}}  // 9
};

void drawDigits(int digit, int x, int y)
{
    if (digit < 0 || digit > 9) return;

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            if (digits[digit][row][col] == 1) {
                putPixel(x + col, y + row, 15); // ritad med färg 15
            }
        }
    }
}

void initScore(Score *score, int x, int y)
{
    if (!score) return;
    score->value = 0;
    score->x = x;
    score->y = y;
}

void updateScore(Score *score)
{
    if (!score) return;
    score->value++;
}

void drawScore(const Score *score)
{
    if (!score) return;
    int value = score->value;
    int tens = (value / 10) % 10; // två siffror räcker
    int ones = value % 10;

    drawDigits(tens, score->x, score->y);
    drawDigits(ones, score->x + 4, score->y); // offset i pixlar
}
