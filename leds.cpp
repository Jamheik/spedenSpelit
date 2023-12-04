#include "Arduino.h"
#include "leds.h"

void initializeLeds()
{
  //asetetaan ledien pinnit outputeiksi
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

//sytytetään tietty ledi ledNumerin antamalla arvolla
void setLed(byte ledNumber)
{
  clearAllLeds();
  if(ledNumber == 0){
    digitalWrite(A2, HIGH);
  }
  else if(ledNumber == 1){
    digitalWrite(A3, HIGH);
  }
  else if (ledNumber == 2) {
  digitalWrite(A4, HIGH);
  }
  else if(ledNumber == 3){
    digitalWrite(A5, HIGH);
  }

}

//sammuttaa kaikki ledit
void clearAllLeds()
{
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
 
}
//sytyttää kaikki ledit
void setAllLeds()
{
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
}
//sammuttaa tietyn ledin 
void shutLed(byte ledNumber)
{
  if(ledNumber == 0){
    digitalWrite(A2, LOW);
  }
  else if(ledNumber == 1){
    digitalWrite(A3, LOW);
  }
  else if (ledNumber == 2) {
  digitalWrite(A4, LOW);
  }
  else if(ledNumber == 3){
    digitalWrite(A5, LOW);
  }

}