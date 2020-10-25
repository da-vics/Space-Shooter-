#include "PlayerCharacterGen.h"

using namespace sf;


int main()
{

	RenderWindow window(sf::VideoMode(800, 600), "Game Dev", Style::Default);
	window.setFramerateLimit(60);

	PlayerCharacterGen Player("../Textures/playership.png", Vector2f(0.f, 0.f), Vector2f(0.1f, 0.1f), &window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		Player.PlayerLogic();


		window.clear(Color::Black);
		window.draw(Player.Asset);

		for (const auto& i : Player.Bullets)
			window.draw(i.Asset);

		window.display();

	}

	return 0;
}
