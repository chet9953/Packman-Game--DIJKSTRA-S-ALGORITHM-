#include "TextDisplay.h"
#include "PlayingState.h"
#include "Core.h"

void TextDisplay::check_update_high_score()
{
	if (score < highScore) return;

	highScore = score;
	highScoreText.setString("High Score: " + to_string(highScore));
	PlayingState::update_player_score(score);
}

TextDisplay::TextDisplay()
 :debug("Text Display"), score(0), highScore(0)
{
	texts = { &showTextText, &playerText, &instructionsText, &scoreText, &highScoreText, &leaderboardText };
}

void TextDisplay::init(std::map<std::string, int> leaderboard)
{
	font.loadFromFile("Resources/Fonts/normal.TTF"); // load the normal font

	// setup show text
	showTextText.setString("Click 'T' to toggle all this text");
	showTextText.setPosition(10, 10);

	// setup instructions
	std::string rules[] = 
	{
		"Use WSAD or arrow keys to turn",
		"Eat dots to get scores",
		"Eat the fruit to scare and eat ghosts",
		"Avoid ghosts so you don't die"
	};
	std::string instructions = "Rules:";
	for (int i = 1; i <= 4; i++)
		instructions += "\n" + to_string(i) + ") " + rules[i - 1];
	instructionsText.setString(instructions);
	instructionsText.setPosition(10, 35);

	// set player name text
	auto name = PlayingState::player_name;
	playerText.setString("Player: " + name);
	playerText.setPosition(10, Core::SCREEN_HEIGHT - 20);
	
	// setup score
	scoreText.setString("Score: 0");
	scoreText.setPosition(Core::SCREEN_WIDTH / 2, Core::SCREEN_HEIGHT - 20);

	// setup high score
	auto it = leaderboard.find(name); // find this name in the leaderboard
	if (it == leaderboard.end()) highScore = 0; // name is not present so high score is 0
	else highScore = it->second; // high score is taken from the leaderboard
	highScoreText.setString("High Score: " + to_string(highScore));
	highScoreText.setPosition(Core::SCREEN_WIDTH / 2 + 100, Core::SCREEN_HEIGHT - 20);

	// setup leaderboard
	if (leaderboard.empty()) leaderboardText.setString("No leaderboard yet");
	else
	{
		string leaderboardString = "Leaderboard: ";
		int size = min((int)leaderboard.size(), 5);

		vector<pair<int, string>> sortedLeaderboard;
		for (auto player : leaderboard) sortedLeaderboard.push_back({ -player.second, player.first });
		sort(sortedLeaderboard.begin(), sortedLeaderboard.end());

		for(int i = 0; i < size; i++)
		{
			string name = sortedLeaderboard[i].second;
			int score = -sortedLeaderboard[i].first;

			leaderboardString += "\n" + to_string(i + 1) + ") " + name + " with score of " + to_string(score);
		}

		leaderboardText.setString(leaderboardString);
	}
	leaderboardText.setPosition(10, Core::SCREEN_HEIGHT / 2);

	for(auto text : texts) // for each text
	{
		text->setFont(font); // set font to normal font
		text->setCharacterSize(16);
	}
}

void TextDisplay::increase_score()
{
	score++;
	scoreText.setString("Score: " + to_string(score));
	check_update_high_score();
}

void TextDisplay::clear_score()
{
	score = 0;
	scoreText.setString("Score: 0");
}

int TextDisplay::getScore() const
{
	return score;
}

int TextDisplay::getHighScore() const
{
	return highScore;
}

void TextDisplay::draw(sf::RenderWindow& window) const
{
	for (auto text : texts) window.draw(*text); // draw each text
}