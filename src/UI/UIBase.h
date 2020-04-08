#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UILayer;

//enum UIType
//{
//    None = 0,
//    UIWindowType,
//    UIButtonType,
//    UIItemType,
//    InventoryType,
//    InventoryCellType
//};

////////////////////////////////////////////////////////////
/// \brief Abstract base class for UI includes {UIDrawable, UITransformable}
///
////////////////////////////////////////////////////////////
class UIBase : public sf::RectangleShape
{
protected:
    explicit UIBase(UILayer* screenParent); // protected constructor - class can not be created

	bool visible;

	UIBase* parent;
	//UIBase* child;
	// ���� ����� ��������� � ������������ ������
	std::vector<UIBase*> childs;

public:
	UILayer* layerParent; // Screen, on which it draws

public:
	virtual void onUpdate() = 0;
	virtual void onDraw(sf::RenderWindow &target);
    //void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setLayerParent(UILayer* screenParent);

	virtual const char* getName() const = 0;
	//virtual UIType getType() const = 0;

	virtual void setParent(UIBase* parent);
	virtual void addChild(UIBase* child);
	virtual void removeChild(UIBase* child);

	// Events
	virtual void onMouseOver() {};
	virtual void onMouseButtonPressed() {};
};