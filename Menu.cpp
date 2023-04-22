#include "Menu.h"
#include "console_functions.h"
#include <iostream>
#include <string>

using namespace std;

void getFirstMax5LetterWord(string& s) {
	char word[5] = { '\0' };
	int word_start_index = -1;
	for (int i = 0; i < s.length(); i++) {
		if (!isspace(s[i])) {
			word_start_index = i;
			break;
		}
	}
	for (int i = word_start_index; i < s.length(); i++) {
		if (!isspace(s[i]) && i - word_start_index <= 10)
			word[i - word_start_index] = s[i];
		else
			break;
	}
	s = word;
}

void stringToLower(std::string& s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);
}

Menu::Menu() : sim(), kb_input('M'), stop(false) {
	ios_base::sync_with_stdio(false);
	(void)mouseClicked();
	setDefaultFont();
	system("color F");
	setDefaultWindowParameters();
}

void Menu::processInputsWhileSleeping() {
	int amount_of_sleeps = 11 - sim.getRules().getSimulationSpeed();
	int i = 0;
	while (i++ < amount_of_sleeps) {
		handleMouseClick();
		handleQuickButtons();
		if (kb_input == esc) {
			stop = true;
			return;
		}
		else if (kb_input == 'M' || kb_input == 'm') {
			stop = simMenu();
			system("cls");
			kb_input = checkForKeyboardInput();
			break;
		}
		kb_input = checkForKeyboardInput();
		placeCursorBelowMap();
	
		appendQuickMenu();
		Sleep(20);
		amount_of_sleeps = 11 - sim.getRules().getSimulationSpeed();
	}
}

void Menu::printLegend() {
	cout << "[+ Regenerating], [";

	cout << square;
	cout << " 1 Worm], [";

	setFontColor(2);
	cout << square;
	clearFontColor();
	cout << " 2-5 Worms], [";

	setFontColor(6);
	cout << square;
	clearFontColor();
	cout << " 6-10 Worms], [";

	setFontColor(11);
	cout << square;
	clearFontColor();
	cout << " 11-20 Worms], [";

	setFontColor(21);
	cout << square;
	clearFontColor();
	cout << " 21-50 Worms], [";

	setFontColor(51);
	cout << square;
	clearFontColor();
	cout << " 51-100 Worms], [";

	setFontColor(101);
	cout << square;
	clearFontColor();
	cout << " 101-500 Worms], [";

	setFontColor(501);
	cout << square;
	clearFontColor();
	cout << " 501-1000 Worms], [";

	setFontColor(1001);
	cout << square;
	clearFontColor();
	cout << " 1001+ Worms]\n";
}

void Menu::printMenu() {
	const Rules rules = sim.getRules();
	system("cls");
	cout << "Game menu\n\n"
		"1 - Set worm parameters\n"
		"2 - Set simulation parameters\n"
		"3 - Set map size\n"
		"R - Restart simulation\n"
		"ENTER - Resume simulation\n"
		"ESC - Quit\n\n"
		"Press any of the following keys to continue\n\n"
		"Current values:"
		"\nTerrain regeneration time: " << rules.getTerrainRegenarationTime()
		<< "\nMaximum worm size: " << rules.getMaxWormSize()
		<< "\nWorm fertility time: " << rules.getFertilityTime()
		<< "\nMaximum worm lifetime: " << rules.getLifetime()
		<< "\nSimulation speed: " << rules.getSimulationSpeed()
		<< "\nWorm breed amount: " << rules.getBreedAmount()
		<< "\nHunger immunity: " << rules.getHungerImmunity();
}

