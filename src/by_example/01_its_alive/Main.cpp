#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	sf::Texture texture;
	if(!texture.loadFromFile("Mushroom.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(320, 240);
	// By default you the origin is at pixel 0,0 (the top left)
	// So to better position it we can set the origin to the middle
	// Rather than hard code these values we can calculate them
	sf::Vector2u spriteSize = texture.getSize();
	sprite.setOrigin(spriteSize.x / 2.0f, spriteSize.y / 2.0f);

	sf::Vector2f direction(0.2f, 0.2f);
	auto windowSize = window.getSize();
	
	while(window.isOpen()) // The game loop
	{
		sf::Event event{};
		while(window.pollEvent(event)) // Process inputs
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// Lets move our sprint around the screen
		// We just need to check it hasn't gone over the edge and invert the direction if so
		// The origin of sprite is set in the centre, so we need to compensate
		sf::Vector2f spritePos = sprite.getPosition();
		if((spritePos.x + (spriteSize.x / 2.0f) > windowSize.x && direction.x > 0) ||
			spritePos.x - (spriteSize.x / 2.0f) < 0 && direction.x < 0)
		{
			direction.x = -direction.x;
		}
		if((spritePos.y + (spriteSize.y / 2.0f) > windowSize.y && direction.y > 0) ||
			spritePos.y - (spriteSize.y / 2.0f) < 0 && direction.y < 0)
		{
			direction.y = -direction.y;
		}

		sprite.setPosition(spritePos + direction);

		// Set the background
		window.clear(sf::Color(64, 0, 64, 255));
		// Draw our scene
		window.draw(sprite);
		// Swap buffers
		window.display();
	}

	return EXIT_SUCCESS;
}