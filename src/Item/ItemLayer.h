#pragma once
#include "Item.h"
#include "Layer.h"

#include <vector>

class LayerStack;

// ������ �������������� ��������
struct ItemInfo
{
	unsigned int maxCount;
};

class ItemLayer : public Layer
{
private:
	std::vector <Item*> items;
	ItemInfo itemInfoArr[10];

public:

    explicit ItemLayer(LayerStack* stack);

    void onUpdate() override;

    void onDraw(sf::RenderWindow &win) override;

    std::string getName() const override;

    void pushItem(Item* item);
    void popItem (Item* item);
	Item* getItem(int tileX, int tileY);
	Item* getItem(sf::Vector2f pos);

	void     setItemInfo(unsigned int id, const ItemInfo& info);
	ItemInfo getItemInfo(unsigned int id);
};
