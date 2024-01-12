#include "Game.h"
#include "Display.h"

int gameSelection = 0;
const char* gameMenuItems[] = {"Start", "Exit"};
const int gameMenuSize = 2;

void handleGameSelection() 
{
  if (gameSelection == 0) 
  {
    // Start the game
  } 
  else if (gameSelection == 1) 
  {
    // Exit to main menu
    currentScreen = 0;
    gameSelection = 0; // Reset game selection
  }
}
