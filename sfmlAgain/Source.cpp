#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{

	RenderWindow window(sf::VideoMode(600, 400), "Davics", Style::Default);
	window.setFramerateLimit(60);


	CircleShape Player(20.f);
	Player.setPosition(window.getSize().x / 2, window.getSize().y / 1.2);
	Player.setFillColor(Color::Red);


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



		if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x <= window.getSize().x - (Player.getRadius() * 2))
			Player.setPosition(Mouse::getPosition(window).x, Player.getPosition().y);



		window.clear(Color::White);
		window.draw(Player);
		window.display();
	}

	return 0;
}
