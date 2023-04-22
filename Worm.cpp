#include "Worm.h"

// constructor/destructor
Worm::Worm() {
	id = -1;
	size = -1;
	remaining_time = -1;
	lifetime = -1;
}

Worm::Worm(int id) {
	this->id = id;
	size = default_worm_size;
	remaining_time = default_lifetime;
	lifetime = remaining_time;
}

Worm::Worm(int id, int worm_size, int worm_remaining_time) {
	this->id = id;
	size = (worm_size > 0) ? worm_size : default_worm_size;
	remaining_time = (worm_remaining_time > 0) ? worm_remaining_time : default_lifetime;
	lifetime = remaining_time;
}

Worm::Worm(const Worm& worm) {
	id = worm.id;
	size = worm.size;
	remaining_time = worm.remaining_time;
	lifetime = worm.lifetime;
}

// get/set
int Worm::getId() const {
	return id;
}

int Worm::getSize() const {
	return size;
}

int Worm::getRemainingTime() const {
	return remaining_time;
}

// worm operations
bool Worm::canBreed(const Rules& rules) const {
	return lifetime - remaining_time <= rules.getFertilityTime();
}

int Worm::decreaseRemainingTime() {
	return --remaining_time;
}

int Worm::increaseSize() {
	return ++size;
}
