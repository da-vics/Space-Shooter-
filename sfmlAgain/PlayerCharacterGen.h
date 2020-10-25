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

	PlayerCharacterGen(std::string TextureLocation, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow* window)
		:BaseObjectClass(TextureLocation, pos, scale)
	{
		this->_window = window;
		this->_bullet = new BulletObj("../Textures/missile.png", pos, scale);
		srand(static_cast<int>(time(NULL)));
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

};

