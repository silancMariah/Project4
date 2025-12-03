#include graphics.h
#include points.h

void drawDigits(int digit, int x, int y)
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (degits[degit][row][col] == 1)
            {
                putPixel(x + col, y + row, 15); // x och y är startpositionen
            }
        }
    }
}

static const int digits[10][5][3] = {
    {// 0
     {1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {// 1
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0}},
    {// 2
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}},
    {// 3
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {// 4
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}},
    {// 5
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {// 6
     {1, 0, 0},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {// 7
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 1, 0},
     {1, 0, 0}},
    {// 8
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {// 9
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}}};

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
    score→ value++;
}
}

void drawScore(const Score *score)
{
    if (!score)
        return;
    int tens = value / 10; // så vi kan visa tvåsiffrigt
    int ones = value % 10;

    drawDigit(tens, score->x, score->y);
    drawDigit(ones, score->x + 4, score->y); // offset i pixlar
}
