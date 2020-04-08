#pragma once
#include "Item/Item.h"
#include "UIDragable.h"

////////////////////////////////////////////////////////////
/// \brief Item class which is dragable
///
////////////////////////////////////////////////////////////
class UIItem : public UIDragable
{
public:
	explicit UIItem(Item item);									   // ����������� Item
	explicit UIItem(UILayer* screenParent);						   // ����������� UI
	explicit UIItem(const sf::Texture& texture, sf::IntRect rect);  // ����������� Item
	explicit UIItem(Item* item);									   // ����������� Item

	void onDraw(sf::RenderWindow &target) override;
	void onUpdate() override;

	void onDragBegin() override;
	void onDrop() override;
	void onCancelDrag() override;

    inline const char *getName() const override { return "UIDragable"; }

public:
	Item item;
};