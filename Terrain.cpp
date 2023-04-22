#include "Terrain.h"
#include "constants.h"
#include "console_functions.h"
#include <iostream>


// constructor/destructor
Terrain::Terrain() {
	worms = new Worm[50];
	worms_amount = 0;
	max_worms_amount = 50;
	time_to_regenerate = default_terrain_regeneration_time;
	consumed = false;
}
Terrain::~Terrain() {
	delete[] worms;
}

// get/set
int Terrain::getRegenerationTime() const {
	return time_to_regenerate;
}

int Terrain::getWormsAmount() const {
	return worms_amount;
}

bool Terrain::getConsumed() const {
	return consumed;
}

void Terrain::setRegenerationTime(int time) {
	time_to_regenerate = time;
}

void Terrain::setWormsAmount(int amount) {
	worms_amount = amount;
}

void Terrain::setConsumed(bool consumed) {
	this->consumed = consumed;
}

// terrain operations
bool Terrain::consume(const Rules& rules) {
	if (consumed)
		return false;

	if (rules.getTerrainRegenarationTime() > 0)
		consumed = true;
	else
		consumed = false;

	time_to_regenerate = rules.getTerrainRegenarationTime();
	return true;
}

void Terrain::restore(int time) {
	consumed = false;
	time_to_regenerate = time;
}

int Terrain::decreaseRemainingTime() {
	if (consumed)
		return --time_to_regenerate;
	else
		return time_to_regenerate;
}

int Terrain::breedAllWorms(int highest_id, const Rules& rules) {
	if (worms_amount > 1000) {
		int old_worms_amount = worms_amount;
		Worm* old_worms = worms;
		worms = new Worm[1000];
		worms_amount = 750;
		max_worms_amount = 1000;
		memcpy(worms, &worms[old_worms_amount - 751], 750);
		delete[] old_worms;
	}

	int old_worms_amount = worms_amount;
	for (int i = 0; i < old_worms_amount; i++) {
		if (worms_amount > 1100)
			break;
		if (worms[i].canBreed(rules))
			for (int j = 0; j < rules.getBreedAmount(); j++)
				createWorm(++highest_id, rules.getLifetime());
	}
		
	return highest_id;
}

void Terrain::consumeFoodAndKillOtherWorms(const Rules& rules) {
	if (worms_amount <= 0)
		return;

	bool worm_ate_food = consume(rules);
	if (rules.getHungerImmunity() == true) {
		if (worm_ate_food) {
			for (int i = worms_amount - 1; i >= 0; i--) {
				if (worms[i].getSize() < rules.getMaxWormSize()) {
					worms[i].increaseSize();
					break;
				}
			}
		}
	} else {
		Worm* new_worms = new Worm[50];
		max_worms_amount = 50;
		if (worm_ate_food) {
			for (int i = worms_amount-1; i >= 0; i--) {
				if (worms[i].getSize() < rules.getMaxWormSize()) {
					new_worms[0] = Worm(worms[i]);
					new_worms[0].increaseSize();
					break;
				}
			}
			worms_amount = 1;
		} else {
			worms_amount = 0;
		}
		delete[] worms;
		worms = new_worms;
	}
}


void Terrain::killWormsWithoutLifetime() {
	int i = 0;
	while (i < worms_amount) {
		if (worms[i].decreaseRemainingTime() > 0)
			i++;
		else
			removeWorm(worms[i].getId());
	}
}

int Terrain::timeTick(const int highest_id, const Rules& rules) {
	if (decreaseRemainingTime() <= 0)
		restore(rules.getTerrainRegenarationTime());
	consumeFoodAndKillOtherWorms(rules);
	killWormsWithoutLifetime();
	return breedAllWorms(highest_id, rules);
}



// worm operations
void Terrain::addWorm(const Worm& worm) {
	if (worms_amount >= max_worms_amount) {
		Worm* temp = new Worm[max_worms_amount + 50];
		max_worms_amount += 50;
		memcpy(temp, worms, sizeof(worms[0]) * worms_amount);
		delete[] worms;
		worms = temp;
	}
	worms[worms_amount] = Worm(worm);
	worms_amount++;
}

void Terrain::createWorm(int id, int lifetime) {
	addWorm(Worm(id, default_worm_size, lifetime));
}

bool Terrain::removeWorm(int id) {
	int index_to_delete = -1;
	for (int i = 0; i < worms_amount; i++) {
		if (worms[i].getId() == id) {
			index_to_delete = i;
			break;
		}
	}
	if (index_to_delete == -1)
		return false;
	
	if (index_to_delete < worms_amount-1)
		memmove(&worms[index_to_delete], &worms[index_to_delete + 1], sizeof(Worm));
	worms_amount--;
	return true;
}

Worm* Terrain::dumpWorms() {
	Worm* new_worms = worms;
	worms = new Worm[5];
	worms_amount = 0;
	max_worms_amount = 5;
	return new_worms;
}

void Terrain::print() const {
	if (worms_amount <= 0) {
		if (consumed) {
			clearFontColor();
			std::cout << " +";
		}
		else {
			std::cout << "  ";
		}
	}
	else {
		setFontColor(worms_amount);
		std::cout << ' ' << square;
	}
}