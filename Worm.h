#pragma once
#include "Rules.h"
class Worm {
	int id;
	int size;
	int remaining_time;
	int lifetime;
public:

	// constructor/destructor
	Worm();
	Worm(int id);
	Worm(int id, int worm_size, int worm_remaining_time);
	Worm(const Worm& worm);

	// get/set
	int getId() const;
	int getSize() const;
	int getRemainingTime() const;

	// worm operations
	bool canBreed(const Rules& rules) const;
	int decreaseRemainingTime();
	int increaseSize();

};

