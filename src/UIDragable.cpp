#include "UIDragable.h"
#include <iostream>
#include "Global.h"
#include "UIManager.h"
#include "UIScreen.h"

UIDragable::UIDragable(UIScreen* screenParent) : UIBase(screenParent)
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
void UIDragable::update()
{
	if (screenParent == nullptr) return;

	// ���� ������ ��������� � �����������
	if (getGlobalBounds().contains(getMouseLocalPos()))
	{

		std::cout << "Intersects with " << getName() << std::endl;

		if (dragAble && isDragAllow())
		{
			// ���� ��� �� ����������� 
			//���� ��� ����������� 1 ��� ������� ��������������
			if (screenParent->drag == nullptr)
			{
				// ���� �������� �����������
				//if (IsMouseLeft())

				screenParent->drag = this;
				dragOffset = getMouseLocalPos() - getPosition();

				onDragBegin();


				std::cout << "START MOVING!! " << this->getName() << std::endl;
			}
		}

		// ���� �� �����������, �� ��������� ��� �����������
		if (screenParent->drag != this)
			screenParent->over = this;
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
	if (screenParent == nullptr) return false;

	return (getGlobalBounds().contains(getMouseLocalPos()) || screenParent->drag == this) && isMouseLeft();
}

//UIDragable::UIDragable(UIScreen* screenParent): screenParent(screenParent)
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
//void UIDragable::draw(sf::RenderTarget &target)
//{
//	if (visible)
//	{	
//		target.draw(rectShape, getViewTransformOffSet());
//	}
//}
//
//void UIDragable::update()
//{
//	
//}
//
//// ��������� ���������� ������� ��� ��������
//void UIDragable::updateOver()
//{
//	if (screenParent == nullptr) return;
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
//			if (screenParent->drag == nullptr)
//			{				
//				// ���� �������� �����������
//				//if (IsMouseLeft())
//
//				screenParent->drag = this;
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
//		if (screenParent->drag != this)
//			screenParent->over = this;
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
//	if (screenParent == nullptr) return false;
//
//	return (rectShape.getGlobalBounds().contains(getMouseLocalPos()) || screenParent->drag == this) && isMouseLeft();
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