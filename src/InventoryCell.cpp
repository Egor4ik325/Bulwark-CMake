#include "InventoryCell.h"
#include "UIItem.h"
#include "Global.h"
#include "Content.h"
#include "Inventory.h"

InventoryCell::InventoryCell(Inventory* inv) : UIDragable(inv->screenParent),
    invParent(inv),
    uiItem(nullptr),
    selectedColor(sf::Color::Black)
{
	// Properties
	screenParent = inv->screenParent;
	dragAble = false;
	// ������������� ��������
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setTexture(&ContentManager::invCellTexture, true);
	setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void InventoryCell::update()
{
	if (uiItem != nullptr && !uiItem->isDragAllow())
	{
		// ������� Item ������
		uiItem->setPosition(getPosition());
	}
	UIDragable::update();
}

void InventoryCell::draw(sf::RenderTarget & target)
{
	if (invParent->getSelectedCell() == this)
		setFillColor(selectedColor);
	else
		setFillColor(sf::Color::White);

	UIDragable::draw(target);
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

const char *InventoryCell::getName() const {
    return "InventoryCell";
}