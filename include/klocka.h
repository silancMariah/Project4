#ifndef KLOCKA_H
#define KLOCKA_H

void Tid();         // sätt timerlängd
void StartaTid();   // starta timern
void StoppaTid();   // stoppa timern
int TestaTimer();   // returnerar 1 om klar, 0 om inte
int getSecondElapsed(); // antal sekunder sedan start

#endif
