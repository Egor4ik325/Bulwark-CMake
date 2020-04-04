#pragma once
#include <SFML/Graphics.hpp>
#include "UIDragable.h"


class Inventory;
class UIItem;

class InventoryCell : public UIDragable
{
public:
	Inventory* invParent;
	UIItem* uiItem;

	sf::Color selectedColor;
public:
	explicit InventoryCell(Inventory* inventoryParent);

	void update() override;
	void draw(sf::RenderTarget& target) override;

	bool isEmpty();

	void addChild(UIBase* child) override;
	void removeChild(UIBase* address) override;

	//void setItem(UIItem* item);
	void removeItem();
	UIItem* getItem();

    const char *getName() const override;
};

