#include "timer.h"
#include "klocka.h"
#include "points.h"

void initTimerDisplay(TimerDisplay *t, int x, int y)
{
    if (!t)
        return;
    t->value = 0;
    t->x = x;
    t->y = y;
}

void updateTimerDisplay(TimerDisplay *t)
{
    if (!t)
        return;
    t->value = getSecondElapsed();
}

void drawTimerDisplay(const TimerDisplay *t)
{
    if (!t)
        return;

    int value = t->value;
    int tens = (value / 10) % 10;
    int ones = value % 10;

    drawDigit(tens, t->x, t->y);
    drawDigit(ones, t->x + 4, t->y);
}

void tickTimerDisplay(TimerDisplay *t)
{
    if (!t)
        return;
    t->value++;
}

void resetTimerDisplay(TimerDisplay *t)
{
    if (!t)
        return;
    t->value = 0;
}
