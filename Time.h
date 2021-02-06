#pragma once

#include "SFML/Graphics.hpp"

class Time
{
	static float last;
	static sf::Clock* timer;

public:
	static float elapsed;
	static float total;

	static void init();
	static void tick();
};