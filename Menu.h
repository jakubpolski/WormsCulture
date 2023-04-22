#pragma once
#include "Simulation.h"

constexpr char esc = (char)27u;
constexpr char enter = (char)13u;

class Menu {
	Simulation sim;
	char kb_input;
	bool stop;
public:
	Menu();
	void processInputsWhileSleeping();
	void printLegend();
	void printMenu();
	void appendQuickMenu();
	bool inputWormParameters();
	bool inputSimulationParameters();
	bool inputMapSize();
	bool simMenu();
	void handleQuickButtons();
	void handleMouseClick();
	void programLoop();
};