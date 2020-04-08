#pragma once
#include "Item.h"


class ItemFood : public Item
{
protected:

	int healthPerEat;

public:
	ItemFood();
	void construct(const sf::Texture &texture, sf::IntRect textureRect, int scale = 4) override;

};

