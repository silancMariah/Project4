#include "paddle.h"

void movePaddle(Paddle* p, int direction) {
    p->y += direction;
}
