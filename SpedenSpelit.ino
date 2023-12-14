#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include <EEPROM.h>
// alustetaan tarvittavia muuttujia
  extern int tens;
  extern int singles;
  bool gameOn = false;
  int lastButtonPress;
  int playedRounds = 0;
  int timerSpeed;
  int score;
  int leds[99];
  int buttonPress[99];
void setup()
{
  Serial.begin(9600); 
  // alustetaan ledit,napit ja näytöt koska niitä tarvitaan highscorejen näyttämiseen
  initButtonsAndButtonInterrupts();
  initializeLeds();
  initializeDisplay();

  
}

void loop()
{
}
ISR(PCINT2_vect) {
    int hiScore; 
    //jos peli ei ole päällä näytetään joka napilla eri highscore. isoin score vasemmasta napista ja pienin oikeasta
    if(digitalRead(2) == LOW && !gameOn){
      hiScore = eeprom_read_byte(0);
      showResult(hiScore);
      setLed(0);
    }
    else if (digitalRead(3) == LOW && !gameOn){
      hiScore = eeprom_read_byte(1);
      showResult(hiScore);
      setLed(1);
    }
  	else if (digitalRead(4) == LOW && !gameOn){
      hiScore = eeprom_read_byte(2);
      showResult(hiScore);
      setLed(2);
    }
  	else if(digitalRead(5) == LOW && !gameOn){
      hiScore = eeprom_read_byte(3);
      showResult(hiScore);
      setLed(3);
    }
    // jos peli on päällä napit toimii "pelimodessa"
  if(digitalRead(2) == LOW && gameOn){
      lastButtonPress = 0;
      checkGame(lastButtonPress);
    }
    else if (digitalRead(3) == LOW && gameOn){
      lastButtonPress = 1;
       checkGame(lastButtonPress);
    }
  	else if (digitalRead(4) == LOW && gameOn){
      lastButtonPress = 2;
       checkGame(lastButtonPress);
    }
  	else if(digitalRead(5) == LOW && gameOn){
      lastButtonPress = 3;
      checkGame(lastButtonPress);
    }
  //yksi nappi laitettu pelin aloittamiselle
   if(digitalRead(6) == LOW){
      startTheGame();
    }
 }



ISR(TIMER1_COMPA_vect)
{
  int nopeutus = 1;
  //laitetaan ledit leds[] taulukkoon
  leds[playedRounds] = random(4);
  //sammutetaan edellinen ledi ennenkuin uusi sytytetään
  setLed(leds[playedRounds]);
  // jos playedrounds on joku tasa kymmen lisätään pelin nopeutta
  if(playedRounds > 0){
   nopeutus = playedRounds  % 10;
  }
  if(nopeutus == 0){
    timerSpeed -= 1562;
    playedRounds++;
    OCR1A = timerSpeed;
    nopeutus = 1;
  }
  //jos ei ole tasakymmen lisätään vaan playedrounds yhdellä
  else{
    playedRounds++;
  }
}



void initializeTimer(void)
{
  // laitetaan timer toimimaan ctc tilassa
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = 0; 
  OCR1A = timerSpeed;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  TIMSK1 |= (1 << OCIE1A); 
  interrupts();
}

void checkGame(byte lastButtonPress)
{
  //laitetaan viimeisin napinpainallus buttonpress[] taulukkoon
  buttonPress[score] = lastButtonPress;
  //verrataan napin painallusta lediin ja jos oikein painettu sammutetaan ledi ja lisätään scorea ja näytöllä näkyvää lukua yhdellä
  if(buttonPress[score] == leds[score]){
    shutLed(buttonPress[score]);
    score++;
    showResult(score);
  }
  //jos väärää nappia painettu peli loppuu
  else{
    stopTheGame();
  }
}

void initializeGame()
{
  // alustetaan tarvittavat asiat peliin ja showresult(0) koska ilman sitä näytöt saattaa alottaa väärästä luvusta laskemisen
  gameOn = true;
  showResult(0);
  clearAllLeds();
  //nollataan score playedrounds ja timerspeed 
  score = 0;
  playedRounds = 0;
  timerSpeed = 15625;
}

void startTheGame()
{
  initializeTimer();
  initializeGame();
}

void stopTheGame(void){
  // vaihdetaan gameon muuttuja falseksi ja näytetään score näytöillä
  gameOn = false;
  showResult(score);
  //sammutetaan timeri ja nollataan tens ja singles
  TCCR1B = 0;
  tens = 0;
  singles = 0;
  //sytytetään kaikki ledit
  setAllLeds();
  //vertaillaa highscoreja ja jos score on isompi se tallennetaan eeprom muistiin
   for(int i = 0; i <=3; i++){
    if(score>eeprom_read_byte(i)){
      int tempScore = eeprom_read_byte(i);
      EEPROM.update(i, score);
      score = tempScore;
    }
  }
}