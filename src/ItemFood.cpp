#include "ItemFood.h"

ItemFood::ItemFood()
{
}

void ItemFood::construct(const sf::Texture& texture, sf::IntRect textureRect, int scale)
{
	Item::construct(texture, textureRect, scale);
}
