#include "GameLogic.h"

using namespace sf;


int main()
{

	RenderWindow window(sf::VideoMode(800, 600), "Game Dev", Style::Default);
	window.setFramerateLimit(60);

	GameLogic gameStateLogic(&window);
	gameStateLogic.SetupPlayer("../Textures/playership.png", "../Textures/missile.png", Vector2f(0.f, 0.f), Vector2f(0.1f, 0.1f));
	gameStateLogic.SetupEnemy("../Textures/enemyship.png", Vector2f(0.f, 0.f), Vector2f(0.1f, 0.1f));

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

		gameStateLogic.GamePlayLogic();  ///


		window.clear(Color::Black);

		gameStateLogic.GameCharScreenLoad(); ///

		window.display();

	}

	return 0;
}
