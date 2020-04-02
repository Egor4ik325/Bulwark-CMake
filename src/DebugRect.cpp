#include "DebugRect.h"

#include <iostream>
#include <vector>

bool DebugRect::enabled;
std::list<sf::RectangleShape> DebugRect::objects;

void DebugRect::addRect(sf::FloatRect Rect, sf::Color color)
{
	if (!enabled) return;
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(Rect.width, Rect.height));
	rect.setPosition(sf::Vector2f(Rect.left, Rect.top));

	rect.setOutlineThickness(1);
	rect.setOutlineColor(color);
	rect.setFillColor(sf::Color::Transparent);

	objects.push_back(rect);
}

void DebugRect::draw(sf::RenderTarget & target)
{
	if (!enabled) return;

	for (auto obj : objects)
		target.draw(obj);

	objects.clear();
}
