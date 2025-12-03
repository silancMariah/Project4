
#ifndef TIMER_H
#define TIMER_H

typedef struct {
    int value;   // sekunder kvar
    int x;
    int y;
} TimerDisplay;

  
void initTimerDisplay(TimerDisplay* t, int startValue, int x, int y);
void updateTimerDisplay(TimerDisplay* t);
void drawTimerDisplay(const TimerDisplay* t);
void tickTimerDisplay(TimerDisplay* t);
void resetTimerDisplay(TimerDisplay* t);


#endif