void Menu::appendQuickMenu() {
	const Rules rules = sim.getRules();
	printLegend();

	cout << "Quick menu:\n"
		"(ESC) " << "Exit the program\n"
		"(Q/A) " << rules.getTerrainRegenarationTime() << " Increase/Decrease terrain regeneration time \n"
		"(W/S) " << rules.getMaxWormSize() << " Increase/Decrease maximum worm size \n"
		"(E/D) " << rules.getFertilityTime() << " Increase/Decrease worm fertility time \n"
		"(R/F) " << rules.getLifetime() << " Increase/Decrease maximum worm lifetime \n"
		"(T/G) " << rules.getSimulationSpeed() << " Increase/Decrease simulation speed \n"
		"(Y/H) " << rules.getBreedAmount() << " Increase / Decrease worms breed amount \n"
		"(U) " << rules.getHungerImmunity() << " Switch worm hunger immunity \n"
		"(P) Place a worm on the map\n"
		"(M) Open full menu" << std::endl;
}

bool getUnsignedIntInput(int& result) {
	std::string buffer;
	std::getline(cin, buffer);
	getFirstMax5LetterWord(buffer);
	if (buffer.empty()) {
		return true;
	}
	else if (isdigit(buffer[0])) {
		result = atoi(buffer.c_str());
		return true;
	}
	else {
		return false;
	}
}

bool Menu::inputWormParameters() {
	Rules* rules = sim.getMutRulesPtr();
	int breed_amount = -1, max_worm_size = -1, fertility_time = -1, lifetime = -1, hunger_immunity = -1;
	system("cls");
	showCursor();
	cout << "Press enter to skip a value\n\n";

	cout << "Enter max breed amount: ";
	if (getUnsignedIntInput(breed_amount) == false)
		return false;

	cout << "Enter maximum worm size: ";
	if (getUnsignedIntInput(max_worm_size) == false)
		return false;

	cout << "Enter fertility time: ";
	if (getUnsignedIntInput(fertility_time) == false)
		return false;

	cout << "Enter maximum lifetime: ";
	if (getUnsignedIntInput(lifetime) == false)
		return false;

	cout << "Enter hunger immunity (true or false): ";
	std::string buffer;
	std::getline(cin, buffer);
	getFirstMax5LetterWord(buffer);
	stringToLower(buffer);
	if (buffer == "true")
		hunger_immunity = 1;
	else if (buffer == "false")
		hunger_immunity = 0;

	hideCursor();

	if ((!testBreedAmount(breed_amount) && breed_amount != -1) ||
		(!testMaxWormSize(max_worm_size) && max_worm_size != -1) ||
		(!testFertilityTime(fertility_time) && fertility_time != -1) ||
		(!testLifetime(lifetime) && lifetime != -1) ||
		(!testImmunity(hunger_immunity) && hunger_immunity != -1)) {
		return false;
	}

	if (testBreedAmount(breed_amount))
		rules->setBreedAmount(breed_amount);

	if (testMaxWormSize(max_worm_size))
		rules->setMaxWormSize(max_worm_size);

	if (testFertilityTime(fertility_time))
		rules->setFertilityTime(fertility_time);

	if (testLifetime(lifetime))
		rules->setLifetime(lifetime);

	if (testImmunity(hunger_immunity))
		rules->setImmunity(hunger_immunity);

	return true;
}

bool Menu::inputSimulationParameters() {
	Rules* rules = sim.getMutRulesPtr();
	int regeneration_time = -1, simulation_speed = -1;
	system("cls");
	showCursor();
	cout << "Press enter to skip a value\n\n";

	cout << "Enter terrain regeneration time: ";
	if (getUnsignedIntInput(regeneration_time) == false)
		return false;

	cout << "Enter simulation speed: ";
	if (getUnsignedIntInput(simulation_speed) == false)
		return false;

	hideCursor();

	if ((!testRegenrationTime(regeneration_time) && regeneration_time != -1) ||
		(!testSimulationSpeed(simulation_speed) && simulation_speed != -1)) {
		return false;
	}
	
	if (testRegenrationTime(regeneration_time))
		rules->setRegenrationTime(regeneration_time);

	if (testSimulationSpeed(simulation_speed))
		rules->setSimulationSpeed(simulation_speed);

	return true;
}

