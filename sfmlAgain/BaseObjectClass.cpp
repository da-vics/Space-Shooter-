#include "BaseObjectClass.h"

BaseObjectClass::BaseObjectClass(std::string TextureLoacation, sf::Vector2f pos, sf::Vector2f scale) {

	if (!this->_assetTexture.loadFromFile(TextureLoacation))
		std::cout << "error loading file" << std::endl;

	this->Asset.setTexture(this->_assetTexture);

	this->SetAssetPos(pos);
	this->SetAssetScale(scale);

}

void BaseObjectClass::SetAssetPos(sf::Vector2f pos)
{
	this->Asset.setPosition(pos);
}

void BaseObjectClass::SetAssetScale(sf::Vector2f scale)
{
	this->Asset.setScale(scale);
}
