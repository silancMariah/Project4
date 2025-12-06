/*
  ball.c
*/

#include "ball.h"
#include "graphics.h"
#include <stdio.h>

static const unsigned char PONG_BALL[8][8] = {
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 2, 2, 1, 0, 0},
    {0, 1, 2, 3, 3, 2, 1, 0},
    {1, 2, 3, 3, 3, 3, 2, 1},
    {1, 2, 3, 3, 3, 3, 2, 1},
    {0, 1, 2, 3, 3, 2, 1, 0},
    {0, 0, 1, 2, 2, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}};

unsigned short ballColors[5] = {
    0x0000, // 0 transparent
    0x0000, // 1 svart outline
    0xFFFF, // 2 vit
    0xC618, // 3 ljusgrå
    0x8410  // 4 mörkgrå
};

void drawBallSprite(int x, int y)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            unsigned char px = PONG_BALL[r][c];
            if (px != 0)
                putPixel(x + c, y + r, ballColors[px]);
        }
    }
}

void drawBallPattern(int x, int y)
{
    drawBallSprite(x, y);
}

void updateBall(Ball *b)
{
    if (!b)
        return;

    b->x += b->dx;
    b->y += b->dy;

    if (b->y <= 0 || b->y + b->size >= SCREEN_HEIGHT)
    {
        b->dy = -b->dy;
    }

    if (b->x <= 0 || b->x + b->size >= SCREEN_WIDTH)
    {
        b->dx = -b->dx;
    }
}

void printBall()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            unsigned char px = PONG_BALL[r][c];

            if (px == 0)
            {
                printf("  "); // transparent
            }
            else if (px == 1)
            {
                printf("\x1b[30m██\x1b[0m"); // svart
            }
            else if (px == 2)
            {
                printf("\x1b[97m██\x1b[0m"); // vit
            }
            else if (px == 3)
            {
                printf("\x1b[37m██\x1b[0m"); // ljusgrå
            }
            else if (px == 4)
            {
                printf("\x1b[90m██\x1b[0m"); // mörkgrå
            }
        }
        printf("\n");
    }
}
