#pragma once
#include <SFML/Graphics.hpp>
#include "UIDragable.h"


class Inventory;
class UIItem;

class InventoryCell : public UIDragable
{
public:
	UIItem* itemContain;

	Inventory* invParent;
	
	sf::Color selectedColor;
public:
	InventoryCell(Inventory* inventoryParent);

	void update() override;
	void draw(sf::RenderTarget& target) override;

	void removeItem();
	bool isEmpty();
	void setItem(UIItem* item);
	UIItem* getItem();
};

