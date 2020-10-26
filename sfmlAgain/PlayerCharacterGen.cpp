#include "PlayerCharacterGen.h"

void PlayerCharacterGen::MovePlayerLogic()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->Asset.getPosition().x > 0)
	{
		this->Asset.move(-1.4f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		(this->Asset.getPosition().x + this->_playerWidth) < this->_window->getSize().x)
	{
		this->Asset.move(1.4f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->Asset.getPosition().y > 0)
	{
		this->Asset.move(0.f, -1.4f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		(this->Asset.getPosition().y + this->_playerHeight) < this->_window->getSize().y)
	{
		this->Asset.move(0.f, 1.4f);
	}

}

void PlayerCharacterGen::FireBullets()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && this->_fireTimer >= 25)
	{
		this->_bullet->Asset.setPosition(this->Asset.getPosition().x + _playerWidth - 20, this->Asset.getPosition().y);
		this->Bullets.push_back(*_bullet);

		_fireTimer = 0;
	}

	else
		++this->_fireTimer;

	for (auto i = 0; i < this->Bullets.size();++i)
	{
		this->Bullets[i].Asset.move(2.f, 0);
		if (Bullets[i].Asset.getPosition().x > this->_window->getSize().x)
			Bullets.erase(Bullets.begin() + i);
	}

}

void PlayerCharacterGen::PlayerLogic()
{
	this->MovePlayerLogic();
	this->FireBullets();
}

PlayerCharacterGen::~PlayerCharacterGen()
{
	if (_bullet != nullptr)
		delete _bullet;
}
