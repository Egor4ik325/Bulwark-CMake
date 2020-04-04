#include "UIManager.h"
#include "UIDragable.h"
#include <iostream>
#include <iterator>

std::vector <UIScreen*> UIManager::screens;

//UIBase* UIManager::overAll = nullptr;
//UIBase* UIManager::dragAll = nullptr;

void UIManager::update()
{
	//updateDrag();

	for (UIScreen* screen : screens)
	{
		if (!screen->visible) continue;
	
		screen->update();
		// ������� ���� ����� ��������� �� *Drag � *Over
		//dragAll = screen->drag;
		//overAll = screen->over;
	}	
}

void UIManager::updateDrag()
{
}

void UIManager::draw(sf::RenderTarget & target)
{
	for (UIScreen* screen : screens)
	{
		if (!screen->visible) continue;

		screen->draw(target);
	}
}

UIBase* UIManager::getMouseOver()
{
	UIBase* over = nullptr;
	for (UIScreen* screen : screens)
	{
		if (!screen->visible) continue;
		if (screen->over == nullptr) continue;

		over = screen->over;
	}

	return over;
}

UIBase* UIManager::getMouseDrag()
{
	UIBase* drag = nullptr;
	for (UIScreen* screen : screens)
	{
		if (!screen->visible) continue;
		if (screen->drag == nullptr) continue;

		drag = screen->over;
	}
	return drag;
}

void UIManager::addScreen(UIScreen * uiscreen)
{
	screens.push_back(uiscreen);
}

void UIManager::deleteScreen(unsigned int index)
{
	if (index > screens.size()) return;

	// free memory
	delete screens[index];

	// remove from vector
	auto iter = screens.begin();
	std::advance(iter, index);
	screens.erase(iter);
}

void UIManager::deleteScreen(const UIScreen * screen)
{
	for (int i = 0; i < screens.size(); i++)
	{
		if (screens[i] == screen)
		{
			deleteScreen(i);
		}
	}
}

UIScreen * UIManager::getScreen(unsigned int index)
{
	if (index > screens.size())
		return nullptr;
	return screens[index];
}

//void UIManager::addControl(unsigned int screenIndex, UIBase* controlAdress)
//{
//	if (screenIndex > screens.size()) return;
//
//	screens[screenIndex]->addControl(controlAdress);
//}
//
//void UIManager::deleteControl(unsigned int screenIndex, unsigned int controlIndex)
//{
//	if (screenIndex > screens.size()) return;
//	if (controlIndex > screens[screenIndex]->controls.size()) return;
//
//	screens[screenIndex]->deleteControl(controlIndex);
//}
