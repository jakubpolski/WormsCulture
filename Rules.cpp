#include "Rules.h"

void Rules::setDefaults() {
	breed_amount = default_breed_amount;
	hunger_immunity = default_hunger_immunity;
	terrain_regeneration_time = default_terrain_regeneration_time;
	max_worm_size = default_max_worm_size;
	fertility_time = default_fertility_time;
	lifetime = default_lifetime;
	simulation_speed = default_simulation_speed;
}

// get
int Rules::getBreedAmount() const {
	return breed_amount;
}
bool Rules::getHungerImmunity() const {
	return hunger_immunity;
}
int Rules::getTerrainRegenarationTime() const {
	return terrain_regeneration_time;
}
int Rules::getMaxWormSize() const {
	return max_worm_size;
}
int Rules::getFertilityTime() const {
	return fertility_time;
}
int Rules::getLifetime() const {
	return lifetime;
}
int Rules::getSimulationSpeed() const {
	return simulation_speed;
}

// set
void Rules::setBreedAmount(int breed) {
	breed_amount = breed;
}
void Rules::setImmunity(bool immunity) {
	hunger_immunity = immunity;
}
void Rules::setRegenrationTime(int regen) {
	terrain_regeneration_time = regen;
}
void Rules::setMaxWormSize(int max_size) {
	max_worm_size = max_size;
}
void Rules::setFertilityTime(int fertility) {
	fertility_time = fertility;
}
void Rules::setLifetime(int lifetime) {
	this->lifetime = lifetime;
}

void Rules::setSimulationSpeed(int speed) {
	simulation_speed = speed;
}

// increase/decrease
void Rules::switchImmunity() {
	hunger_immunity = !hunger_immunity;
}

void Rules::increaseBreedAmount() {
	breed_amount++;
}

void Rules::increaseRegenerationTime() {
	terrain_regeneration_time++;
}

void Rules::increaseMaxWormSize() {
	max_worm_size++;
}

void Rules::increaseFertilityTime() {
	fertility_time++;
}

void Rules::increaseLifetime() {
	lifetime++;
}

void Rules::increaseSimulationSpeed() {
	if (simulation_speed < 10)
		simulation_speed++;
}

void Rules::decreaseBreedAmount() {
	if (breed_amount > 0)
		breed_amount--;
}

void Rules::decreaseRegenerationTime() {
	if (terrain_regeneration_time > 0)
		terrain_regeneration_time--;
}

void Rules::decreaseMaxWormSize() {
	if (max_worm_size > 1)
		max_worm_size--;
}

void Rules::decreaseFertilityTime() {
	if (fertility_time > 0)
		fertility_time--;
}

void Rules::decreaseLifetime() {
	if (lifetime > 1)
		lifetime--;
}

void Rules::decreaseSimulationSpeed() {
	if (simulation_speed > 1)
		simulation_speed--;
}
// test
bool testBreedAmount(int breed) {
	return breed >= 0;
}
bool testImmunity(int immunity) {
	return immunity == 1 || immunity == 0;
}
bool testRegenrationTime(int regen) {
	return regen >= 0;
}
bool testMaxWormSize(int max_size) {
	return max_size > 0;
}
bool testFertilityTime(int fertility) {
	return fertility >= 0;
}
bool testLifetime(int lifetime) {
	return lifetime > 0;
}
bool testSimulationSpeed(int speed) {
	return speed > 0;
}