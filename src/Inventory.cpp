#include "Inventory.h"

#include "Global.h"
#include "LayerStack.h"
#include "UI/UILayer.h"
#include "Content.h"
#include "Item/Item.h"
#include "InventoryCell.h"

Inventory::Inventory(UILayer* layerParent) : UIWindow(layerParent),
    cellCount(0)
{
	dragAble = true;
	titleVisible = false;
	bodyColor = sf::Color(256, 256, 256, 100);
	selectedCell = 0;

	createCells();
}

void Inventory::createCells()
{
	if (layerParent == nullptr) return;

	cellCount = 5;
	setSize(sf::Vector2f(cellCount * 64 + 64, 64));
	for (int i = 0; i < cellCount; i++)
        addCell();
}

void Inventory::addCell()
{
	auto* cell = new InventoryCell(this);
	cell->setPosition(cells.size() * cell->getSize().x, 0);
	layerParent->pushControl(cell);

	cells.push_back(cell);
}

//bool Inventory::isDragAllow() const
//{
//	bool cellDrag = false;
//	for (auto c : cells)
//	{
//		if (c->isDragAllow())
//			cellDrag = true;
//	}
//
//	if (cellDrag && layerParent->drag != this)
//		return false;
//
//	return UIDragable::isDragAllow();
//}

void Inventory::onEvent(sf::Event &event)
{
    UIWindow::onEvent(event);

    for (int i = 0; i < cellCount; i++)
    {
    	if (!cells[i]->isDragAllow(event))
    	{
    		cells[i]->setPosition(getPosition() + sf::Vector2f(i * TILE_SIZE, 0));
    	}
    }
}

bool Inventory::isDragAllow(const sf::Event &event) const
{
    bool cellDrag = false;
	for (auto c : cells)
	{
		if (c->isDragAllow(event))
			cellDrag = true;
	}

	if (cellDrag && layerParent->drag != this)
	    return false;

    return UIWindow::isDragAllow(event);
}

void Inventory::onUpdate()
{
	if (layerParent == nullptr) return;
    UIWindow::onUpdate();

	//for (int i = 0; i < cellCount; i++)
	//{
	//	if (!cells[i]->isDragAllow())
	//	{
	//		cells[i]->setPosition(getPosition() + sf::Vector2f(i * TILE_SIZE, 0));
	//	}
	//}
}

InventoryCell * Inventory::getFirstEmptyCell() const
{
	for (InventoryCell* cell : cells)
	{
		if (cell->isEmpty())
			return cell;
	}
	
	return nullptr;
}

InventoryCell* Inventory::getCell(unsigned int index) const
{
	if (index > cells.size()) return nullptr;

	return cells[index];
}