#pragma once
#include <SFML/Graphics.hpp>
#include "UIBase.h"

class UILayer;

////////////////////////////////////////////////////////////
/// \brief Base class for UI with drag and over
///
////////////////////////////////////////////////////////////
class UIDragable : public UIBase
{
protected:
	UIDragable(UILayer* screenParent);

	bool dragAble;
	sf::Vector2f dragOffset;
public:

	// ������������ ����� UIBase
	void onUpdate() override;

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
//	// ��� �������� UI �� ��������
//	UILayer* layerParent;
//public:
//
//	UIDragable(UILayer* layerParent = nullptr);
//
//	virtual void onDraw(sf::RenderTarget & target);
//	virtual void onUpdate();
//
//	virtual void updateOver();		  //
//	virtual void onDragBegin();		  //
//	virtual void onDrop();			  //   Dragable fuctions
//	virtual void onCancelDrag();	  //
//	virtual bool isDragAllow() const; //
//
//	inline void setLayerParent(UILayer* parent) { layerParent = parent; };
//	inline void setLayerParent(UILayer& parent) { layerParent = &parent; };
//	void setPosition(float x, float y);
//	void setPosition(sf::Vector2f position);
//	void setSize(float x, float y);
//	void setSize(sf::Vector2f size);
//
//	inline sf::Vector2f getDragOffSet() { return dragOffset; };
//	inline sf::Vector2f getPosition() { return rectShape.getPosition(); };
//	inline const sf::RectangleShape& getRectShape() const { return rectShape; };
//};