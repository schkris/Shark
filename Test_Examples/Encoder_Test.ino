#include <U8g2lib.h>
#include <RotaryEncoder.h>

#define BTN_EN1 11
#define BTN_EN2 10
#define BTN_ENC 16
#define BEEPER_PIN 27
#define LCD_CLOCK_PIN 30
#define LCD_DATA_PIN  17
#define LCD_CS_PIN    28

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, LCD_CLOCK_PIN, LCD_DATA_PIN, LCD_CS_PIN, U8X8_PIN_NONE);
RotaryEncoder *encoder = nullptr;

void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}

void setup() 
{
  pinMode(BTN_ENC, INPUT_PULLUP);
  pinMode(BEEPER_PIN, OUTPUT);
  Serial.begin(9600);
  u8g2.begin();
  // use TWO03 mode when PIN_IN1, PIN_IN2 signals are both LOW or HIGH in latch position.
  encoder = new RotaryEncoder(BTN_EN1, BTN_EN2, RotaryEncoder::LatchMode::TWO03);

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(BTN_EN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN_EN2), checkPosition, CHANGE);
}

void loop() 
{

  static int pos = 0;

  encoder->tick(); // just call tick() to check the state.

  int newPos = encoder->getPosition();
  if (pos != newPos) {
    Serial.print("pos:");
    Serial.print(newPos);
    Serial.print(" dir:");
    Serial.println((int)(encoder->getDirection()));
    pos = newPos;
  }
  

  if (digitalRead(BTN_ENC) == LOW) 
  {
    digitalWrite(BEEPER_PIN, HIGH); // Turn on the buzzer
  }
  else
  {
    digitalWrite(BEEPER_PIN, LOW);
  }

  u8g2.firstPage();
  do {
    char displayStr[20]; // Buffer to hold the string representation
    u8g2.setFont(u8g2_font_ncenB10_tr); // Set a slightly larger font

    // Convert MSB, LSB, and currentSelection to string and display them
    snprintf(displayStr, sizeof(displayStr), "Pos: %d Dir: %d", encoder->getPosition(), (int)(encoder->getDirection()));
    u8g2.drawStr(0, 20, displayStr); // Display MSB and LSB
    

    // snprintf(displayStr, sizeof(displayStr), "Selection: %d", currentSelection);
    // u8g2.drawStr(0, 40, displayStr); // Display currentSelection
  } while (u8g2.nextPage());

}
