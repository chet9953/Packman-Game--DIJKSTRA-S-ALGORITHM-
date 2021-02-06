#pragma once

#include "SFML/Graphics.hpp"
#include "Debug.h"
#include "StateManager.h"

class Core // for core functionality like setting up window and running game loop
{
	static sf::RenderWindow* window; // actual window
	static Debug debug; // debug for console
	static StateManager stateManager; // the state manager

public:
	const static int SCREEN_WIDTH = 500;
	const static int SCREEN_HEIGHT = 600;

	static void init(); // initialize the program
	static bool isRunning(); // is it still running?
	static void handleEvents(); // handle keypress and window close
	static void draw(); // draw to window
};