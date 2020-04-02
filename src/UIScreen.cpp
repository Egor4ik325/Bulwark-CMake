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
	if (drag != nullptr)
	{
		// ���� ��� ��� ���������
		if (drag->isDragAllow())
		{
			// �������� �� ������� ���� ���������� ������� ������ ���� ����� UI � �����,
			// � �������� ��������� ����������
			sf::Vector2f nextPos = getMouseLocalPos() - drag->getDragOffSet();
			drag->setPosition(nextPos);
		}
		// ���� ��� �� ���������
		else
		{
			// ���� ��� �������� ���-�� ����
			if (over != nullptr)
				drag->onDrop();
			else
				drag->onCancelDrag();
	
			// ���������
			drag = nullptr;
		}
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

void UIScreen::addControl(UIDragable& control)
{
	control.setScreenParent(this);
	controls.push_back(&control);
}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	//// ������� �� ������������ ������
	//delete controls[index];       

	// ������� �� ������
	std::vector <UIBase*>::iterator iter = controls.begin();
	std::advance(iter, index);
	controls.erase(iter);        
}

void UIScreen::deleteControls()
{
	//for (UIBase* c : controls)
	//{
	//	delete c;
	//}
	controls.clear();
}

bool UIScreen::mouseIntersect()
{
	bool intersect = false;
	for (UIBase* c : controls)
	{
		if (c->getGlobalBounds().contains(getMouseLocalPos()))
		{
			intersect = true;
			break;
		}
	}

	return intersect;
}

UIScreen::~UIScreen()
{
}
