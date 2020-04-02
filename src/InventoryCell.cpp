#include "InventoryCell.h"
#include "UIItem.h"
#include "Global.h"
#include "Content.h"
#include "Inventory.h"

InventoryCell::InventoryCell(Inventory* inv) : UIDragable(inv->screenParent)
{
	// Name
	name = "InventoryCell";
	// Запоминаем родителя
	this->invParent = inv;
	screenParent = invParent->screenParent;
	// Хранимый предмет
	itemContain = nullptr;
	dragAble = false;
	selectedColor = sf::Color::Black;
	// Устанавливаем текстуру
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setTexture(&ContentManager::invCellTexture, true);
	setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void InventoryCell::update()
{
	if (itemContain != nullptr && !itemContain->isDragAllow())
	{
		// Двигаем Item внутри
		itemContain->setPosition(getPosition());
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

void InventoryCell::setItem(UIItem * item)
{
	itemContain = item;
	itemContain->setParent(this);
	itemContain->item.onGround = false;
	itemContain->setPosition(getPosition());
}

void InventoryCell::removeItem()
{
	itemContain = nullptr;
}

bool InventoryCell::isEmpty()
{
	return itemContain == nullptr;
}

UIItem * InventoryCell::getItem()
{
	return itemContain;
}
