#pragma once

#include "GameState.h"

#include "Debug.h"
#include "Maze.h"
#include "Creature.h"
#include "PacMan.h"
#include "Ghost.h"

#include "TextDisplay.h"

class PlayingState : public GameState
{
	Debug debug; // Debug object for writing things on console
	Maze* maze; // the maze

	TextDisplay textDisplay;
	bool showText; // should we show the text?

	PacMan* pacman; // the player

	Ghost *blinky, *pinky, *inky, *clyde; // ghosts
	vector<Ghost*> ghosts; // stores all ghosts for simplyfying actions that happen to all of them the same way

public:
	const static int GHOST_START_X = 13; // starting tile x of ghosts
	const static int GHOST_START_Y = 14; // starting tile y of ghosts

	static string player_name; // name of the player

private:
	const static string leaderboardFilePath; // path to the file that stores leaderboard

	const static int PINKY_UNLOCK_SCORE = 5; // score required to unleash Pinky
	const static int INKY_UNLOCK_SCORE = 50; // score required to unleash Inky
	const static int CLYDE_UNLOCK_SCORE = 100; // score required to unleash Clyde

	const static int WINNING_SCORE = 240; // score required to win the game

	const static int MAX_WAIT_TIME = 200; // once waitTime reaches this, time to reset the game

	int waitTime; // waiting timer before we start a new game once the current game is over

	bool pacmanCanMove() const; // can PacMan move?
	void handleGhostMovement(Ghost* ghost); // make the ghosts move in whatever way they are supposed to
	bool ghostCanMove(Ghost* ghost) const; // can this ghost move?
	void teleportTunnels(Creature* creature); // if the creature is in a tunnel, teleport it to the other end
	void handleGhostCollision(Ghost* ghost); // check if ghost is in same spot as player and do something about it

	sf::Sprite getGhostSprite(Ghost* ghost) const; // give the ghost a different sprite (for moving animations or for being scared)

public:
	PlayingState(); // constructor

	void init() override; // initialize the game
	void loop() override; // game loop where all the logic takes place
	void draw(sf::RenderWindow& window) const override; // draw things to window
	void keyPressed(int code) override; // key was pressed, do something about it
	void keyReleased(int code) override; // key was released, do something about it

	map<string, int> loadLeaderboard() const; // load the leaderboard
	static void update_player_score(int score); // write the score into the file
};