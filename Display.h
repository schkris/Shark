#ifndef Display_h
#define Display_h

#include <U8g2lib.h>

// Display Pins (Using EXP1 Connector)
#define LCD_CLOCK_PIN 30
#define LCD_DATA_PIN  17
#define LCD_CS_PIN    28

extern int currentScreen;

void displayBootScreen();
void initializeDisplay();
void renderMenu();
void renderStatusScreen();
void renderGameScreen();

#endif
