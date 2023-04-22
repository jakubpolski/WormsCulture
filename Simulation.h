#pragma once
#include "Terrain.h"
#include "Rules.h"

enum Directions { N, NE, E, SE, S, SW, W, NW };

class Simulation {
	Rules rules;
	int highest_id;
	Terrain** map;
	int map_height;
	int map_width;
	// worm opeartions
	void copyWormToNewMap(int x, int y, Directions dirs, const Worm& worm, Terrain**& new_map);
	
public:

	// constructor/destructor
	Simulation();
	~Simulation();

	// initilize/delete
	void init();
	void del();
	void initMap(Terrain**& map);
	void delMap(Terrain**& map);

	// get/set
	const Rules& getRules() const;
	Rules* getMutRulesPtr();
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);

	// operations on parameters
	int increaseId();

	// worm operations
	void spreadWorms(int x, int y, Terrain**& new_map);

	// terrain operations
	void timeTick();
	void placeWorm();
	void placeWormAt(int x, int y);
	
	// printing
	void printMap() const;
	void printTop() const;
	void printBottom() const;
	void printTerrain(int worms_amount, bool consumed) const;
};

// console operations
void clearFontColor();
void setFontColor(int worms_amount);