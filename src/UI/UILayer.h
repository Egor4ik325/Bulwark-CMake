#pragma once
#include "SFML/Graphics.hpp"
#include "UI/UIDragable.h"
#include "Layer.h"

class LayerStack;
// ����� - ������ �����������
///////////////////////////////////////
/// A layer that will handle UI
///
///////////////////////////////////////
class UILayer : public Layer
{
public:
    std::vector <UIBase*> controls;
	UIDragable* over, *drag;

public:
	explicit UILayer(LayerStack * stack);
    ~UILayer();

	void onUpdate() override;
	void onDraw(sf::RenderWindow & win) override;

	// �������� UI ��� ���������� � Managment
	void pushControl(UIBase *control);
	void popControl (UIBase *control);

    std::string getName() const override;

    UIBase* getOver();

    void onEvent(sf::Event &event) override;

private:
	void updateDrag(sf::Event &event);
};