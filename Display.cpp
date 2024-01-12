#include "Display.h"
#include "Menu.h"
#include "Status.h"
#include "Game.h"
#include "SharkBitmap.h"
#include "GalagaBitmap.h"
#include "TestBitmap.h"

// Initialize the display (Software SPI)
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, LCD_CLOCK_PIN, LCD_DATA_PIN, LCD_CS_PIN, U8X8_PIN_NONE);

uint8_t flipByte(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void displayBootScreen() 
{
    // Define a buffer in RAM
    uint8_t buffer[sizeof(shark_bitmap)];

    // Copy data from PROGMEM to RAM buffer
    memcpy_P(buffer, shark_bitmap, sizeof(shark_bitmap));

    // Flip the bits in the buffer
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = flipByte(buffer[i]);
    }

    // Render the bitmap from the buffer
    u8g2.firstPage();
    do {
        u8g2.drawXBM(0, 0, SHARK_BMPWIDTH, SHARK_BMPHEIGHT, buffer);
    } while (u8g2.nextPage());

    delay(3500); // Display for 3.5 seconds
}

void initializeDisplay() {
  u8g2.begin();
  displayBootScreen();
}

void renderMenu() 
{
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB10_tr); // Set font
        u8g2.setDrawColor(1);
        for (int i = 0; i < menuSize; i++) {
            int y = i * 20 + 25; // Calculate the y position for each menu item
            u8g2.drawStr(15, y, menuItems[i]); // Draw menu item text

            if (i == currentSelection) {
                // Draw a circle next to the selected item
                u8g2.drawCircle(8, y - 5, 4); // Adjust x, y, and radius as needed
            }
        }
    } while (u8g2.nextPage());
}


void renderStatusScreen() {
    char tempHumidBuffer[50];  // Buffer to hold the temperature and humidity string
    char stepSpeedBuffer[50];

    // Format the temperature and humidity readings into a string
    snprintf(tempHumidBuffer, sizeof(tempHumidBuffer), "Temp: %.1fC, Hum: %.1f%%", temperature, humidity);

    snprintf(stepSpeedBuffer, sizeof(stepSpeedBuffer), "Speed: %d", stepperSpeed);

    u8g2.firstPage();
    do {
        u8g2.setDrawColor(1);
        u8g2.setFont(u8g2_font_ncenB08_tr); // Set font

        // Draw the status title
        u8g2.drawStr(0, 12, "Status");

        // Draw the temperature and humidity data
        u8g2.drawStr(0, 24, tempHumidBuffer);  // Position the text below the title

        // You can add more status information here as needed
        u8g2.drawStr(0, 36, stepSpeedBuffer);

    } while (u8g2.nextPage());
}

void renderGameScreen() {
    // Define a buffer for the Galaga bitmap
    uint8_t buffer[sizeof(galaga_bitmap)];  // Make sure this matches your bitmap array name

    // Copy the Galaga bitmap from PROGMEM to RAM buffer
    memcpy_P(buffer, galaga_bitmap, sizeof(galaga_bitmap));

    // Flip the bits in the buffer
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = flipByte(buffer[i]);
    }

    // Render the bitmap and text options
    u8g2.firstPage();
    do {
        // Black Background
        u8g2.setDrawColor(0);
        u8g2.drawBox(0, 0, 128, 64);

        // Center and draw the Galaga bitmap
        int bitmapX = (128 - GALAGA_BMPWIDTH) / 2;  // Center horizontally
        u8g2.drawXBM(bitmapX, 0, GALAGA_BMPWIDTH, GALAGA_BMPHEIGHT, buffer);

        u8g2.setDrawColor(1);
        u8g2.setFont(u8g2_font_ncenB08_tr); // Set the font for text
        // Draw game menu items and selection circle
        for (int i = 0; i < 2; i++) {
            const char* item = gameMenuItems[i];
            int itemWidth = u8g2.getStrWidth(item);
            int itemX = (128 - itemWidth) / 2;
            int itemY = GALAGA_BMPHEIGHT + 12 + i * 12;

            u8g2.drawStr(itemX, itemY, item);

            if (i == gameSelection) {
                // Draw a circle next to the selected item
                u8g2.drawCircle(itemX - 10, itemY - 3, 3);
            }
        }

    } while (u8g2.nextPage());
}
