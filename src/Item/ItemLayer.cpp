#include "ItemLayer.h"

#include "Application.h"
#include "Global.h"
#include <iostream>

ItemLayer::ItemLayer(LayerStack *stack) : Layer(*stack)
{
}

void ItemLayer::onUpdate()
{

}

void ItemLayer::onDraw(sf::RenderWindow &win)
{
    for (Item* item : items)
    {
        item->draw(win);
    }
}

void ItemLayer::popItem(Item * item)
{
	// ������� �� ����� ������
	delete item;

	// ������� �� ������
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			// ������� �� ������
			auto iter = items.begin();
			std::advance(iter, i);
			items.erase(iter);
		}
	}
}

void ItemLayer::pushItem(Item * item)
{
	items.push_back(item);
}

Item* ItemLayer::getItem(int tileX, int tileY)
{
	for (Item* item : items)
	{
		sf::Vector2f pointPos(tileX * Application::get().getTileSize(), tileY * Application::get().getTileSize());

		//sf::Vector2f itemCoords(item->GetGlobalPosition());
		//sf::FloatRect itemRect(itemPos, sf::Vector2f( TileSize, TileSize ));
		
		if (item->getGlobalBounds().contains(pointPos))
			return item;
	}

	return nullptr;
}

Item * ItemLayer::getItem(sf::Vector2f pos)
{
	return getItem(pos.x / Application::get().getTileSize(), pos.y / Application::get().getTileSize());
}

void ItemLayer::setItemInfo(unsigned int id, const ItemInfo & info)
{
	itemInfoArr[id] = info;
}

ItemInfo ItemLayer::getItemInfo(unsigned int id)
{
	if (id > 10) return ItemInfo();
	
	return itemInfoArr[id];
}

std::string ItemLayer::getName() const {
	return "ItemLayer";
}


