#include "GameLogic.h"

GameLogic::GameLogic(sf::RenderWindow* window)
{
	srand(static_cast<int>(time(NULL)));

	this->_gamewindow = window;

	if (!this->_font.loadFromFile("../Fonts/Handlee.ttf"))
		std::cout << "error" << std::endl;

	this->_uIText.setFont(this->_font);
	this->_uIText.setString("HP:");
	this->_uIText.setFillColor(sf::Color::Red);
	this->_uIText.setScale(0.4f, 0.4f);
	this->_uIText.setStyle(sf::Text::Bold);

	this->_uIScore.setFont(this->_font);
	this->_uIScore.setString("Score:");
	this->_uIScore.setFillColor(sf::Color::White);
	this->_uIScore.setScale(0.4f, 0.4f);
	this->_uIScore.setStyle(sf::Text::Bold);

	this->_uIGameState = this->_uIScore;
	this->_uIGameState.setPosition((this->_gamewindow->getSize().x / 2) - this->_uIScore.getCharacterSize(), this->_gamewindow->getSize().y / 2);
	this->_uIGameState.setScale(0.8f, 0.8f);
	this->_uIGameState.setString("Game Over!");
}

void GameLogic::SetupPlayer(std::string TextureLocation, std::string bulletLocation, sf::Vector2f pos, sf::Vector2f scale)
{
	this->_playerCharGen = new PlayerCharacterGen(TextureLocation, bulletLocation, pos, scale, _gamewindow);
	this->_uIText.setPosition(this->_playerCharGen->HealthBar.getPosition().x - this->_uIText.getCharacterSize(), 0.0f);
}


void GameLogic::SetupEnemy(std::string TextureLocation, sf::Vector2f pos, sf::Vector2f scale)
{
	this->_enemyCharGen = new EnemyCharacterGen(TextureLocation, pos, scale, _gamewindow);
}


void GameLogic::GamePlayLogic()
{
	if (this->_gameState)
	{
		this->_dt = this->_clock.restart().asSeconds();
		this->_playerCharGen->PlayerLogic(this->_dt);
		this->RandEnemyGen();
		this->MoveEnemy();
		this->CollisonDection();
	}

}

void GameLogic::RandEnemyGen()
{
	auto enemyRandGen = 35.f * this->_dt * this->constMulti;

	//std::cout << this->_randEnemyTimer << std::endl;
	//std::cout << "const : " << enemyRandGen << std::endl;

	if ((this->_randEnemyTimer * this->_dt * this->constMulti) >= enemyRandGen)
	{
		auto temp = this->_enemyCharGen->Asset.getTextureRect().height * this->_enemyCharGen->Asset.getScale().y;
		this->_enemyCharGen->Asset.setPosition(rand() % this->_gamewindow->getSize().x + 400, (rand() % this->_gamewindow->getSize().y - temp) + 80.f);
		this->_randEnemys.push_back(this->_enemyCharGen->Asset);
		this->_randEnemyTimer = 0;
	}

	else
		this->_randEnemyTimer++;
}

void GameLogic::GameCharScreenLoad()
{
	auto temp = "Score : " + std::to_string(this->_playerCharGen->GameScore);
	this->_uIScore.setString(temp);
	this->_gamewindow->draw(this->_uIText);
	this->_gamewindow->draw(this->_uIScore);
	this->_gamewindow->draw(this->_playerCharGen->HealthBar);
	this->_gamewindow->draw(this->_playerCharGen->Asset);

	for (const auto& i : this->_playerCharGen->Bullets)
		this->_gamewindow->draw(i.Asset);

	for (const auto& i : this->_randEnemys)
		this->_gamewindow->draw(i);

	if (!this->_gameState)
		this->_gamewindow->draw(this->_uIGameState);

}

void GameLogic::MoveEnemy()
{
	auto moveStep = 2.f * this->_dt * this->constMulti;

	for (size_t assetIndex = 0; assetIndex < this->_randEnemys.size(); ++assetIndex)
	{
		this->_randEnemys[assetIndex].move(-(moveStep), 0.f);

		auto temp = this->_randEnemys[assetIndex].getTextureRect().width * this->_randEnemys[assetIndex].getScale().x;

		if ((this->_randEnemys[assetIndex].getPosition().x + temp) < 0)
			this->_randEnemys.erase(this->_randEnemys.begin() + assetIndex);

		if (this->_playerCharGen->Asset.getGlobalBounds().intersects(this->_randEnemys[assetIndex].getGlobalBounds()))
		{
			this->_randEnemys.erase(this->_randEnemys.begin() + assetIndex);

			(this->_playerCharGen->PlayerHp > 0) ? this->_playerCharGen->PlayerHp -= 10 : this->_playerCharGen->PlayerHp = 0;

			this->_playerCharGen->HealthBar.setSize(sf::Vector2f(this->_playerCharGen->PlayerHp, 10.f));

			if (this->_playerCharGen->PlayerHp <= 0)
			{
				this->_gameState = false;
			}
		}
	}
}

void GameLogic::CollisonDection()
{
	for (size_t i = 0; i < this->_randEnemys.size(); ++i)
	{
		for (size_t j = 0; j < this->_playerCharGen->Bullets.size(); ++j)
		{
			if (this->_playerCharGen->Bullets[j].Asset.getGlobalBounds().intersects(this->_randEnemys[i].getGlobalBounds()))
			{
				this->_playerCharGen->Bullets.erase(this->_playerCharGen->Bullets.begin() + j);
				this->_randEnemys.erase(this->_randEnemys.begin() + i);
				this->_playerCharGen->GameScore += 10;
				break;
			}
		}
	}
}

GameLogic::~GameLogic()
{
	if (this->_playerCharGen != nullptr)
		delete this->_playerCharGen;

	if (this->_enemyCharGen != nullptr)
		delete this->_enemyCharGen;
}