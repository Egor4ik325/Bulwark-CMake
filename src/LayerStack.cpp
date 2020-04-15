#include "LayerStack.h"

#include <iostream>
#include <iterator>

//UIBase* LayerStack::overAll = nullptr;
//UIBase* LayerStack::dragAll = nullptr;

LayerStack::LayerStack(const sf::RenderWindow &window):
    window(window)
{
}

void LayerStack::onUpdate()
{
	//updateDrag();

	for (Layer* layer : layers)
	{
		if (!layer->isVisible()) continue;

        layer->onUpdate();
		// ������� ���� ����� ��������� �� *Drag � *Over
		//dragAll = layer->drag;
		//overAll = layer->over;
	}	
}

void LayerStack::updateDrag()
{
}

void LayerStack::onDraw(sf::RenderWindow &target)
{
    // Draw layer in right order, from 0
	for (Layer* layer : layers)
	{
		if (!layer->isVisible()) continue;

        layer->onDraw(target);
	}
}

//UIBase* LayerStack::getMouseOver()
//{
//	UIBase* over = nullptr;
//	for (UILayer* layer : layers)
//	{
//		if (!layer->visible) continue;
//		if (layer->getOver() == nullptr) continue;
//
//		over = layer->over;
//	}
//
//	return over;
//}
//
//UIBase* LayerStack::getMouseDrag()
//{
//	UIBase* drag = nullptr;
//	for (UILayer* layer : layers)
//	{
//		if (!layer->visible) continue;
//		if (layer->drag == nullptr) continue;
//
//		drag = layer->over;
//	}
//	return drag;
//}

void LayerStack::pushLayer(Layer * layer)
{
	layers.push_back(layer);
}

void LayerStack::popLayer(Layer * layer)
{
    auto iter = std::find(layers.begin(), layers.end(), layer);

    if(iter != layers.end())
    {
        layers.erase(iter);
    }

    //for (int i = 0; i < layers .size(); i++)
    //{
    //	if (layers[i] == screen)
    //	{
    //        popLayer(i);
    //	}
    //}
}

bool LayerStack::onMouseButtonPressed(sf::Event &event) {

    return false;
}

void LayerStack::onEvent(sf::Event &event)
{
    for(Layer* layer : layers)
    {
        layer->onEvent(event);
    }
}

//void LayerStack::popLayer(unsigned int index)
//{
//	if (index > layers.size()) return;
//
//	// free memory
//	delete layers[index];
//
//	// remove from vector
//	auto iter = layers.begin();
//	std::advance(iter, index);
//	layers.erase(iter);
//}

//void LayerStack::pushControl(unsigned int screenIndex, UIBase* controlAdress)
//{
//	if (screenIndex > layers.size()) return;
//
//	layers[screenIndex]->pushControl(controlAdress);
//}
//
//void LayerStack::popControl(unsigned int screenIndex, unsigned int controlIndex)
//{
//	if (screenIndex > layers.size()) return;
//	if (controlIndex > layers[screenIndex]->controls.size()) return;
//
//	layers[screenIndex]->popControl(controlIndex);
//}
