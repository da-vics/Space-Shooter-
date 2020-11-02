#include "PlayerCharacterGen.h"

void PlayerCharacterGen::MovePlayerLogic()
{
	auto moveStep = 1.5f * this->_dt * this->constMulti;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->Asset.getPosition().x > 0)
	{
		this->Asset.move(-(moveStep), 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		(this->Asset.getPosition().x + this->_playerWidth) < this->_window->getSize().x)
	{
		this->Asset.move(moveStep, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->Asset.getPosition().y > 10.f)
	{
		this->Asset.move(0.f, -(moveStep));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		(this->Asset.getPosition().y + this->_playerHeight) < this->_window->getSize().y)
	{
		this->Asset.move(0.f, moveStep);
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	//{
	//	this->Asset.rotate(0.5f);
	//}


}

void PlayerCharacterGen::FireBullets()
{
	auto moveStep = 2.f * this->_dt * this->constMulti;
	auto fireTimerStep = 35 * this->_dt * this->constMulti;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && (this->_fireTimer * this->_dt * this->constMulti) >= fireTimerStep)
	{
		this->_bullet->Asset.setPosition(this->Asset.getPosition().x + _playerWidth - 20, this->Asset.getPosition().y);
		this->Bullets.push_back(*_bullet);
		_fireTimer = 0;
	}

	else
		++this->_fireTimer;

	for (auto i = 0; i < this->Bullets.size();++i)
	{
		this->Bullets[i].Asset.move(moveStep, 0);
		if (Bullets[i].Asset.getPosition().x > this->_window->getSize().x)
			Bullets.erase(Bullets.begin() + i);
	}

}

void PlayerCharacterGen::PlayerLogic(const float& deltatime)
{
	this->_dt = deltatime;
	this->MovePlayerLogic();
	this->FireBullets();
}

PlayerCharacterGen::~PlayerCharacterGen()
{
	if (_bullet != nullptr)
		delete _bullet;
}
