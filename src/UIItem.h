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
	explicit UIItem(Item item);									   // ����������� Item
	explicit UIItem(UIScreen* screenParent);						   // ����������� UI
	explicit UIItem(const sf::Texture& texture, sf::IntRect rect);  // ����������� Item
	explicit UIItem(Item* item);									   // ����������� Item

	void draw(sf::RenderTarget& target) override;
	void update() override;

	void onDragBegin() override;
	void onDrop() override;
	void onCancelDrag() override;

    const char *getName() const override;

public:
	Item item;
};