#include "Item.h"
#include "Global.h"
#include "ItemManager.h"

Item::Item(const sf::Texture & texture, sf::IntRect TextureRect, int Scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(TextureRect);
	sprite.setScale(Scale, Scale);
}

void Item::construct(const sf::Texture & texture, sf::IntRect TextureRect, int Scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(TextureRect);
	sprite.setScale(Scale, Scale);
}

void Item::draw(sf::RenderTarget &target)
{
	if (onGround)
		target.draw(sprite);
	else
		target.draw(sprite, getViewTransformOffSet());
}

sf::Vector2f Item::getGlobalPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Item::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Item::setTilePosition(sf::Vector2f tilePos)
{
	sprite.setPosition(sf::Vector2f(tilePos.x * TILE_SIZE, tilePos.y * TILE_SIZE));
}

void Item::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
