#pragma once

#include"PlayerCharacterGen.h"
#include"EnemyCharacterGen.h"

class GameLogic
{

public:

	GameLogic() = delete;

	GameLogic(sf::RenderWindow*);

	void SetupPlayer(std::string, std::string, sf::Vector2f, sf::Vector2f);
	void SetupEnemy(std::string, sf::Vector2f, sf::Vector2f);
	void GamePlayLogic();

	void GameCharScreenLoad();

	~GameLogic();

private:
	void RandEnemyGen();
	void MoveEnemy();
	void CollisonDection();
	sf::Font _font;
	sf::Text _uIText;
	sf::Text _uIScore;
	sf::Text _uIGameState;
	std::vector<sf::Sprite> _randEnemys;
	PlayerCharacterGen* _playerCharGen{};
	EnemyCharacterGen* _enemyCharGen{};
	sf::RenderWindow* _gamewindow;
	int _randEnemyTimer = 15;
	bool _gameState{ true };
};

