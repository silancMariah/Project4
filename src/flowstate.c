
#include "rendergame.h"
#include "graphics.h"
#include "game.h"
#include "animation.h"

void updateGame()
{
    switch (currentState)
    {
    case STATE_MENU:
        updateRain();
        if (buttonStartPressed())
            currentState = STATE_PLAYING;
        break;

    case STATE_PLAYING:
        updatePong(); // uppdaterar paddlar, boll, poäng
        if (playerLost())
            currentState = STATE_GAMEOVER;
        break;

    case STATE_GAMEOVER:
        updateGameOver(); // t.ex blink, regn, etc
        if (buttonStartPressed())
            resetGame();
        break;
    }
}


void renderGame()
{
    clearScreen();

    switch (currentState)
    {
    case STATE_MENU:
        drawMenu();
        break;

    case STATE_PLAYING:
        drawPongGameplay();
        break;

    case STATE_GAMEOVER:
        drawGameOverScreen();
        break;
    }

    swapBuffers();
}

void drawMenu()
{
    drawPong(SCREEN_WIDTH / 2 - 40, 20);
    drawPlayButton(SCREEN_WIDTH / 2 - 16, 100, 0); // 0 = inte nedtryckt
    drawRainBalls();                               // dekor
}

void drawPongGameplay()
{
    drawPaddle(&leftPaddle, 7);
    drawPaddle(&rightPaddle, 7);
    drawBallPattern(ball.x, ball.y);
    drawScore(&leftScore);
    drawScore(&rightScore);
}

void drawGameOverScreen()
{
    drawSpite16(60, 30, HEART); // dekoration
    drawSpite16();  // t.ex. LEFT WINS, DRAW
    drawPlayButton(60, 100, 0);
    drawRainBalls();   // använd regnets rendering!
    drawSpite16
}


}

void drawGameOverScreen()
{
    drawHeart(60, 30); // cute decoration?
    drawTeddy(80, 50); // kan också bytas
    drawPlayButton(60, 100, 0);
    drawStopButton(140, 100, 0);
    drawRain();
}
