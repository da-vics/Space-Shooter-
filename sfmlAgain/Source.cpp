#include <SFML/Graphics.hpp>
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace sf;
using namespace std;

int main()
{

	RenderWindow window(sf::VideoMode(600, 400), "Davics", Style::Default);
	window.setFramerateLimit(60);
	int timer = 0;
	int projectileTimer = 0;


	srand(static_cast<int>(time(NULL)));

	CircleShape Player(30.f);
	Player.setPosition(window.getSize().x / 2, window.getSize().y / 1.2);
	Player.setFillColor(Color::White);

	vector<RectangleShape> EnemyContainer;


	RectangleShape rect;
	rect.setSize(Vector2f(10.f, 10.f));
	rect.setFillColor(Color::Yellow);

	CircleShape Projectiles(5.f);
	Projectiles.setFillColor(Color::Red);

	vector<CircleShape> ProjectileContainer;

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

		if (timer >= 20)
		{
			rect.setPosition((int)rand() % window.getSize().x, (int)rand() % window.getSize().y);
			EnemyContainer.push_back(RectangleShape(rect));

			timer = 0;
		}

		else
			++timer;


		if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x <= window.getSize().x - (Player.getRadius() * 2))
			Player.setPosition(Mouse::getPosition(window).x, Player.getPosition().y);

		for (int i = 0; i < EnemyContainer.size(); ++i)
		{
			EnemyContainer[i].move(0.f, .5f);

			if (EnemyContainer[i].getPosition().y > window.getSize().y ||
				EnemyContainer[i].getGlobalBounds().intersects(Player.getGlobalBounds()))
			{
				EnemyContainer.erase(EnemyContainer.begin() + i);
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left) && projectileTimer >= 20)
		{
			Projectiles.setPosition(Player.getPosition().x + Player.getRadius(), Player.getPosition().y - 10.f);
			ProjectileContainer.push_back(CircleShape(Projectiles));
			projectileTimer = 0;
		}

		else
			projectileTimer++;

		for (int i = 0; i < ProjectileContainer.size(); ++i)
		{
			ProjectileContainer[i].move(0.f, -1.f);

			if (ProjectileContainer[i].getPosition().y < 0)
				ProjectileContainer.erase(ProjectileContainer.begin() + i);
		}

		for (int i = 0; i < EnemyContainer.size(); ++i)
		{
			for (int j = 0;j < ProjectileContainer.size(); ++j)
			{

				if (EnemyContainer[i].getGlobalBounds().intersects(ProjectileContainer[j].getGlobalBounds()))
				{
					ProjectileContainer.erase(ProjectileContainer.begin() + j);
					EnemyContainer.erase(EnemyContainer.begin() + i);
				}
			}
		}


		window.clear(Color::Black);
		window.draw(Player);

		for (const auto& i : EnemyContainer)
			window.draw(i);

		for (const auto& i : ProjectileContainer)
			window.draw(i);

		window.display();

	}

	return 0;
}
