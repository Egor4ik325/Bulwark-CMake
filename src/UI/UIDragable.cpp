#include "UIDragable.h"

#include "Application.h"
#include <iostream>
#include "Global.h"
#include "LayerStack.h"
#include "UILayer.h"

UIDragable::UIDragable(UILayer* screenParent) : UIBase(screenParent),
    dragAble(true)
{
	// ����������� ��������� ������
	setFillColor(sf::Color::White);
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setPosition(0.f, 0.f);
}

// ��������� ���������� ������� ��� ��������
void UIDragable::onUpdate()
{
	//if (layerParent == nullptr) return;
//
	//if(dragAble) {
    //    if (isDragAllow())
    //        if (layerParent->drag == nullptr){
    //            layerParent->drag = this; // drag this
    //            dragOffset = GETMOUSELOCAL(Application::get().getWindow()) - getPosition();
//
    //            onDragBegin();
    //            std::cout << "Begin drag!! " << getName() << std::endl;
    //        }
    //}
//
    //// ���� ������ ��������� � �����������
    //// Just over check
    //if (getGlobalBounds().contains(GETMOUSELOCAL(Application::get().getWindow())))
    //{
    //    std::cout << "Intersects with " << getName() << std::endl;
    //    // ���� �� �����������, �� ��������� ��� �����������
    //    if (layerParent->drag != this)
    //        layerParent->over = this;
    //}
	//if(isDragAllow())
	//{
	//
//
	//	if (dragAble && isDragAllow())
	//	{
	//		// ���� ��� �� �����������
	//		//���� ��� ����������� 1 ��� ������� ��������������
	//		if (layerParent->drag == nullptr)
	//		{
	//			// ���� �������� �����������
	//			//if (IsMouseLeft())
//
	//			layerParent->drag = this;
	//			dragOffset = GETMOUSELOCAL(;
//
	//			onDragBegin();
//
//
	//
	//		}
	//	}
//
	//
	//}
}

void UIDragable::onDragBegin()
{
}

void UIDragable::onDrop()
{
}

void UIDragable::onCancelDrag()
{
}

//bool UIDragable::isDragAllow() const
//{
//	if (layerParent == nullptr) return false;
//
//	return (getGlobalBounds().contains(GETMOUSELOCAL(Application::get().getWindow())) || layerParent->drag == this) && ISMOUSELEFT;
//}

void UIDragable::onEvent(sf::Event &event)
{
    if(dragAble)
        if(isDragAllow(event))
            if (layerParent->drag == nullptr){
                layerParent->drag = this; // drag this!
                dragOffset = sf::Vector2f(event.mouseButton.x, event.mouseButton.y) - getPosition();

                onDragBegin();
                std::cout << "Begin Drag!! " << getName() << std::endl;
            }
}

bool UIDragable::isDragAllow(const sf::Event &event) const
{
    if(layerParent == nullptr) return false;

    if(event.type == sf::Event::EventType::MouseButtonPressed)
        if(event.mouseButton.button == sf::Mouse::Button::Left)
            // if mouse was clicked over the ui OR if mouse is dragging it already => then allow start or continue drag
            if(getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) || layerParent->drag == this)
                return true;

    return false;
}

//UIDragable::UIDragable(UILayer* layerParent): layerParent(layerParent)
//{
//	visible = true;
//	dragAble = false;
//	// ����������� ��������� ������
//	rectShape.setFillColor(sf::Color::White);
//	rectShape.setSize(sf::Vector2f(TileSize, TileSize));
//	rectShape.setPosition(0.f, 0.f);
//	dragOffset = sf::Vector2f(0.f, 0.f);
//}
//
//void UIDragable::onDraw(sf::RenderTarget &target)
//{
//	if (visible)
//	{	
//		target.onDraw(rectShape, getViewTransformOffSet());
//	}
//}
//
//void UIDragable::onUpdate()
//{
//	
//}
//
//// ��������� ���������� ������� ��� ��������
//void UIDragable::updateOver()
//{
//	if (layerParent == nullptr) return;
//
//	// ���� ������ ��������� � �����������
//	if (rectShape.getGlobalBounds().contains(getMouseLocalPos()))
//	{
//		
//		std::cout << "Intersect!! \n" ;
//		
//		if (dragAble && isDragAllow())
//		{
//			// ���� ��� �� ����������� 
//			//���� ��� ����������� 1 ��� ������� ��������������
//			if (layerParent->drag == nullptr)
//			{				
//				// ���� �������� �����������
//				//if (IsMouseLeft())
//
//				layerParent->drag = this;
//				dragOffset = getMouseLocalPos() - rectShape.getPosition();
//				
//				onDragBegin();
//				
//
//				std::cout << "START MOVING!! \n";
//			}
//		}
//
//		// ���� �� �����������, �� ��������� ��� �����������
//		if (layerParent->drag != this)
//			layerParent->over = this;
//	}
//}
//
//void UIDragable::onDragBegin()
//{
//
//}
//
//void UIDragable::onDrop()
//{
//
//}
//
//void UIDragable::onCancelDrag()
//{
//
//}
//
//bool UIDragable::isDragAllow() const
//{
//	if (layerParent == nullptr) return false;
//
//	return (rectShape.getGlobalBounds().contains(getMouseLocalPos()) || layerParent->drag == this) && isMouseLeft();
//}
//
//////////////////////////////////////////////////////////////////////////////////////
//void UIDragable::setPosition(sf::Vector2f position)
//{
//	rectShape.setPosition(position);
//}
//
//void UIDragable::setPosition(float x, float y)
//{
//	rectShape.setPosition(sf::Vector2f(x, y));
//}
//
//void UIDragable::setSize(sf::Vector2f size)
//{
//	rectShape.setSize(size);
//}
//
//void UIDragable::setSize(float x, float y)
//{
//	rectShape.setSize(sf::Vector2f(x, y));
//}