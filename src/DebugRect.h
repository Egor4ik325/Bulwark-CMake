#pragma once
#include "SFML/Graphics.hpp"
#include <list>

class DebugRect
{
public:
	static bool enabled;
	static std::list <sf::RectangleShape> objects; // Тут хранятся все рисуемые фигуры

public:
	static void addRect(sf::FloatRect, sf::Color color);
	static void draw(sf::RenderTarget & target);
};