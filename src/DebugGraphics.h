#pragma once
#include "SFML/Graphics.hpp"

#include <list>

class DebugGraphics
{
public:
	static bool enabled;
	static std::list <sf::RectangleShape> objects; // ��� �������� ��� �������� ������

public:
	static void addRect(sf::FloatRect, sf::Color color);
	static void draw(sf::RenderTarget & target);
};