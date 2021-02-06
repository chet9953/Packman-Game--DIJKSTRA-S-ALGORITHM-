#include "StateManager.h"

GameState * StateManager::getCurrentState() const
{
	return gameStates.top(); // current state is whatever is on top of the gameStates stack
}

void StateManager::addGameState(GameState * state)
{
	gameStates.push(state); // add to states
	state->init(); // initialize this new game state
}

void StateManager::loop() const
{
	getCurrentState()->loop(); // run the game loop of current (top) game state
}

void StateManager::draw(sf::RenderWindow & window) const
{
	getCurrentState()->draw(window); // draw current game state's window
}

void StateManager::keyPressed(int code)
{
	getCurrentState()->keyPressed(code); // handle keypress for current gamestate
}

void StateManager::keyReleased(int code)
{
	getCurrentState()->keyReleased(code); // handle keyrelease for current game state
}
