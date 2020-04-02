#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class UIScreen;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for UI includes {UIDrawable, UITransformable}
///
////////////////////////////////////////////////////////////
class UIBase : public sf::RectangleShape
{
protected:
	//UIBase() = default; // Default protected contructor means - abstract class - can not be created
	
	UIBase(UIScreen* screenParent); 

	std::string name;
	bool visible;

	UIBase* parent;
	UIBase* child;
	//// Дети будет храниться в динамической памяти
	//std::vector<UIBase*> childs;

public:
	UIScreen* screenParent; // Родитель

public:

	virtual void update();
	//void updateChildren();

	virtual void draw(sf::RenderTarget& target);
	//void drawChildren(sf::RenderTarget& target);

	void setScreenParent(UIScreen* screenParent);
	void setScreenParent(UIScreen& screenParent);
	const std::string& getName() const;

	void setParent(UIBase* parent);
	void setChild(UIBase* child);

	UIBase* getChild();
};