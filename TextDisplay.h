#pragma once

#include <SFML/Graphics.hpp>
#include "Debug.h"

class TextDisplay
{
	Debug debug; // debugger

	sf::Font font;

	sf::Text showTextText, playerText, scoreText, highScoreText, leaderboardText, instructionsText;
	std::vector<sf::Text*> texts;

	int score;
	int highScore;

	void check_update_high_score(); // check if it's time to update the high score and update the leaderboard accordingly

public:
	TextDisplay(); // constructor
	
	void init(std::map<std::string, int> leaderboard); // initialize the texts
	void increase_score(); // add 1 to current score
	void clear_score(); // clear current score

	int getScore() const;
	int getHighScore() const;

	void draw(sf::RenderWindow& window) const; // draw texts to window
};