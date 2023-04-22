#define _CRT_SECURE_NO_WARNINGS
#include "console_functions.h"
#include <conio.h>
#include <iostream>

char checkForKeyboardInput() {
	if (_kbhit()) {
		char ch = _getch();
		fflush(stdin);
		return ch;
	} else {
		return ' ';
	}
}

void hideCursor() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hStdOut, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &curInfo);
}

void showCursor() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(hStdOut, &curInfo);
	curInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hStdOut, &curInfo);
}

bool mouseClicked() {
	return GetAsyncKeyState(VK_LBUTTON);
}

int getMouseXPositionOnGrid(int x_position, int offset) {
	x_position -= offset;
	if (x_position < 0 || x_position > 1919)
		return -1;
	else
		return x_position / 16;
}

int getMouseYPositionOnGrid(int y_position, int offset) {
	y_position -= offset;
	if (y_position < 0 || y_position > 1079)
		return -1;
	else
		return y_position / 16;
}

void resetCursorPosition() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

void placeCursorBelowMap() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 47 });
}

void setDefaultWindowParameters() {
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_SHOWMAXIMIZED);

	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(h_out, &buffer_info);
	short height = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
	COORD new_buffer_size;
	new_buffer_size.X = buffer_info.dwSize.X;
	new_buffer_size.Y = height;
	SetConsoleScreenBufferSize(h_out, new_buffer_size);
	
	HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE);
	DWORD cursor_input_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(h_in, cursor_input_mode);

	SetConsoleTitleA("Worm Culture");
}

void clearFontColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void setDefaultFont() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void setFontColor(int worms_amount) {
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	int color;
	if (worms_amount <= 1)
		color = 0xf;
	else if (worms_amount <= 5)
		color = 0xa;
	else if (worms_amount <= 10)
		color = 0x2;
	else if (worms_amount <= 20)
		color = 0xe;
	else if (worms_amount <= 50)
		color = 0x6;
	else if (worms_amount <= 100)
		color = 0xc;
	else if (worms_amount <= 500)
		color = 0x4;
	else if (worms_amount <= 1000)
		color = 0xd;
	else
		color = 0x5;

	SetConsoleTextAttribute(h_console, color);
}

