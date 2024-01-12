#ifndef Encoder_h
#define Encoder_h

#include <RotaryEncoder.h>

// Encoder pins and variables
#define BTN_EN1 11
#define BTN_EN2 10
#define BTN_ENC 16
#define BEEPER_PIN 27

extern bool buttonPressed;

void initializeEncoder();
void encoderInterrupt();
bool isButtonPressed();

#endif