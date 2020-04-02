#include "ItemManager.h"
#include <iostream>
#include "Global.h"

std::vector <Item*> ItemManager::items;
ItemInfo ItemManager::itemInfoArr[];

void ItemManager::deleteItem(Item * item)
{
	// Удаляем из динам памяти
	delete item;

	// Удаляем из списка
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			// Удаляем из списка
			std::vector <Item*>::iterator iter = items.begin();
			std::advance(iter, i);
			items.erase(iter);
		}
	}
}

void ItemManager::addItem(Item * item)
{
	items.push_back(item);
}

void ItemManager::draw(sf::RenderTarget& target)
{
	for (Item* item : items)
	{
		(*item).draw(target);
	}
}

Item* ItemManager::getItem(int tileX, int tileY)
{
	for (Item* item : items)
	{
		sf::Vector2f pointPos(tileX * TILE_SIZE, tileY * TILE_SIZE);

		//sf::Vector2f itemCoords(item->GetGlobalPosition());
		//sf::FloatRect itemRect(itemPos, sf::Vector2f( TILE_SIZE, TILE_SIZE ));
		
		if (item->getGlobalBounds().contains(pointPos))
			return item;
	}

	return nullptr;
}

Item * ItemManager::getItem(sf::Vector2f pos)
{
	return getItem(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
}

void ItemManager::setItemInfo(unsigned int id, const ItemInfo & info)
{
	itemInfoArr[id] = info;
}

ItemInfo ItemManager::getItemInfo(unsigned int id)
{
	if (id > 10) return ItemInfo();
	
	return itemInfoArr[id];
}
