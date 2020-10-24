#include <SFML/Graphics.hpp>

using namespace sf;

enum class EnemyPosition
{
	Right,
	Left

};

int main()
{

	RenderWindow window(sf::VideoMode(600, 400), "Davics", Style::Default);
	window.setFramerateLimit(60);

	CircleShape Enemy(50.f);
	Enemy.setPosition(0.f, 10.f);
	Enemy.setFillColor(Color::Black);
	Enemy.setOutlineColor(Color::Blue);
	Enemy.setOutlineThickness(1.f);

	EnemyPosition EnemyDirection;
	EnemyDirection = EnemyPosition::Right;

	CircleShape Player(15.f);
	Player.setPosition(window.getSize().x / 2, window.getSize().y / 1.2);
	Player.setFillColor(Color::Red);

	bool isShot = false;

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

		if (EnemyDirection == EnemyPosition::Right)
			Enemy.move(0.8f, 0.f);

		else if (EnemyDirection == EnemyPosition::Left)
			Enemy.move(-0.8f, 0.f);

		if (Enemy.getPosition().x <= 0)
			EnemyDirection = EnemyPosition::Right;

		else if (Enemy.getPosition().x + (Enemy.getRadius() * 2) >= window.getSize().x)
			EnemyDirection = EnemyPosition::Left;

		if (Mouse::isButtonPressed(Mouse::Left))
			isShot = true;


		if (isShot)
			Player.move(0, -5.f);

		else
		{
			if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x <= window.getSize().x - (Player.getRadius() * 2))
				Player.setPosition(Mouse::getPosition(window).x, Player.getPosition().y);
		}


		if (Player.getPosition().y < 0 || Player.getGlobalBounds().intersects(Enemy.getGlobalBounds()))
		{
			isShot = false;
			Player.setPosition(window.getSize().x / 2, window.getSize().y / 1.2);
		}


		window.clear(Color::White);
		window.draw(Enemy);
		window.draw(Player);
		window.display();
	}

	return 0;
}
