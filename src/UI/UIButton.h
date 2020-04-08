#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

class UIButton : public UIDragable
{
protected:
	sf::Text text;
	sf::Color color;

public:
	// ����� ���������� ����������� �� ���������, �� ������� � ���������� �������� ��������, ��� �������� �� ��������
	explicit UIButton(UILayer* screenParent);
	//UIButton(const std::string& text, const sf::Color& color, const sf::Font& font);

	void onDraw(sf::RenderWindow &target) override;

	void setColor(const sf::Color& color);

    inline const char *getName() const override { return "UIButton"; };

protected:

	void drawText(sf::RenderTarget& target);
};