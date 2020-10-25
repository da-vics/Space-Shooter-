#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>

using namespace sf;
using namespace std;


class Bullet
{
public:

	CircleShape Shape;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)

	{
		this->Shape.setRadius(radius);
		this->Shape.setFillColor(Color::Red);
	}

private:

};


int main()
{

	RenderWindow window(sf::VideoMode(800, 600), "Davics", Style::Default);
	window.setFramerateLimit(60);

	CircleShape Player(25.f);
	Player.setFillColor(Color::White);
	Player.setPosition(window.getSize().x / 2 - Player.getRadius(), window.getSize().y / 1.2);

	Bullet B1;

	vector<Bullet> bullets;

	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

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

		if (Keyboard::isKeyPressed(Keyboard::A))
			Player.move(-1.f, 0);

		if (Keyboard::isKeyPressed(Keyboard::D))
			Player.move(1.f, 0);

		if (Keyboard::isKeyPressed(Keyboard::W))
			Player.move(0, -1.f);

		if (Keyboard::isKeyPressed(Keyboard::S))
			Player.move(0, 1.f);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			B1.Shape.setPosition(playerCenter);
			B1.currVelocity = aimDirNorm * B1.maxSpeed;
			bullets.push_back(Bullet(B1));
		}

		playerCenter = Vector2f(Player.getPosition().x + Player.getRadius(), Player.getPosition().y + Player.getRadius());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		for (size_t i = 0; i < bullets.size();++i)
		{
			bullets[i].Shape.move(bullets[i].currVelocity);

			if (bullets[i].Shape.getPosition().x <0 || bullets[i].Shape.getPosition().x > window.getSize().x ||
				bullets[i].Shape.getPosition().y <0 || bullets[i].Shape.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);
			}

		}

		window.clear(Color::Black);

		window.draw(Player);

		for (const auto& i : bullets)
			window.draw(i.Shape);

		window.display();

	}

	return 0;
}
