#include "Testing.h"

#include "Maze.h"
#include "AudioManager.h"
#include "Resources.h"
#include "Time.h"
#include "PlayingState.h"

#include <chrono>
#include <thread>

#include <assert.h>


/* Test Case 1 */

void Testing::test_pathfindinding() // test that pathfinding is working right
{
	Maze maze;

	for(int from = 0; from < Maze::MAP_FULL_SIZE; from++)
	{
		int fromX = from % Maze::SIZE_X;
		int fromY = from / Maze::SIZE_X;

		if (maze.tileBlocksCreature(fromX, fromY)) continue; // it is a wall so ignore it

		for(int x = 0; x < Maze::SIZE_X; x++)
		{
			for(int y = 0; y < Maze::SIZE_Y; y++)
			{
				if (maze.tileBlocksCreature(x, y)) continue; // it is a wall so ignore it

				// we got here, which means this guy has valid price, and therefore his neighbor must have his price - 1

				int cost = maze.getPathCost(fromX, fromY, x, y);

				if(cost > 0)
				{
					bool hasValidNeighbor = false;
					pair<int, int> neighbors[] = { { x - 1, y }, { x + 1, y}, { x, y - 1}, { x, y + 1} };

					for(int i = 0; i < 4; i++)
					{
						int neighborX = neighbors[i].first;
						int neighborY = neighbors[i].second;

						if(maze.is_inside_borders(neighborX, neighborY))
						{
							if(maze.getPathCost(fromX, fromY, neighborX, neighborY) == cost - 1) // found the right neighbor
							{
								hasValidNeighbor = true;
								break;
							}
						}
					}

					assert(hasValidNeighbor);
				}
			}
		}
	}
}


/* Test case 2 */

// test that all audio files load and play fine (will throw error if it fails)
void Testing::test_audio_loading()
{
	auto manager = AudioManager();

	int checkIDs[] = 
	{
		AudioManager::COIN_COLLECTING_SOUND_ID, AudioManager::FRUIT_EATEN_SOUND_ID,
		AudioManager::GHOST_EATEN_SOUND_ID, AudioManager::DEATH_SOUND_ID, AudioManager::OPENING_MUSIC_ID
	};

	for(int i = 0; i < 5; i++)
	{
		manager.play(checkIDs[i]);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}


/* Test case 3 */

// test that both the maze and the creatures sprites are loading correctly (will throw error if it fails)
void Testing::test_sprites_loading()
{
	Resources::load();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Testing Sprites");

	// draw creatures on screen (will throw error if anything went wrong)
	for(int i = 0; i < 22; i++)
	{
		auto sprite = Resources::get(i, false, Direction::NONE);

		int distance = 80;

		int x = (i % 5) * distance;
		int y = (i / 5) * distance;

		sprite->setPosition(x, y);

		window.draw(*sprite);
	}

	window.close(); // done here
}


/* Test case 4 */

void Testing::test_elapsed_time_counting_right() // check that timer works right
{
	Time::init();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Time::tick();

	int elapsed_milliseconds = (int)(Time::elapsed * 1000);

	float difference = abs(elapsed_milliseconds - 2000);

	assert(difference < 15); // check that there is less than 15 milliseconds of innacuracy
}


/* Test case 5 */


void Testing::test_scores_working_right() // checks that scores work right
{
	TextDisplay display;
	map<string, int> leaderboard; // empty because we don't care about the leaderboard

	display.init(leaderboard);

	assert(display.getScore() == 0);
	assert(display.getHighScore() == 0);

	for (int i = 0; i < 10; i++) display.increase_score();

	assert(display.getScore() == 10);
	assert(display.getHighScore() == 10);

	display.clear_score();

	assert(display.getScore() == 0);
	assert(display.getHighScore() == 10);

	for (int i = 0; i < 30; i++) display.increase_score();

	assert(display.getScore() == 30);
	assert(display.getHighScore() == 30);
}