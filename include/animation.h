#ifndef ANIMATION_H
#define ANIMATION_H

void printSprite16(const unsigned char sprite[16][16]);
void drawPig(int x, int y);
void drawHeart(int x, int y);
void drawButton16(int x, int y, const unsigned char btn[16][16]);
void drawPlayButtonUp(int x, int y);
void drawPlayButtonDown(int x, int y);
void drawStopButtonDown(int x, int y);
void drawPauseButtonDown(int x, int y);
void drawStopButtonUp(int x, int y);
void drawPauseButtonUp(int x, int y);

/* Convenience wrappers that pick the correct button frame. */
void drawPlayButton(int x, int y, int pressed);
void drawStopButton(int x, int y, int pressed);
void drawPauseButton(int x, int y, int pressed);

#endif
