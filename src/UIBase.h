#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UIScreen;

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
    explicit UIBase(UIScreen* screenParent); // protected constructor - class can not be created



	bool visible;

	UIBase* parent;
	//UIBase* child;
	// ���� ����� ��������� � ������������ ������
	std::vector<UIBase*> childs;

public:
	UIScreen* screenParent; // Screen, on which it draws

public:
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target);
    //void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setScreenParent(UIScreen* screenParent);

	virtual const char* getName() const = 0;
	//virtual UIType getType() const = 0;

	virtual void setParent(UIBase* parent);
	virtual void addChild(UIBase* child);
	virtual void removeChild(UIBase* adress);

	// Events
	virtual void onMouseOver() {};
	virtual void onMouseButtonPressed() {};

};