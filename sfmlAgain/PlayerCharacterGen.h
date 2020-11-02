#pragma once
#include"BulletObj.h"
#include "BaseObjectClass.h"
#include<vector>
#include<cstdlib>
class PlayerCharacterGen :public BaseObjectClass
{

public:

	float PlayerHp = 300.f;
	int GameScore = 0;
	sf::RectangleShape HealthBar;
	std::vector<BulletObj>Bullets;

	PlayerCharacterGen() = delete;

	PlayerCharacterGen(std::string TextureLocation, std::string bulletTexture, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow* window)
		:BaseObjectClass(TextureLocation, pos, scale)
	{
		this->_window = window;
		this->Asset.setPosition(0.f, 10.f);
		this->_bullet = new BulletObj(bulletTexture, pos, sf::Vector2f(0.07f, 0.07f));
		this->HealthBar.setSize(sf::Vector2f(this->PlayerHp, 10.f));
		this->HealthBar.setFillColor(sf::Color::Red);
		this->HealthBar.setPosition((this->_window->getPosition().x + (this->HealthBar.getSize().x / 2)) / 2, 0.f);
	}

	~PlayerCharacterGen();

	void PlayerLogic(const float&);


private:

	BulletObj* _bullet{ nullptr };
	float _playerWidth = this->Asset.getTextureRect().width * this->Asset.getScale().x;
	float _playerHeight = this->Asset.getTextureRect().height * this->Asset.getScale().y;
	sf::Clock _clock;
	float _dt{};
	float constMulti = 60.f;

	sf::RenderWindow* _window;

	void MovePlayerLogic();
	void FireBullets();

	int _fireTimer = 30;

};

