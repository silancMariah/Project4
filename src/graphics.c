#include "graphics.h"
#include "paddle.h"
#include "ball.h"

void drawRect(int x, int y, int width, int height, int color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setPixel(x + i, y + j, color);
        }
    }
}

drawRect(paddle.x, paddle.y, paddle.width, paddle.height, COLOR_WHITE);

drawRect(ball.x, ball.y, ball.size, ball.size, COLOR_WHITE);
