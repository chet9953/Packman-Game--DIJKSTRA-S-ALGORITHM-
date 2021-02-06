#include "Core.h"

#include "PlayingState.h"
#include "Resources.h"
#include "AudioManager.h"

using namespace sf;

RenderWindow* Core::window;
Debug Core::debug("Core");
StateManager Core::stateManager;

void Core::init()
{
	debug.logLine("Init...");
	Resources::load(); // load all sprites (png files for maze and creatures)
	AudioManager::init(); // load all audio files
	window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "PacMan"); // create window
	debug.logLine("Window has been created...");
	stateManager.addGameState(new PlayingState); // this is how we will play
}

bool Core::isRunning()
{
	return window->isOpen(); // if window is still open, game is still running
}

void Core::handleEvents()
{
	Event event;
	while(window->pollEvent(event))
	{
		switch(event.type)
		{
		case Event::Closed:
			debug.logLine("Closing the window...");
			window->close();
			break;

		case Event::KeyPressed:
			stateManager.keyPressed(event.key.code); // call keyPressed on stateManager
			break;

		case Event::KeyReleased:
			stateManager.keyReleased(event.key.code); // call keyReleased on stateManager
			break;
		}
	}
	stateManager.loop(); // call the loop() of stateManager
}

void Core::draw() 
{
	window->clear(Color::Black); // clear window
	stateManager.draw(*window); // draw everything
	window->display(); // display everything
}