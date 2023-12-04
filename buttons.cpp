#include "buttons.h"

void initButtonsAndButtonInterrupts(void)
{
  //asetetaan nappien portit input_pullupeiksi ja laitetaan nappien keskeytykset päälle
    pinMode(2, INPUT_PULLUP);
  	pinMode(3, INPUT_PULLUP);
  	pinMode(4, INPUT_PULLUP);
  	pinMode(5, INPUT_PULLUP);
  	pinMode(6, INPUT_PULLUP);
  
  	PCICR |= B00000100;
  	PCMSK2 |= B01111100;
}