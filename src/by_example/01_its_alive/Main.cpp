#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "First Window!");

	while(window.isOpen())
	{
		sf::Event event{};
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Blue);
		window.display();
	}

	return EXIT_SUCCESS;
}
