#include "Simulation.h"
#include <iostream>


// constructor/destructor
Simulation::Simulation() : map_height(40), map_width(40) {
	init();
}

Simulation::~Simulation() {
	del();
}

// initialize/delete
void Simulation::init() {
	srand((unsigned)time(NULL));
	highest_id = 0;
	rules.setDefaults();
	initMap(map);
}

void Simulation::del() {
	delMap(map);
}
void Simulation::initMap(Terrain**& map) {
	map = new Terrain* [map_height];
	for (int i = 0; i < map_height; i++) {
		map[i] = new Terrain[map_width];
	}
}

void Simulation::delMap(Terrain**& map) {
	for (int i = 0; i < map_height; i++) {
		delete[] map[i];
	}
	delete[] map;
}

// get/set
const Rules& Simulation::getRules() const {
	return rules;
}

Rules* Simulation::getMutRulesPtr() {
	return &rules;
}

int Simulation::getWidth() const {
	return map_width;
}

int Simulation::getHeight() const {
	return map_height;
}

void Simulation::setWidth(int width) {
	map_width = width;
}

void Simulation::setHeight(int height) {
	map_height = height;
}

// operations on parameters
int Simulation::increaseId() {
	return ++highest_id;
}

// worm operations 
void Simulation::copyWormToNewMap(int x, int y, Directions dir, const Worm& worm, Terrain**& new_map) {
	int new_x = x, new_y = y;
	switch (dir) {
	case N:
		if (x == 0) new_x = map_height-1;
		else new_x--;
		break;
	case NE:
		if (y == map_width-1) new_y = 0;
		else new_y++;
		if (x == 0) new_x = map_height-1;
		else new_x--;
		break;
	case SE:
		if (y == map_width-1) new_y = 0;
		else new_y++;
		if (x == map_height-1) new_x = 0;
		else new_x++;
		break;
	case S:
		if (x == map_height-1) new_x = 0;
		else new_x++;
		break;
	case SW:
		if (y == 0) new_y = map_width-1;
		else new_y--;
		if (x == map_height-1) new_x = 0;
		else new_x++;
		break;
	case W:
		if (y == 0) new_y = map_width-1;
		else new_y--;
		break;
	case NW:
		if (y == 0) new_y = map_width-1;
		else new_y--;
		if (x == 0) new_x = map_height-1;
		else new_x--;
		break;
	}
	if (new_x < 0 || new_x > map_height-1 || new_y < 0 || new_y > map_width-1) {
		std::cout << "ERROR\nProgram is adding a worm outside of the map:\n"
			<< "direction:" << (int)dir 
			<< "\nnew_x: " << new_x << ", new_y: " << new_y << std::endl;
	}
	new_map[new_x][new_y].addWorm(worm);
}

void Simulation::spreadWorms(int x, int y, Terrain**& new_map) {
	if (x < 0 || x > map_height-1 || y < 0 || y > map_width-1)
		return;

	int dumped_amount = map[x][y].getWormsAmount();
	Worm* dumped = map[x][y].dumpWorms();
	for (int i = 0; i < dumped_amount; i++)
		copyWormToNewMap(x, y, static_cast<Directions>(rand() % 9), dumped[i], new_map);

	delete[] dumped;
}

// terrain operations
void Simulation::placeWorm() {
	int x = rand() % map_height;
	int y = rand() % map_width;
	map[x][y].createWorm(++highest_id, rules.getLifetime());
}

void Simulation::placeWormAt(int x, int y) {
	if (x < 0 || x >= map_height || y < 0 || y >= map_width) {
		return;
	}
	map[x][y].createWorm(++highest_id, rules.getLifetime());
}

void Simulation::timeTick() {
	Terrain** new_map;
	initMap(new_map);
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			highest_id = map[i][j].timeTick(highest_id, rules);
			new_map[i][j].setRegenerationTime(map[i][j].getRegenerationTime());
			new_map[i][j].setConsumed(map[i][j].getConsumed());
			spreadWorms(i, j, new_map);
		}
	}
	delMap(map);
	map = new_map;
}

// printing
void Simulation::printTop() const {
	std::cout << corner_tl;
	for (int i = 0; i < map_width*2 + 1; i++) {
		std::cout << hor_line;
	}
	std::cout << corner_tr << std::endl;
}

void Simulation::printBottom() const {
	std::cout << corner_bl;
	for (int i = 0; i < map_width*2 + 1; i++) {
		std::cout << hor_line;
	}
	std::cout << corner_br << std::endl;
}

void Simulation::printMap() const {
	printTop();
	for (int i = 0; i < map_height; i++) {
		std::cout << ver_line;
		for (int j = 0; j < map_width; j++)
			map[i][j].print();
		clearFontColor();
		std::cout << ' ' << ver_line << '\n';
	}
	printBottom();
}