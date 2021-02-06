#pragma once

#include "SFML/Graphics.hpp"

class GameState // overall game manager
{
public:
	const static int TILE_SIZE = 16; // size of tile in pixels
	const static int TILE_HALF = TILE_SIZE / 2; // size of half of the tile

	virtual void init(); // initialize
	virtual void loop() = 0; // run the game loop
	virtual void draw(sf::RenderWindow& window) const = 0; // draw to window
	virtual void keyPressed(int keycode) = 0; // handle key press
	virtual void keyReleased(int keycode) = 0; // handle key release
};