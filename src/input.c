/*
  input.c
  - Hantera knapp- eller joystickinput, mappa inmatning till movePaddle()
    eller spelkontroller.
  TODO:
  - Implementera pollInput() eller interrupt-baserad inläsning beroende på plattform.
*/

//Behöver första tio bitarna bara så låter den här läsa 16 bitar av 32 bitar
volatile unsigned short* switches = (volatile unsigned short*) 0x04000010;

void rörligaPaddlar(){
  //För att endast ha 10 bitar maskerar 6MSB bitarna
  unsigned short switchVal= *switches; 
  unsigned short tioSwitch= switchVal & 0x03FF;
  //flyttar vänstra paddeln neråt 
  if (tioSwitch & (1<<0)){
    move_paddle(&left,-5);
  }
  //flyttar vänstra paddeln uppåt
  else if(tioSwitch & (1<<1)){
    move_paddle(&left,5);
  }
  //Flyttar högra paddeln neråt
  if(tioSwitch & (1<<2)){
    move_paddle(&right,-5);
  }
  //FLyttar högra paddeln uppåt
  else if(tioSwitch & (1<<3)){
    move_paddle(&right,5);
  }
}

/*Switch som går upp/ner så länge switchen är på*/
