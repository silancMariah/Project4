#include <stdio.h>

// === LOKAL PRINT FÖR TERMINALSPRITES ===
void printSprite16(const unsigned char sprite[16][16]) {
    for(int r = 0; r < 16; r++){
        for(int c = 0; c < 16; c++){
            unsigned char px = sprite[r][c];
            switch(px) {
                case 0: printf("  "); break;      // bakgrund
                case 1: printf("██"); break;      // outline
                case 2: printf("▓▓"); break;      // ljus
                case 3: printf("▒▒"); break;      // mörkare
                case 4: printf(".."); break;      // ögon/markering
                case 5: printf("■■"); break;      // text
                case 6: printf("**"); break;      // highlight
                default: printf("??"); break;
            }
        }
        printf("\n");
    }
}


// === DIN SPRITE ===
static const unsigned char pig[16][16] = {
    {0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0},
    {0,0,1,2,3,3,1,1,0,0,1,1,3,2,1,0},
    {0,1,3,3,4,3,2,1,1,2,3,3,4,3,1,0},
    {1,3,4,4,3,3,3,2,2,3,3,3,4,4,3,1},
    {1,3,3,6,6,6,3,3,3,3,3,3,3,3,3,1},
    {1,3,3,3,6,6,3,3,3,3,4,4,3,3,3,1},
    {1,3,3,3,3,3,2,2,6,6,3,3,3,3,3,1},
    {1,3,3,3,2,2,2,3,3,3,3,2,2,3,3,1},
    {1,3,2,2,2,5,5,4,4,5,5,2,2,2,3,1},
    {1,3,2,2,5,5,4,4,4,4,5,5,2,2,3,1},
    {0,1,3,2,2,5,4,4,4,4,5,2,2,3,1,0},
    {0,0,1,3,3,6,6,6,3,3,3,3,3,1,0,0},
    {0,0,0,1,3,6,6,6,6,6,3,3,1,0,0,0},
    {0,0,0,0,1,3,6,6,6,3,3,1,0,0,0,0},
    {0,0,0,0,1,1,1,3,3,3,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0}
};

int main() {
    printSprite16(pig);
    return 0;
}
