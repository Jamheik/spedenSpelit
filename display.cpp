#include "display.h"
  const int serialInput_pin = 8; 
	const int outEnable_pin = 9; 
	const int latchClock_pin = 10; 
	const int shiftClock_pin = 11;
	const int reset_pin = 12;
  int digits[10][8] = {
  	{0, 0, 0, 0, 0, 0, 1, 1}, // digit 0
  	{1, 0, 0, 1, 1, 1, 1, 1}, // digit 1
  	{0, 0, 1, 0, 0, 1, 0, 1}, // digit 2
  	{0, 0, 0, 0, 1, 1, 0, 1}, // digit 3
  	{1, 0, 0, 1, 1, 0, 0, 1}, // digit 4
  	{0, 1, 0, 0, 1, 0, 0, 1}, // digit 5
  	{0, 1, 0, 0, 0, 0, 0, 1}, // digit 6
  	{0, 0, 0, 1, 1, 1, 1, 1}, // digit 7
  	{0, 0, 0, 0, 0, 0, 0, 1}, // digit 8
  	{0, 0, 0, 0, 1, 0, 0, 1}  // digit 9
};
  volatile byte result = 0;
	volatile byte singles = 0;
	volatile byte tens = 0;
/*
  initializeDisplay subroutine initializes 5 pins needed for controlling 7-segment
  displays in a cascade as follows:
  Arduino pin 12 = serial to parallel component reset
  Arduino pin 11 = serial to parallel component shiftClock
  Arduino pin 10 = serial to parallel component latchClock
  Arduino pin 9  = serial to parallel component outEnable
  Arduino pin 8  = serial to parallel component serialInput
  

*/
void initializeDisplay(void)
{

 	pinMode(serialInput_pin, OUTPUT);
	pinMode(outEnable_pin, OUTPUT);
	pinMode(latchClock_pin, OUTPUT);
	pinMode(shiftClock_pin, OUTPUT);
	pinMode(reset_pin, OUTPUT);
	digitalWrite(outEnable_pin, LOW); // enables output on QH' pin
	digitalWrite(reset_pin, HIGH); //resets bits on LOW
  writeHighAndLowNumber(0, 0);
}

/*
  WriteByte subroutine writes number 0,1,...,9 to
  7-segment display. If there are many 7-segment
  displays cascaded, last parameter can be used to
  control when number is actually shown at the outputs of
  display element.
  
  Parameters:
  uint8_t number: accepts values 0,1,..,9
  
  bool last: either true or false. True = number is displayed
  at the output, false is used if this function is called
  multiple times to write all cascaded numbers to 7-segment
  displays.
*/
void writeByte(uint8_t bits,bool last)
{
// See requirements for this function from display.h
}


// See requirements for this function from display.h
void writeHighAndLowNumber(uint8_t tens, uint8_t singles)
{
// See requirements for this function from display.h

  digitalWrite(latchClock_pin, LOW);
  for(int i = 7; i>=0; i--){
      digitalWrite(shiftClock_pin, LOW);
      if (digits[singles][i]==1) digitalWrite(serialInput_pin, LOW);
      if (digits[singles][i]==0) digitalWrite(serialInput_pin, HIGH);
      digitalWrite(shiftClock_pin, HIGH);
    }
   for(int i = 7; i>=0; i--){
      digitalWrite(shiftClock_pin, LOW);
      if (digits[tens][i]==1) digitalWrite(serialInput_pin, LOW);
      if (digits[tens][i]==0) digitalWrite(serialInput_pin, HIGH);
      digitalWrite(shiftClock_pin, HIGH);
    }
  digitalWrite(latchClock_pin, HIGH);
}

void showResult(byte number)
{
tens = 0;
  singles = 0;
  while(number >= 10){
    tens++;
    number = number - 10;
  }
  singles = number;
  writeHighAndLowNumber(tens, singles);
}


