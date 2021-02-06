#include "Time.h"

float Time::elapsed = 0;
float Time::last = 0;
float Time::total = 0;
sf::Clock* Time::timer = nullptr;

void Time::init()
{
	timer = new sf::Clock();
	elapsed = total = last = 0;
}

void Time::tick()
{
	total = timer->getElapsedTime().asSeconds();
	elapsed = total - last;
	last = total;
}
