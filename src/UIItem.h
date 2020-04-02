#pragma once
#include "Item.h"
#include "UIDragable.h"

////////////////////////////////////////////////////////////
/// \brief Item class which is dragable
///
////////////////////////////////////////////////////////////
class UIItem : public UIDragable
{
public:
	UIItem(Item item);									   // Конструктор Item
	UIItem(UIScreen* screenParent);						   // Конструктор UI
	UIItem(const sf::Texture& texture, sf::IntRect rect);  // Конструктор Item

	UIItem(Item* item);									   // Конструктор Item

	virtual void draw(sf::RenderTarget& target) override;
	virtual void update() override;

	virtual void onDragBegin() override;
	virtual void onDrop() override;
	virtual void onCancelDrag() override;


public:
	Item item;
};