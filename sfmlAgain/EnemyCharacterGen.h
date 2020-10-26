#pragma once
#include"BaseObjectClass.h"
class EnemyCharacterGen : public BaseObjectClass
{

public:

	EnemyCharacterGen() = delete;

	EnemyCharacterGen(std::string TextureLocation, sf::Vector2f pos, sf::Vector2f scale, sf::RenderWindow* window)
		:BaseObjectClass(TextureLocation, pos, scale)
	{
		this->_window = window;
	};


	~EnemyCharacterGen() {}

private:

	sf::RenderWindow* _window;

private:

};

