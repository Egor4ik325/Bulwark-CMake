#include "Item.h"

#include "Application.h"
#include "Global.h"
#include "ItemLayer.h"

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

void Item::draw(sf::RenderWindow &target)
{
	if (onGround)
		target.draw(sprite);
	else
		target.draw(sprite, getViewTransformOffSet(target));
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
	sprite.setPosition(sf::Vector2f(tilePos.x * (float)Application::get().getTileSize(), tilePos.y * (float)Application::get().getTileSize()));
}

void Item::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
