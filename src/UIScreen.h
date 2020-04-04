#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

// ����� - ������ �����������
class UIScreen
{
public:
	std::vector <UIBase*> controls; // ������ UI �� ������. ������ Heap
	UIDragable* over, *drag;

public:
	bool visible = false;

	UIScreen();

	void update();
	void draw(sf::RenderTarget &target);

	// �������� UI ��� ���������� � Managment
	void addControl(UIDragable* control);
	void deleteControl(unsigned int index);
	bool mouseIntersect();

	UIBase* getOver();

	~UIScreen();
private:
	void updateDrag();
};