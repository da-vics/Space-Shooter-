#pragma once
#include "BaseObjectClass.h"
class BulletObj :public BaseObjectClass
{
public:


	BulletObj() = delete;

	BulletObj(std::string TextureLocation, sf::Vector2f pos, sf::Vector2f scale)
		:BaseObjectClass(TextureLocation, pos, scale)
	{

	}

private:


};

