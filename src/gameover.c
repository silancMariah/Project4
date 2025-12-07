#include "gameover.h"
#include "game.h"
#include "graphics.h"
#include "points.h"
#include "animation.h"
#include <string.h>
#include <stdio.h>


void drawGameOverScreen() {
    clearScreen(0); // svart
    drawSprite16(150, 150, GAME_OVER);
}
void drawTheWinner(){
    int winnerY = 75; // start y för vinnaren, under "OVER"
    int winnerX = 50;       // start x, justera efter smak
    //Om vänster vinner
    if (leftScore.value > rightScore.value){
        //LEFT
        drawLetter('L',winnerX+6,winnerY,14, 4);
        drawLetter('E',winnerX+12,winnerY,14, 4);
        drawLetter('F',winnerX+18,winnerY,14, 4);   
        drawLetter('T',winnerX+24,winnerY,14, 4);

        //WINS
        drawLetter('W',winnerX+36,winnerY,14, 4);
        drawLetter('I',winnerX+42,winnerY,14, 4);
        drawLetter('N',winnerX+48,winnerY,14, 4);
        drawLetter('S',winnerX+56,winnerY,14, 4);  
    }
    else if(rightScore.value > leftScore.value){
        //RIGHT
        drawLetter('R',winnerX +6,winnerY,14, 4);
        drawLetter('I',winnerX+12,winnerY,14, 4);
        drawLetter('G',winnerX +18,winnerY,14, 4);
        drawLetter('H',winnerX +24,winnerY,14, 4); 
        drawLetter('T',winnerX +30,winnerY,14, 4);

        //WINS
        drawLetter('W',winnerX+36,winnerY,14, 4);
        drawLetter('I',winnerX+42,winnerY,14, 4);
        drawLetter('N',winnerX+48,winnerY,14, 4);
        drawLetter('S',winnerX+56,winnerY,14, 4);   
    }
    else{
        //DRAW
        drawLetter('D',winnerX+6,winnerY,14, 4);
        drawLetter('R',winnerX+12,winnerY,14, 4);
        drawLetter('A',winnerX+18,winnerY,14, 4);   
        drawLetter('W',winnerX+24,winnerY,14, 4);
    }
}
