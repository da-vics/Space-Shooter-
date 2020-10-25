#pragma once

#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>

class BaseObjectClass
{

public:
	sf::Sprite Asset;

	BaseObjectClass() = delete;

	BaseObjectClass(std::string, sf::Vector2f, sf::Vector2f);

	void SetAssetPos(sf::Vector2f);
	void SetAssetScale(sf::Vector2f);

private:
	sf::Texture _assetTexture;
};

