#pragma once
#include <SFML/Graphics.hpp>

enum ItemType
{
	Weapon = 0,
	Tool,
	Spell,
	Food,
	Arrmor
};

class Item
{
protected:
	// Собственные данные
	sf::Sprite sprite;

	unsigned int id;
	unsigned int count;
	
	ItemType type;

public:
	bool onGround;

	Item() = default;
	Item(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void construct(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void draw(sf::RenderTarget &target);

	void setTilePosition(sf::Vector2f tilePos);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getGlobalPosition();
	sf::FloatRect getGlobalBounds();
};