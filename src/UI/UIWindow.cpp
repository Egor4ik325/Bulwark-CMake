#include "UIWindow.h"

#include "LayerStack.h"
#include "UI/UILayer.h"
#include "Global.h"

UIWindow::UIWindow(UILayer* screenParent): UIDragable(screenParent)
{
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

void UIWindow::onUpdate()
{
    UIDragable::onUpdate();

	// UIWINDOW
	title.setPosition(getPosition());
	applyColors();
}

bool UIWindow::isDragAllow() const
{
	if (layerParent == nullptr)
		return false;

	bool Title = title.getGlobalBounds().contains(getMouseLocalPos(layerParent->window));

	return (Title || layerParent->drag == this) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void UIWindow::onDraw(sf::RenderWindow &target)
{
    UIDragable::onDraw(target);

	// UIWINDOW
	if (titleVisible)
	{
		target.draw(title, getViewTransformOffSet(target));
	}
}

void UIWindow::applyColors()
{
	setFillColor(bodyColor);
	title.setFillColor(titleColor);

	if (layerParent->over == this)
		title.setFillColor(titleSelectedColor);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && layerParent->drag == this)
		title.setFillColor(sf::Color::Red);
}