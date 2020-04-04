#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIScreen.h"

class UIDragable;

// ��������������� c���������� �����, �������� UI � ���������� ����������������� � ���� 
// �� ����� �������� ��� ���� �������
class UIManager
{
private:
	static std::vector<UIScreen*> screens;     // ������ ��� ��������� ������ UI

	//static UIBase* overAll, *dragAll;
public:				 

	static void update();						 // ��������� �������� UI ������
    static void draw(sf::RenderTarget &target);  // ������ �������� UI ������

	static UIBase* getMouseOver();
	static UIBase* getMouseDrag();

	// �������� ����� Screen ���������� � ������������ ������
	static void addScreen(UIScreen* screen);
	//static void addScreen(UIScreen& screen);

	// ������� Screen
	static void deleteScreen(unsigned int index);
	static void deleteScreen(const UIScreen* screen);
	//static void deleteScreen(const UIScreen& screen);

	static UIScreen* getScreen(unsigned int index);
private:

	static void updateDrag();
};