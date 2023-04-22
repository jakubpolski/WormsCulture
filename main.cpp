#include "console_functions.h"
#include "Menu.h"
#include <iostream>

int main() {
	Menu menu{};
	menu.programLoop();
	system("cls");
	std::cout << "Do zrobaczenia\n";
	Sleep(1000);
	return 0;
}