#pragma once
#include <Windows.h>

char checkForKeyboardInput();
void hideCursor();
void showCursor();
void resetCursorPosition();
void placeCursorBelowMap();
void setDefaultWindowParameters();
void clearFontColor();
void setFontColor(int worms_amount);
void setDefaultFont();
bool mouseClicked();
int getMouseXPositionOnGrid(int x_position, int offset);
int getMouseYPositionOnGrid(int y_position, int offset);
