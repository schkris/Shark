#include "Menu.h"
#include "Display.h"

const char* menuItems[] = {"Status Screen", "Game Screen"};
int currentSelection = 0;
const int menuSize = 2;

void handleMenuSelection() 
{
    switch (currentSelection) 
    {
      case 0:
        currentScreen = 1;
        break;
      case 1:
        currentScreen = 2;
        break;
    }
}
