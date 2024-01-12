#include "Encoder.h"
#include "Display.h"
#include "Menu.h"
#include "Game.h"
#include <Arduino.h>

// Encoder pin definitions and variables
bool buttonPressed = false;
RotaryEncoder encoder(BTN_EN1, BTN_EN2, RotaryEncoder::LatchMode::FOUR3);

void checkEncoder() 
{
  encoder.tick();
}

void initializeEncoder() 
{
    attachInterrupt(digitalPinToInterrupt(BTN_EN1), checkEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BTN_EN2), checkEncoder, CHANGE);
    pinMode(BTN_ENC, INPUT_PULLUP);
    pinMode(BEEPER_PIN, OUTPUT);
}

// Serial.print("MSB: "); Serial.print(MSB); Serial.print(", LSB: "); Serial.println(LSB);
void encoderInterrupt()
{
    static int lastPos = -1;
    RotaryEncoder::Direction dir = RotaryEncoder::Direction::NOROTATION;
    int newPos = encoder.getPosition();
    if (newPos != lastPos) 
    {
        dir = encoder.getDirection();
        if(dir == RotaryEncoder::Direction::COUNTERCLOCKWISE) // CCW
        {
            if(currentSelection > 0 && currentScreen == 0)
            {
                currentSelection--;
            }
            else if(gameSelection > 0 && currentScreen == 2)
            {
                gameSelection --;
            }
        }
        else if(dir == RotaryEncoder::Direction::CLOCKWISE) // CW
        {
            if(currentSelection < menuSize - 1 && currentScreen == 0)
            {
                currentSelection++;
            }
            else if(gameSelection < gameMenuSize - 1 && currentScreen == 2)
            {
                gameSelection ++;
            }
        }
    }
}

bool isButtonPressed() {
    static unsigned long lastDebounceTime = 0;
    static bool lastButtonState = HIGH;
    static bool buttonState = HIGH;

    unsigned long debounceDelay = 50; // 50 milliseconds for debounce
    bool currentReading = digitalRead(BTN_ENC);

    if (currentReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentReading != buttonState) {
            buttonState = currentReading;
            if (buttonState == LOW) {
                lastButtonState = currentReading;
                return true; // Button is pressed
            }
        }
    }

    lastButtonState = currentReading;
    return false; // Button is not pressed
}
