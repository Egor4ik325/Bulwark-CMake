#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Layer.h"

class UIDragable;

// ��������������� c���������� �����, �������� UI � ���������� ����������������� � ���� 
// �� ����� �������� ��� ���� �������
/////////////////////////////////
/// A stack of layer that will
/// handle any layer
/////////////////////////////////
class LayerStack
{
private:
    std::vector<Layer*> layers;     // ������ ��� ��������� ������ UI

	//static UIBase* overAll, *dragAll;
public:
    const sf::RenderWindow& window;

    explicit LayerStack(const sf::RenderWindow& window);

	void onUpdate();						 // ��������� �������� UI ������
    void onDraw(sf::RenderWindow &target);  // ������ �������� UI ������

	//UIBase* getMouseOver();
	//UIBase* getMouseDrag();

	bool onMouseButtonPressed(sf::Event& event);

	// �������� ����� Screen ���������� � ������������ ������
	void pushLayer(Layer* layer);
	void popLayer (Layer* layer);


	void onEvent(sf::Event& event);
	//static void pushLayer(UILayer& screen);
	//void popLayer(unsigned int index);
private:

    void updateDrag();
};