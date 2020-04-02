#include "UIWindow.h"

#include "UIManager.h"
#include "Global.h"

UIWindow::UIWindow(UIScreen* screenParent): UIDragable(screenParent)
{
	// Name
	name = "UIWindow";
	// Window
	visible = true;
	dragAble = true;
	setSize(sf::Vector2f(300, 200));
	// Colors
	bodyColor = sf::Color(130, 130, 130, 180);
	titleColor = sf::Color(90, 90, 90, 200);
	titleSelectedColor = sf::Color(120, 120, 120, 200);
	// Title
	titleVisible = true;
	title.setSize(sf::Vector2f(getSize().x, TITLE_HEIGHT));
}

void UIWindow::update()
{	
	UIDragable::update();

	// UIWINDOW
	title.setPosition(getPosition());
	applyColors();
}

bool UIWindow::isDragAllow() const
{
	if (screenParent == nullptr)
		return false;

	bool Title = title.getGlobalBounds().contains(getMouseLocalPos());

	return (Title || screenParent->drag == this) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void UIWindow::draw(sf::RenderTarget & target)
{	
	UIDragable::draw(target);

	// UIWINDOW
	if (titleVisible)
	{
		target.draw(title, getViewTransformOffSet());
	}
}

void UIWindow::applyColors()
{
	setFillColor(bodyColor);
	title.setFillColor(titleColor);

	if (screenParent->over == this)
		title.setFillColor(titleSelectedColor);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && screenParent->drag == this)
		title.setFillColor(sf::Color::Red);
}