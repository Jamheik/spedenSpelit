#include "display.h"
  const int serialInput_pin = 8; 
	const int outEnable_pin = 9; 
	const int latchClock_pin = 10; 
	const int shiftClock_pin = 11;
	const int reset_pin = 12;
  int digits[10][8] = { //raudassa A ja B 7-segment pinnit väärinpäin
  {0, 0, 0, 0, 0, 0, 1, 1}, // digit 0
  {0, 1, 0, 1, 1, 1, 1, 1}, // digit 1 //korjattu ekat 2 toisinpäin eli A ja B
  {0, 0, 1, 0, 0, 1, 0, 1}, // digit 2
  {0, 0, 0, 0, 1, 1, 0, 1}, // digit 3
  {0, 1, 0, 1, 1, 0, 0, 1}, // digit 4 //korjattu sama
  {1, 0, 0, 0, 1, 0, 0, 1}, // digit 5 //korjattu sama
  {1, 0, 0, 0, 0, 0, 0, 1}, // digit 6 //korjattu sama
  {0, 0, 0, 1, 1, 1, 1, 1}, // digit 7
  {0, 0, 0, 0, 0, 0, 0, 1}, // digit 8
  {0, 0, 0, 0, 1, 0, 0, 1}  // digit 9
};
  volatile byte result = 0;
	volatile byte singles = 0;
	volatile byte tens = 0;

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

void writeHighAndLowNumber(uint8_t tens, uint8_t singles)
{

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


