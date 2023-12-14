#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

void initializeDisplay(void);

void writeHighAndLowNumber(uint8_t tens,uint8_t ones);

void showResult(byte result);

void writeSingles(byte);

void writeTens(byte);
#endif
