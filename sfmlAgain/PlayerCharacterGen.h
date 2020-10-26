#pragma once
#include"BulletObj.h"
#include "BaseObjectClass.h"
#include<vector>
#include<cstdlib>
class PlayerCharacterGen :public BaseObjectClass
{

public:

	int PlayerHp = 100;
	std::vector<BulletObj>Bullets;

	PlayerCharacterGen() = delete;

	PlayerCharacterGen(std::string TextureLocation, std::string bulletTexture, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow* window)
		:BaseObjectClass(TextureLocation, pos, scale)
	{
		this->_window = window;
		this->_bullet = new BulletObj(bulletTexture, pos, sf::Vector2f(0.07f, 0.07f));
	}

	~PlayerCharacterGen();

	void PlayerLogic();


private:

	BulletObj* _bullet{ nullptr };
	float _playerWidth = this->Asset.getTextureRect().width * this->Asset.getScale().x;
	float _playerHeight = this->Asset.getTextureRect().height * this->Asset.getScale().y;

	sf::RenderWindow* _window;

	void MovePlayerLogic();
	void FireBullets();

	int _fireTimer = 30;

};

