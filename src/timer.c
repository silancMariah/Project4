#include "timer.h"
#include "graphics.h"
#include "klocka.h"

void initTimerDisplay(TimerDisplay *t, int x, int y) {
    if (!t) return;
    t->x = x;
    t->y = y;
}

void drawTimerDisplay(TimerDisplay *t) {
    if (!t) return;
    int sec = getSecondElapsed();  // få sekunder från timern
    int tens = (sec / 10) % 10;    // tiotal
    int ones = sec % 10;            // ental
    
    drawDigits(tens, t->x, t->y);
    drawDigits(ones, t->x + 4, t->y);  // offset för andra siffran
}

void updateTimerDisplay(TimerDisplay* t) {
    // Denna funktion kan användas för att uppdatera timer-displayen
    // om det behövs ytterligare logik i framtiden.
    if
}