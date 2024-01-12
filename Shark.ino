#include "Safety.h"
#include "Display.h"
#include "Encoder.h"
#include "Menu.h"
#include "Status.h"
#include "Game.h"

int currentScreen = 0;
int stepperSpeed = 0;

void setup() 
{
  Serial.begin(9600);
  initializeSafety();
  initializeDisplay();
  initializeEncoder();
  initializeDHTSensor();
  initializeStepper();
}

void loop() 
{
  maintainSafety();
  encoderInterrupt();

  if (isButtonPressed()) 
  {
    // Switch Statement For Selecting
    switch (currentScreen) 
    {
      case 0:
        handleMenuSelection();
      break;
      case 1:
        stepperSpeed = 0;
        currentScreen = 0;
      break;
      case 2:
        handleGameSelection();
      break;
    }
    digitalWrite(BEEPER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BEEPER_PIN, LOW);
  }

  // Switch Statement For Rendering
  switch (currentScreen) 
  {
    case 0:
      renderMenu();
    break;
    case 1:
      readDHTSensor();
      controlStepperMotor(stepperSpeed);
      renderStatusScreen();
    break;
    case 2:
      renderGameScreen();
    break;
  }
}
