#pragma once
#include "constants.h"

class Rules {
	int breed_amount;
	bool hunger_immunity;
	int terrain_regeneration_time;
	int max_worm_size;
	int fertility_time;
	int lifetime;
	int simulation_speed;
public:
	Rules() {
		setDefaults();
	}
	void setDefaults();

	// get/set
	int getBreedAmount() const;
	bool getHungerImmunity() const;
	int getTerrainRegenarationTime() const;
	int getMaxWormSize() const;
	int getFertilityTime() const;
	int getLifetime() const;
	int getSimulationSpeed() const;
	
	void setBreedAmount(int breed);
	void setImmunity(bool immunity);
	void setRegenrationTime(int regen);
	void setMaxWormSize(int max_size);
	void setFertilityTime(int fertility);
	void setLifetime(int lifetime);
	void setSimulationSpeed(int speed);

	// increase/decrease
	void switchImmunity();
	void increaseBreedAmount();
	void increaseRegenerationTime();
	void increaseMaxWormSize();
	void increaseFertilityTime();
	void increaseLifetime();
	void increaseSimulationSpeed();

	void decreaseBreedAmount();
	void decreaseRegenerationTime();
	void decreaseMaxWormSize();
	void decreaseFertilityTime();
	void decreaseLifetime();
	void decreaseSimulationSpeed();

};

// tests whether the value fits
bool testBreedAmount(int breed);
bool testImmunity(int immunity);
bool testRegenrationTime(int regen);
bool testMaxWormSize(int max_size);
bool testFertilityTime(int fertility);
bool testLifetime(int lifetime);
bool testSimulationSpeed(int speed);
