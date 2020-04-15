#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIDragable.h"


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

	void onUpdate() override;
	void onDraw(sf::RenderWindow &target) override;

	bool isEmpty();

	void addChild(UIBase* child) override;
	void removeChild(UIBase* address) override;

	//void setItem(UIItem* item);
	void removeItem();
	UIItem* getItem();

    inline const char *getName() const override { return "InventoryCell"; }

    void onEvent(sf::Event &event) override;
};

