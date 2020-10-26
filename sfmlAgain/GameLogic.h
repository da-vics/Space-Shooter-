#pragma once

#include"PlayerCharacterGen.h"
#include"EnemyCharacterGen.h"

class GameLogic
{

public:

	GameLogic() = delete;

	GameLogic(sf::RenderWindow* window) : _gamewindow{ window }
	{
		srand(static_cast<int>(time(NULL)));

		if (!this->_font.loadFromFile("../Fonts/Handlee.ttf"))
			std::cout << "error" << std::endl;

		this->_uIText.setFont(this->_font);
		this->_uIText.setString("HP:");
		this->_uIText.setFillColor(sf::Color::Red);
		this->_uIText.setScale(0.4f, 0.4f);
		this->_uIText.setStyle(sf::Text::Bold);
	}

	void SetupPlayer(std::string, std::string, sf::Vector2f, sf::Vector2f);
	void SetupEnemy(std::string, sf::Vector2f, sf::Vector2f);
	void GamePlayLogic();

	void GameCharScreenLoad() const;

	~GameLogic();

private:
	void RandEnemyGen();
	void MoveEnemy();
	void CollisonDection();
	sf::Font _font;
	sf::Text _uIText;
	std::vector<sf::Sprite> _randEnemys;
	PlayerCharacterGen* _playerCharGen{};
	EnemyCharacterGen* _enemyCharGen{};
	sf::RenderWindow* _gamewindow;
	int _randEnemyTimer = 15;
};

