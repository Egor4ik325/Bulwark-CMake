#include "UIScreen.h"
#include "Global.h"
#include "UIManager.h"

UIScreen::UIScreen(): drag(nullptr), over(nullptr)
{
	UIManager::addScreen(this);
}

void UIScreen::update()
{
	// ������� ��������
	updateDrag();

	over = nullptr;
	//updateOver();
	for (UIBase* c : controls)
	{
		c->update();
	}
}

void UIScreen::updateDrag()
{
	// ���� ��������� ��������� - (������ ���� ���������)
	if (drag == nullptr) return;

	// Dragging
	if (drag->isDragAllow())
	{
	    // �������� �� ������� ���� ���������� ������� ������ ���� ����� UI � �����,
	    // � �������� ��������� ����������
	    sf::Vector2f nextPos = getMouseLocalPos() - drag->getDragOffSet();
	    drag->setPosition(nextPos);
	}
	// Stop dragging
	else{
	    // UI drop method
	    drag->onDrop();
	    // Zero
	    drag = nullptr;
	}
}

void UIScreen::draw(sf::RenderTarget &target)
{
	for (UIBase *c : controls)
	{
		c->draw(target);
	}
}

void UIScreen::addControl(UIDragable* control)
{
	control->setScreenParent(this);
	controls.push_back(control); // ��������� UI � ������
}

//void UIScreen::addControl(UIDragable& control)
//{
//	control.setScreenParent(this);
//	controls.push_back(&control);
//}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	// free memory
	delete controls[index];

	// remove from vector
	auto iter = controls.begin();
	std::advance(iter, index);
	controls.erase(iter);        
}

bool UIScreen::mouseIntersect()
{
	for (UIBase* c : controls)
	{
		if (c->getGlobalBounds().contains(getMouseLocalPos()))
		{
			return true;
		}
	}
	return false;
}

UIScreen::~UIScreen() {
    // free memory
    for (UIBase *c : controls)
    {
        delete c;
    }
}

UIBase *UIScreen::getOver() {

    UIBase* _over = nullptr;
    for(UIBase* c : controls)
    {
        if(c->getGlobalBounds().contains(getMouseLocalPos()))
            _over = c;
    }

    return _over;
}
