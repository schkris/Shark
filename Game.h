#ifndef Game_h
#define Game_h

// Global variable
extern int gameSelection; // 0 for "Start", 1 for "Exit"
extern const char* gameMenuItems[];
extern const int gameMenuSize; // Total number of items in the game menu

void handleGameSelection();
void startGame();
void runGame();

#endif