#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

/// UIWindowDrag
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

	void applyColors(sf::Event &event);

public:
	explicit UIWindow(UILayer* screenParent);

	void onUpdate() override;
	void onDraw(sf::RenderWindow &target) override;

    void onEvent(sf::Event &event) override;

    //bool isDragAllow() const override;
    bool isDragAllow(const sf::Event &event) const override;

    inline const char *getName() const override { return "UIWindow"; }
};