bool Menu::inputMapSize() {
	int width = -1, height = -1;
	system("cls");
	showCursor();
	cout << "Press enter to skip a value\n\n";

	cout << "Enter new map width: ";
	if (getUnsignedIntInput(width) == false || width > max_width || width == 0) {
		hideCursor();
		return false;
	}
	cout << "Enter new map height: ";
	if (getUnsignedIntInput(height) == false || height > max_height || height == 0) {
		hideCursor();
		return false;
	}
	hideCursor();
	
	if (width != -1 || height != -1) {
		sim.del();
		if (width != -1) sim.setWidth(width);
		if (height != -1) sim.setHeight(height);
		sim.init();
	}	
	return true;
}

bool Menu::simMenu() {
	printMenu();

	std::string input_data;
	while (true) {
		switch (checkForKeyboardInput()) {
		case esc:
			return true;
		case enter:
			return false;
		case 'R':
		case 'r':
			system("cls");
			sim.del();
			sim.init();
			cout << "Simulation restarted";
			Sleep(1000);
			printMenu();
			break;
		case '1':
			if (inputWormParameters())
				cout << "\nOperation completed" << std::endl;
			else
				cout << "\nInvalid input, reverting changes" << std::endl;
			Sleep(1000);
			printMenu();
			break;
		case '2':
			if (inputSimulationParameters())
				cout << "\nOperation completed" << std::endl;
			else
				cout << "\nInvalid input, reverting changes" << std::endl;
			Sleep(1000);
			printMenu();
			break;
		case '3':
			if (inputMapSize()) {
				cout << "\nOperation completed" << std::endl;
			}
			else {
				cout << "\nInvalid input, reverting changes" << std::endl;
			}
			Sleep(1000);
			printMenu();
			break;
		}
		Sleep(50);
	}
}

void Menu::handleQuickButtons() {
	Rules* rules = sim.getMutRulesPtr();
	switch (kb_input) {
	case 'Q': case 'q':
		rules->increaseRegenerationTime();
		break;
	case 'A': case 'a':
		rules->decreaseRegenerationTime();
		break;
	case 'W': case 'w':
		rules->increaseMaxWormSize();
		break;
	case 'S': case 's':
		rules->decreaseMaxWormSize();
		break;
	case 'E': case 'e':
		rules->increaseFertilityTime();
		break;
	case 'D': case 'd':
		rules->decreaseFertilityTime();
		break;
	case 'R': case 'r':
		rules->increaseLifetime();
		break;
	case 'F': case 'f':
		rules->decreaseLifetime();
		break;
	case 'T': case 't':
		rules->increaseSimulationSpeed();
		break;
	case 'G': case 'g':
		rules->decreaseSimulationSpeed();
		break;
	case 'Y': case 'y':
		rules->increaseBreedAmount();
		break;
	case 'H': case 'h':
		rules->decreaseBreedAmount();
		break;
	case 'U': case 'u':
		rules->switchImmunity();
		break;
	case 'P': case 'p':
		sim.placeWorm();
		break;
	}
}

void Menu::handleMouseClick() {
	if (!mouseClicked())
		return;

	static POINT mouse_pos{ NULL };
	GetCursorPos(&mouse_pos);

	static RECT window_pos{ NULL };
	GetWindowRect(GetConsoleWindow(), &window_pos);

	int window_x_coord = window_pos.left + 8;
	int window_y_coord = window_pos.top + 28;

	int grid_x = getMouseXPositionOnGrid(mouse_pos.x, window_x_coord);
	int grid_y = getMouseYPositionOnGrid(mouse_pos.y, window_y_coord);
	if (grid_x < 1 || grid_x > sim.getWidth() || grid_y < 1 || grid_y > sim.getHeight())
		return;

	sim.placeWormAt(grid_y-1, grid_x-1);
}

void Menu::programLoop() {
	while (!stop) {
		hideCursor();
		processInputsWhileSleeping();
		resetCursorPosition();
		sim.printMap();
		sim.timeTick();
	}
}