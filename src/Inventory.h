#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "UI/UIWindow.h"
#include "InventoryCell.h"

class Inventory : public UIWindow
{
protected:
	std::vector <InventoryCell*> cells;
    unsigned int cellCount;
	
public:
	unsigned int selectedCell;

	explicit Inventory(UILayer* screenParent = nullptr);

	void onUpdate() override;
	void createCells();

	bool isDragAllow() const override;
	InventoryCell* getCell(unsigned int index) const;
	InventoryCell* getFirstEmptyCell() const;

	InventoryCell* getSelectedCell() const { return getCell(selectedCell); }
	const char *getName() const override { return "Inventory"; }

protected:
	void addCell();
};
