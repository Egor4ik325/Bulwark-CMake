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
	explicit UIWindow(UILayer* screenParent);

	void onUpdate() override;
	void onDraw(sf::RenderWindow &target) override;

    bool isDragAllow() const override;

    inline const char *getName() const override { return "UIWindow"; }
};