#include "UIItem.h"
#include "InventoryCell.h"
#include "UIManager.h"

UIItem::UIItem(UIScreen* screenParent) : UIDragable(screenParent)
{
	dragAble = true;
	// Name
	name = "UIItem";
}

UIItem::UIItem(const sf::Texture& texture, sf::IntRect rect) : UIDragable(nullptr),
	item(Item(texture, rect))
{
	dragAble = true;
	// Name
	name = "UIItem";
}

UIItem::UIItem(Item * item) : UIItem(*item)
{
	dragAble = true;
}

UIItem::UIItem(Item item) : UIDragable(nullptr),
item(item)
{
	dragAble = true;
	// Name
	name = "UIItem";
}

void UIItem::draw(sf::RenderTarget & target)
{
	UIDragable::draw(target);

	item.draw(target);
}

void UIItem::update()
{
	UIDragable::update();
	
	item.setPosition(getPosition());
}

void UIItem::onDragBegin()
{
	if (parent->getName() == "InventoryCell")
	{
		InventoryCell* cellParent = (InventoryCell*)parent;

		cellParent->removeItem();
	}
}

void UIItem::onDrop()
{
	UIBase* over = screenParent->over;

	if (over->getName() == "InventoryCell")
	{
		InventoryCell* cell = (InventoryCell*)over;

		parent = cell;

		cell->setItem(this);
	}

}

void UIItem::onCancelDrag()
{
	if (parent->getName() == "InventoryCell")
	{
		InventoryCell* cellParent = (InventoryCell*)parent;

		cellParent->setItem(this);
	}
}


