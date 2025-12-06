#include "timer.h"
#include "graphics.h"
#include "klocka.h"
#include "points.h"

void initTimerDisplay(TimerDisplay *t, int startValue, int x, int y) {
    if (!t) return;
    t->value = startValue;
    t->x = x;
    t->y = y;
}

void updateTimerDisplay(TimerDisplay *t) {
    if (!t) return;
    t->value = getSecondElapsed();  // hämta tid från hårdvarutimern
}

void drawTimerDisplay(const TimerDisplay *t) {
    if (!t) return;
    int sec = t->value;
    int tens = (sec / 10) % 10;    // tiotal
    int ones = sec % 10;           // ental
    
    drawDigits(tens, t->x, t->y);
    drawDigits(ones, t->x + 4, t->y);  // offset för andra siffran
}

void tickTimerDisplay(TimerDisplay *t) {
    // Uppdatera det cacheade värdet; kan bytas mot egen logik vid behov
    updateTimerDisplay(t);
}

void resetTimerDisplay(TimerDisplay *t) {
    if (!t) return;
    t->value = 0;
}
