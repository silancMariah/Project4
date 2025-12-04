#include <stdio.h>
//Basfrekvensen hos TIMER 30MHz
#define BasFrekvens 30000000

//Skapar pekare för dessa register: periodL,periodH, Control och Status
volatile unsigned short *TMR1_PERLO = (unsigned short*) 0x04000028;
volatile unsigned short *TMR1_PERHI = (unsigned short*) 0x0400002c;
volatile unsigned short *TMR1_CTRL = (unsigned short*) 0x04000024;
volatile unsigned short *TMR1_STAT = (unsigned short*) 0x04000020;
volatile unsigned short *TMR1_COUNT = (unsigned short*) 0x0400002a;  // eller rätt adress


static int elapsed_seconds = 0;

int getSecondElapsed(){
    unsigned int current = *TMR1_COUNT;
    unsigned int period = (BasFrekvens * 30) - 1;
    unsigned int elapsed = period - current;
    return elapsed / BasFrekvens;
}

/*Här bestämmer vi antal cyklar 30 skeunder motsvarar och
och sätter CONT=0 så att räknaren stoppas när den nått noll*/
void Tid(){
    /*Beräknar period vilket är basfrekvens 
    gånger 30 -1 (tar bort nollcykeln)*/
    unsigned int period=(BasFrekvens*30)-1;

    *(TMR1_PERLO) = period & 0xFFFF;
    *(TMR1_PERHI) = period >> 16;  
    // Bit 0=0 => kör inte  
        *(TMR1_CTRL) = 0x0;
}


//Startar tiden
void StartaTid(){
    //lägger 001 till TMR_CTRL
    *(TMR1_CTRL) |= 0x4;
}

//Stoppar tiden 
void StoppaTid(){
    //lägger till 1000 till TMR1_CTRL
    *(TMR1_CTRL) = *(TMR1_CTRL)| 0x8;
}

//Ser om timern fungerar 
int TestaTimer(){
    //Timern är klar 
   
    if((*TMR1_STAT) & 0x1){
        (*TMR1_STAT)=0;
        return(1);
    }
    else 
    //Timern är inte klar 
    return(0);
}


int main(){
    Tid(); 
    printf("Startar tiden..\n"); 

    StartaTid();
    while(1) {
    if (TestaTimer()) {
        printf("Timern är klar!\n");
        break;
    }
    // Annan spel-logik kan köras här
    }  
    return 0;
}

