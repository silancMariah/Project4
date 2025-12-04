#include <stdio.h>
#include "klocka.h"
//Basfrekvensen hos TIMER 30MHz
#define BAS_FREK 30000000

//Skapar pekare för dessa register: periodL,periodH, Control, Status, SNAPL och SNAPH
volatile unsigned short *TMR1_PERLO = (unsigned short*) 0x04000028;
volatile unsigned short *TMR1_PERHI = (unsigned short*) 0x0400002c;
volatile unsigned short *TMR1_CTRL = (unsigned short*) 0x04000024;
volatile unsigned short *TMR1_STAT = (unsigned short*) 0x04000020;
volatile unsigned short *TMR1_SNAPL = (unsigned short*) 0x04000030;
volatile unsigned short *TMR1_SNAPH = (unsigned short*) 0x04000034;

//Aktuella timer-värde 
unsigned int current_timer = *(TMR1_SNAPL) | (*(TMR1_SNAPH) << 16);



/*Här bestämmer vi antal cyklar 30 skeunder motsvarar och
och sätter CONT=0 så att räknaren stoppas när den nått noll*/
void Tid(){
    /*Beräknar period vilket är basfrekvens 
    gånger 30 -1 (tar bort nollcykeln)*/
    unsigned int period=(BAS_FREK*30)-1;

    *(TMR1_PERLO) = period & 0xFFFF;
    *(TMR1_PERHI) = period >> 16;  
    // Bit 0=0
        *(TMR1_CTRL) = 0x0;
}

//Startar tiden
void StartaTid(){
    //lägger 0100 till TMR_CTRL
    *(TMR1_CTRL) |= 0x4;
}

//Stoppar tiden 
void StoppaTid(){
    //lägger till 1000 till TMR1_CTRL
    *(TMR1_CTRL) = *(TMR1_CTRL)| 0x8;
}

//Bestämer förflutna sekunder 
int getSecondElapsed(){
    
    unsigned int low = *TMR1_SNAPL;
    unsigned int high=*TMR1_SNAPH; 
    //Kombinerar låg och hög bitarna så att det blir sammanlagd 32 bitar
    unsigned int current = (high << 16) |low; 
    //Beräknar igen antal perioden
    unsigned int period = (BAS_FREK*30)-1; 
    //Antal cyklar som har passerats 
    unsigned int elapsed_cyklar= period-current; 
    //Returnerar antal sekunder som är förflutna
    return elapsed_cyklar /BAS_FREK;
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
