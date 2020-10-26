#pragma once

#include"PlayerCharacterGen.h"
#include"EnemyCharacterGen.h"

class GameLogic
{

public:

	GameLogic() = delete;

	GameLogic(sf::RenderWindow* window) : _gamewindow{ window } { srand(static_cast<int>(time(NULL))); }

	void SetupPlayer(std::string, std::string, sf::Vector2f, sf::Vector2f);
	void SetupEnemy(std::string, sf::Vector2f, sf::Vector2f);
	void GamePlayLogic();

	void GameCharScreenLoad() const;

	~GameLogic();

private:
	void RandEnemyGen();
	void MoveEnemy();
	void CollisonDection();
	std::vector<sf::Sprite> _randEnemys;
	PlayerCharacterGen* _playerCharGen{};
	EnemyCharacterGen* _enemyCharGen{};
	sf::RenderWindow* _gamewindow;
	int _randEnemyTimer = 15;
};

