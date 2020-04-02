#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "UIWindow.h"
#include "InventoryCell.h"

class Inventory : public UIWindow
{
protected:	
	std::vector <InventoryCell*> cells;
    unsigned int cellCount;
	
public:
	unsigned int selectedCell;

	Inventory(UIScreen* screenParent = nullptr);

	void update() override;
	void createCells();

	bool isDragAllow() const override;
	InventoryCell* getCell(unsigned int index);
	InventoryCell* getFirstEmptyCell();
	InventoryCell* getSelectedCell();

	~Inventory();
protected:
	void addCell();
};
