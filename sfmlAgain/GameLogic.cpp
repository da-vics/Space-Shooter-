#include "GameLogic.h"

void GameLogic::SetupPlayer(std::string TextureLocation, std::string bulletLocation, sf::Vector2f pos, sf::Vector2f scale)
{
	this->_playerCharGen = new PlayerCharacterGen(TextureLocation, bulletLocation, pos, scale, _gamewindow);
	this->_uIText.setPosition(this->_playerCharGen->HealthBar.getPosition().x - this->_uIText.getCharacterSize(), 0.0f);
}


void GameLogic::SetupEnemy(std::string TextureLocation, sf::Vector2f pos, sf::Vector2f scale)
{
	this->_enemyCharGen = new  EnemyCharacterGen(TextureLocation, pos, scale, _gamewindow);
}


void GameLogic::GamePlayLogic()
{
	this->_playerCharGen->PlayerLogic();
	this->RandEnemyGen();
	this->MoveEnemy();
	this->CollisonDection();
}

void GameLogic::RandEnemyGen()
{
	if (this->_randEnemyTimer >= 15)
	{
		this->_enemyCharGen->Asset.setPosition((int)rand() % this->_gamewindow->getSize().x + 400, (int)rand() % this->_gamewindow->getSize().y + 10.f);
		this->_randEnemys.push_back(this->_enemyCharGen->Asset);
		this->_randEnemyTimer = 0;
	}

	else
		this->_randEnemyTimer++;

}

void GameLogic::GameCharScreenLoad() const
{
	this->_gamewindow->draw(this->_uIText);
	this->_gamewindow->draw(this->_playerCharGen->HealthBar);
	this->_gamewindow->draw(this->_playerCharGen->Asset);

	for (const auto& i : this->_playerCharGen->Bullets)
		this->_gamewindow->draw(i.Asset);

	for (const auto& i : this->_randEnemys)
		this->_gamewindow->draw(i);

}

void GameLogic::MoveEnemy()
{

	for (size_t assetIndex = 0; assetIndex < this->_randEnemys.size(); ++assetIndex)
	{
		this->_randEnemys[assetIndex].move(-1.2f, 0.f);

		auto temp = this->_randEnemys[assetIndex].getTextureRect().width * this->_randEnemys[assetIndex].getScale().x;

		if ((this->_randEnemys[assetIndex].getPosition().x + temp) < 0)
			this->_randEnemys.erase(this->_randEnemys.begin() + assetIndex);

		if (this->_playerCharGen->Asset.getGlobalBounds().intersects(this->_randEnemys[assetIndex].getGlobalBounds()))
		{
			this->_randEnemys.erase(this->_randEnemys.begin() + assetIndex);
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