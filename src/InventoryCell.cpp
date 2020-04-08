#include "InventoryCell.h"
#include "UI/UIItem.h"
#include "Global.h"
#include "Content.h"
#include "Inventory.h"

InventoryCell::InventoryCell(Inventory* inv) : UIDragable(inv->layerParent),
    invParent(inv),
    uiItem(nullptr),
    selectedColor(sf::Color::Black)
{
	// Properties
	layerParent = inv->layerParent;
	dragAble = false;
	// ������������� ��������
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setTexture(&Content::invCellTexture, true);
	setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void InventoryCell::onUpdate()
{
	if (uiItem != nullptr && !uiItem->isDragAllow())
	{
		// ������� Item ������
		uiItem->setPosition(getPosition());
	}
    UIDragable::onUpdate();
}

void InventoryCell::onDraw(sf::RenderWindow &target)
{
	if (invParent->getSelectedCell() == this)
		setFillColor(selectedColor);
	else
		setFillColor(sf::Color::White);

	UIDragable::onDraw(target);
}

//void InventoryCell::setItem(UIItem * item)
//{
//    uiItem = item;
//	uiItem->setParent(this);
//    uiItem->item.onGround = false;
//	uiItem->setPosition(getPosition());
//	// add to childs
//	addChild(uiItem);
//}


void InventoryCell::addChild(UIBase *child)
{
    UIBase::addChild(child);

    if(child->getName() == "UIItem")
    {
        auto* item = (UIItem*) child;
        uiItem = item;
    }
}

void InventoryCell::removeChild(UIBase *child)
{
    UIBase::removeChild(child);

    if(child->getName() == "UIItem")
    {
        uiItem = nullptr;
    }
}

void InventoryCell::removeItem()
{
    // remove from childs
    removeChild(uiItem);
    uiItem = nullptr;
}

UIItem * InventoryCell::getItem()
{
	return uiItem;
}

bool InventoryCell::isEmpty()
{
	return uiItem == nullptr;
}