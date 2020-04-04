#include "UIItem.h"
#include "InventoryCell.h"
#include "UIManager.h"

UIItem::UIItem(UIScreen* screenParent) : UIDragable(screenParent),
    item(Item())
{
	dragAble = true;
}

UIItem::UIItem(const sf::Texture& texture, sf::IntRect rect) : UIDragable(nullptr),
	item(Item(texture, rect))
{
	dragAble = true;
}

UIItem::UIItem(Item * item) : UIItem(*item)
{
	dragAble = true;
}

UIItem::UIItem(Item item) : UIDragable(nullptr),
item(item)
{
	dragAble = true;
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

void UIItem::onDragBegin() {
    //if (parent->getName() == "InventoryCell")
    //{
    //	InventoryCell* cellParent = (InventoryCell*)parent;
    //	cellParent->removeItem();
    //}
    if (parent != nullptr) {
        parent->removeChild(this);
    }
}

void UIItem::onDrop()
{
	UIBase* over = screenParent->over;
	if(strcmp(over->getName(), "InventoryCell") != 0) // TODO remove in future
	{
	    parent = over;
        over->addChild(this);
    } else{
	    onCancelDrag();
	}
}

void UIItem::onCancelDrag()
{
	//if (parent->getName() == "InventoryCell")
	//{
	//	InventoryCell* cellParent = (InventoryCell*)parent;
    //
	//	cellParent->setItem(this);
	//}
	if(parent != nullptr){
	    parent->addChild(this);
	}
}

const char *UIItem::getName() const {
    return "UIItem";
}