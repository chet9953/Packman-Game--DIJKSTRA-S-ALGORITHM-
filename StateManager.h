#pragma once

#include "SFML/Graphics.hpp"
#include "GameState.h"
#include <stack>

class StateManager // to manage all game states
{
	std::stack<GameState*> gameStates; // the game states

	GameState* getCurrentState() const; // current game state (top of the stack)

public:
	void addGameState(GameState* state); // add new game state
	void loop() const; // run the game loop
	void draw(sf::RenderWindow& window) const; // draw to window
	void keyPressed(int code); // handle keypress event
	void keyReleased(int code); // handle keyrelease event
};