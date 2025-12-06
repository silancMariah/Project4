#include <stdio.h>
#include <time.h>
#include "klocka.h"

/* If you compile on hardware with the real timer, define USE_REAL_TIMER.
   Otherwise a host-safe software timer is used so the program can run
   without accessing memory-mapped IO. */
#ifdef USE_REAL_TIMER

//Basfrekvensen hos TIMER 30MHz
#define BAS_FREK 30000000

#ifndef TIMER_BASE_ADDR
#define TIMER_BASE_ADDR 0x04000020
#endif

//Register-offsets (från STATUS-registret som bas)
#define TMR_STAT_ADDR  (TIMER_BASE_ADDR + 0x0)
#define TMR_CTRL_ADDR  (TIMER_BASE_ADDR + 0x4)
#define TMR_PERLO_ADDR (TIMER_BASE_ADDR + 0x8)
#define TMR_PERHI_ADDR (TIMER_BASE_ADDR + 0xC)
#define TMR_SNAPL_ADDR (TIMER_BASE_ADDR + 0x10)
#define TMR_SNAPH_ADDR (TIMER_BASE_ADDR + 0x14)

#define REG16(addr) ((volatile unsigned short *)(addr))

//Skapar pekare för dessa register: periodL,periodH, Control, Status, SNAPL och SNAPH
static volatile unsigned short *TMR1_PERLO = REG16(TMR_PERLO_ADDR);
static volatile unsigned short *TMR1_PERHI = REG16(TMR_PERHI_ADDR);
static volatile unsigned short *TMR1_CTRL = REG16(TMR_CTRL_ADDR);
static volatile unsigned short *TMR1_STAT = REG16(TMR_STAT_ADDR);
static volatile unsigned short *TMR1_SNAPL = REG16(TMR_SNAPL_ADDR);
static volatile unsigned short *TMR1_SNAPH = REG16(TMR_SNAPH_ADDR);

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
    // nollställ statusflaggan innan start så vi inte ser en gammal timeout
    *TMR1_STAT = 0;
    //lägg till 0100 till TMR_CTRL
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

#else

/* Host-safe software timer (monotonic clock) so the game can run without
   real hardware registers. */
static struct timespec start_time;
static int running = 0;

void Tid(){
    running = 0;
}

//Startar tiden
void StartaTid(){
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    running = 1;
}

//Stoppar tiden 
void StoppaTid(){
    running = 0;
}

//Bestämer förflutna sekunder 
int getSecondElapsed(){
    if (!running) return 0;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    time_t sec = now.tv_sec - start_time.tv_sec;
    long nsec = now.tv_nsec - start_time.tv_nsec;
    if (nsec < 0) { sec -= 1; nsec += 1000000000L; }
    return (int)sec;
}

//Ser om timern fungerar 
int TestaTimer(){
    if (!running) return 0;
    return getSecondElapsed() >= 30; // signalera klar efter 30 sekunder
}

#endif
