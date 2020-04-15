#include "UILayer.h"

#include "Application.h"
#include "Global.h"
#include "LayerStack.h"

UILayer::UILayer(LayerStack* stack): Layer(*stack),
    drag(nullptr), over(nullptr)
{
}

UILayer::~UILayer()
{
	// free memory
	for (UIBase *c : controls)
	{
		delete c;
	}
}

void UILayer::onUpdate()
{
	// ������� ��������
	//updateDrag();

	over = nullptr;
	//updateOver();
	for (UIBase* c : controls)
	{
        c->onUpdate();
	}
}

void UILayer::updateDrag(sf::Event &event)
{
	// ���� ��������� ��������� - (������ ���� ���������)
	if (drag == nullptr) return;
	if(event.type != sf::Event::MouseMoved) return;

	// Dragging
	if (drag->isDragAllow(event))
	{
	    // �������� �� ������� ���� ���������� ������� ������ ���� ����� UI � �����,
	    // � �������� ��������� ����������
	    sf::Vector2f nextPos = GETMOUSELOCAL(Application::get().getWindow()) - drag->getDragOffSet();
	    drag->setPosition(nextPos);
	}
	// Drag end
	else{
	    // UI drop method
	    drag->onDrop();
	    // Zero
	    drag = nullptr;
	}
}

void UILayer::onDraw(sf::RenderWindow & win)
{
	for (UIBase *c : controls)
	{
		c->onDraw(win);
	}
}

void UILayer::pushControl(UIBase *control)
{
    control->setLayerParent(this);
	controls.push_back(control); // ��������� UI � ������
}

void UILayer::popControl(UIBase *control)
{
	std::vector<UIBase *>::iterator iter = std::find(controls.begin(), controls.end(), control);
	// Remove from vector
	controls.erase(iter);
}

UIBase *UILayer::getOver()
{
	UIBase* _over = nullptr;
	for(UIBase* c : controls)
	{
		auto mouseLocalPos = GETMOUSELOCAL(Application::get().getWindow());;
		if(c->getGlobalBounds().contains(mouseLocalPos))
			_over = c;
	}

	return _over;
}

std::string UILayer::getName() const {
    return "UILayer";
}

void UILayer::onEvent(sf::Event &event)
{
    updateDrag(event);

    for(UIBase* c : controls)
    {
        c->onEvent(event);
    }
}