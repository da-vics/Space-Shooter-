#include <SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;


#define DEBUG true;

int main()
{

	RenderWindow window(sf::VideoMode(600, 400), "Davics", Style::Default);
	window.setFramerateLimit(60);

	Texture catTexture;
	Sprite CatSprite;

	Texture dogTexture;
	Sprite DogSprite;

	if (!catTexture.loadFromFile("../Textures/cat.png"))
		cout << "load Failed!" << endl;


	CatSprite.setTexture(catTexture);
	CatSprite.setScale(Vector2f(0.2f, 0.2f));

	if (!dogTexture.loadFromFile("../Textures/dog.png"))
		cout << "load Failed!" << endl;

	DogSprite.setTexture(dogTexture);
	DogSprite.setScale(Vector2f(0.2f, 0.2f));
	DogSprite.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);


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


		window.clear(Color::White);

		window.draw(CatSprite);
		window.draw(DogSprite);

		window.display();

	}

	return 0;
}
