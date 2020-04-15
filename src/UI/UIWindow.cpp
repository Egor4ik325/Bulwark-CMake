#include "UIWindow.h"

#include "Application.h"
#include "LayerStack.h"
#include "UI/UILayer.h"
#include "Global.h"

UIWindow::UIWindow(UILayer* screenParent): UIDragable(screenParent),
    titleVisible      (true),
    bodyColor         (sf::Color(130, 130, 130, 180)),
    titleColor        (sf::Color(90, 90, 90, 200)),
    titleSelectedColor(sf::Color(120, 120, 120, 200))
{
	// Window
	visible = true;
	dragAble = true;
	setSize(sf::Vector2f(300, 200));
    setFillColor(bodyColor);
	// Title
	title.setSize(sf::Vector2f(getSize().x, TITLE_HEIGHT));
	title.setFillColor(titleColor);
}

void UIWindow::onUpdate()
{
    UIDragable::onUpdate();

	// UIWINDOW
	title.setPosition(getPosition());
    //applyColors(<#initializer#>);
}

//bool UIWindow::isDragAllow() const
//{
//	//if (layerParent == nullptr)
//	//	return false;
////
//	//bool Title = title.getGlobalBounds().contains(GETMOUSELOCAL(Application::get().getWindow()));
////
//	//return (Title || layerParent->drag == this) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
//}

bool UIWindow::isDragAllow(const sf::Event &event) const
{
    if(layerParent == nullptr) return false;

    if(event.type == sf::Event::MouseButtonPressed || layerParent->drag == this)
        if(event.mouseButton.button == sf::Mouse::Left)
            return true;

    return false;
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

void UIWindow::onEvent(sf::Event &event) {
    UIDragable::onEvent(event);

    if(event.type)
    applyColors(event);
}

void UIWindow::applyColors(sf::Event &event)
{
    // If mouse over
    if (layerParent->over == this)
        title.setFillColor(titleSelectedColor);

    // If mouse pressed - onMousePressed - create function
    if(event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (layerParent->drag == this)
            title.setFillColor(sf::Color::Red);
    }

    // If mouse released
    if(event.type == sf::Event::MouseButtonReleased)
    {
        setFillColor(bodyColor);
        title.setFillColor(titleColor);
        return;
    }


}