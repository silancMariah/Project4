#ifndef ANIMATION_H
#define ANIMATION_H

/* Enkla sprite-hjälpare som används för att rita dekorativa element. */
void drawPig(int x, int y);
void drawHeart(int x, int y);

/* Generisk helper för 16x16-knappar och färdiga PLAY/STOP/PAUSE-varianter. */
void drawButton16(int x, int y, const unsigned char btn[16][16]);
void drawPlayButton(int x, int y, int pressed);
void drawStopButton(int x, int y, int pressed);
void drawPauseButton(int x, int y, int pressed);

#endif
