#pragma once
#include <SFML/Graphics.hpp>
#include "UIBase.h"

class UIScreen;

////////////////////////////////////////////////////////////
/// \brief Base class for UI with drag and over
///
////////////////////////////////////////////////////////////
class UIDragable : public UIBase
{
protected:
	UIDragable(UIScreen* screenParent);

	bool dragAble;
	sf::Vector2f dragOffset;
public:

	// Унаследовано через UIBase
	virtual void update() override;

	virtual void onDragBegin();	      
	virtual void onDrop();		      
	virtual void onCancelDrag();      
	virtual bool isDragAllow() const; 
	inline sf::Vector2f getDragOffSet() { return dragOffset; };
};

//class UIDragable
//{
//protected:
//	sf::RectangleShape rectShape;
//	bool visible;
//
//	bool dragAble;
//	sf::Vector2f dragOffset;
//public:
//	// Без родителя UI НЕ РАБОТАЕТ
//	UIScreen* screenParent;
//public:
//
//	UIDragable(UIScreen* screenParent = nullptr);
//
//	virtual void draw(sf::RenderTarget & target);
//	virtual void update();
//
//	virtual void updateOver();		  //
//	virtual void onDragBegin();		  //
//	virtual void onDrop();			  //   Dragable fuctions
//	virtual void onCancelDrag();	  //
//	virtual bool isDragAllow() const; //
//
//	inline void setScreenParent(UIScreen* parent) { screenParent = parent; };
//	inline void setScreenParent(UIScreen& parent) { screenParent = &parent; };
//	void setPosition(float x, float y);
//	void setPosition(sf::Vector2f position);
//	void setSize(float x, float y);
//	void setSize(sf::Vector2f size);
//
//	inline sf::Vector2f getDragOffSet() { return dragOffset; };
//	inline sf::Vector2f getPosition() { return rectShape.getPosition(); };
//	inline const sf::RectangleShape& getRectShape() const { return rectShape; };
//};