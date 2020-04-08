#include "UIDragable.h"
#include <iostream>
#include "Global.h"
#include "LayerStack.h"
#include "UILayer.h"

UIDragable::UIDragable(UILayer* screenParent) : UIBase(screenParent)
{
	visible = true;
	dragAble = false;
	// ����������� ��������� ������
	setFillColor(sf::Color::White);
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setPosition(0.f, 0.f);
	dragOffset = sf::Vector2f(0.f, 0.f);
}

// ��������� ���������� ������� ��� ��������
void UIDragable::onUpdate()
{
	if (layerParent == nullptr) return;

	// ���� ������ ��������� � �����������
	if (getGlobalBounds().contains(getMouseLocalPos(layerParent->window)))
	{
		std::cout << "Intersects with " << getName() << std::endl;

		if (dragAble && isDragAllow())
		{
			// ���� ��� �� ����������� 
			//���� ��� ����������� 1 ��� ������� ��������������
			if (layerParent->drag == nullptr)
			{
				// ���� �������� �����������
				//if (IsMouseLeft())

				layerParent->drag = this;
				dragOffset = getMouseLocalPos(layerParent->window) - getPosition();

				onDragBegin();


				std::cout << "START MOVING!! " << this->getName() << std::endl;
			}
		}

		// ���� �� �����������, �� ��������� ��� �����������
		if (layerParent->drag != this)
            layerParent->over = this;
	}
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

bool UIDragable::isDragAllow() const
{
	if (layerParent == nullptr) return false;

	return (getGlobalBounds().contains(getMouseLocalPos(layerParent->window)) || layerParent->drag == this) && isMouseLeft();
}

//UIDragable::UIDragable(UILayer* layerParent): layerParent(layerParent)
//{
//	visible = true;
//	dragAble = false;
//	// ����������� ��������� ������
//	rectShape.setFillColor(sf::Color::White);
//	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
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