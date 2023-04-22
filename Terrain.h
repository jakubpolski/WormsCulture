#pragma once
#include "Worm.h"
#include "Rules.h"

class Terrain {
	Worm* worms;
	int worms_amount;
	int max_worms_amount;
	int time_to_regenerate;
	bool consumed;
public:
	// constructor/destructor
	Terrain();
	~Terrain();

	// get/set
	int getRegenerationTime() const;
	int getWormsAmount() const;
	bool getConsumed() const;

	void setRegenerationTime(int time);
	void setWormsAmount(int amount);
	void setConsumed(bool consumed);

	// terrain operations
	bool consume(const Rules& rules);
	void restore(int time);
	int decreaseRemainingTime();
	int breedAllWorms(int highest_id, const Rules& rules);
	void consumeFoodAndKillOtherWorms(const Rules& rules);
	void killWormsWithoutLifetime();
	int timeTick(int highest_id, const Rules& rules);

	// worm operations
	void addWorm(const Worm& worm);
	void createWorm(int id, int lifetime);
	bool removeWorm(int id);
	Worm* dumpWorms();

	// printing
	void print() const;
};

