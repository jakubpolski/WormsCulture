#pragma once

// Map size
constexpr short max_width = 115,
	max_height = 45;

// Rules
constexpr short default_breed_amount = 3,
	default_terrain_regeneration_time = 5,
	default_max_worm_size = 10,
	default_fertility_time = 2,
	default_lifetime = 2,
	default_simulation_speed = 7;

constexpr bool default_hunger_immunity = false;

// characters
constexpr char square = (char)254u,
	hor_line = (char)205u,
	ver_line = (char)186u,
	corner_tl = (char)201u,
	corner_tr = (char)187u,
	corner_bl = (char)200u,
	corner_br = (char)188u;

// Worm
constexpr short default_worm_size = 1;
