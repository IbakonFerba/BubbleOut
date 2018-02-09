#include "stdafx.h"

int main()
{
	//create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ZombieArena", sf::Style::Default);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
	std::cout << "bla";

	return 0;
}
