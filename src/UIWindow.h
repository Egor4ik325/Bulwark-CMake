#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

class UIWindow : public  UIDragable
{
protected:
	sf::RectangleShape title;
	bool titleVisible;
	const int TITLE_HEIGHT = 25;
	
	sf::Color bodyColor;
	sf::Color titleColor;
	sf::Color titleSelectedColor;
	sf::Color titleDragColor;

	void applyColors();
public:

	UIWindow(UIScreen* screenParent = nullptr);

	void update() override;
	void draw(sf::RenderTarget & target) override;

	bool isDragAllow() const override;
};