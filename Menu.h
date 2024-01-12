#ifndef Menu_h
#define Menu_h

// Menu items
extern const char* menuItems[];
extern int currentSelection; // Index of the currently selected menu item
extern const int menuSize;   // Total number of items in the menu

void handleMenuSelection();

#endif