#include "rainball.h"
#include "graphics.h"
#include <stdlib.h>

#define MAX_RAIN 12

RainBall rain[MAX_RAIN];

void initRain() {
    for (int i = 0; i < MAX_RAIN; i++) {
        rain[i].x = rand() % 144;    // random bred på skärmen (exempel)
        rain[i].y = -(rand() % 50);  // börjar ovanför skärmen
        rain[i].speed = 1 + rand() % 3; // slumpad hastighet
    }
}

void updateRain() {
    for (int i = 0; i < MAX_RAIN; i++) {
        rain[i].y += rain[i].speed;

        if (rain[i].y > 160) {              // om utanför skärmen (exempel höjd)
            rain[i].x = rand() % 144;
            rain[i].y = -(rand() % 30);
        }
    }
}

void drawRain() {
    for (int i = 0; i < MAX_RAIN; i++) {
        drawBall(rain[i].x, rain[i].y);
    }
}
