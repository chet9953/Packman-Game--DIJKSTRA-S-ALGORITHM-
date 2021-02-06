#include "SFML/Graphics.hpp"

#include "Core.h"
#include "PlayingState.h"

using namespace sf;

bool get_player_name() // gets the player name
{
	RenderWindow nameWindow(VideoMode(600, 200), "PacMan Get Name Window");
	Text nameText;
	Font nameFont;

	std::string name = "";

	nameFont.loadFromFile("Resources/Fonts/normal.TTF");

	nameText.setString("Name: ");
	nameText.setFont(nameFont);
	nameText.setPosition(50, 50);

	while(nameWindow.isOpen())
	{
		Event event;
		while (nameWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				nameWindow.close();
				break;

			case Event::KeyPressed:
				int key = event.key.code;

				if(key == Keyboard::BackSpace)
				{
					if (name.size() > 0) name.pop_back(); // remove last lettter entered
				}
				else if(key == Keyboard::Enter)
				{
					if (name.size() > 0) nameWindow.close(); // enter key means time to close this window
				}
				else if(key >= Keyboard::A && key <= Keyboard::Z)
				{
					char pressed = 'a' + (key - Keyboard::A);
					name += pressed;
				}
				break;
			}

			nameText.setString("Name: " + name);
		}

		nameWindow.clear(Color::Black);
		nameWindow.draw(nameText);
		nameWindow.display();
	}

	if (name.size() > 0) // name was selected
	{
		PlayingState::player_name = name; // assign name
		return true;
	}
	else return false; // name was not selected
}

void play()
{
	Core::init(); // initialize the game window

	while(Core::isRunning()) // iterate while game is running
	{
		Core::handleEvents(); // handle keypress events and game loop
		Core::draw(); // draw to screen
	}
}

int main()
{
	bool nameChosen = get_player_name();
	if(nameChosen) play();
	system("pause"); // don't exit right away
}