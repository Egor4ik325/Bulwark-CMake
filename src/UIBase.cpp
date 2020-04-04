#include "UIBase.h"
#include "Global.h"

UIBase::UIBase(UIScreen * screenParent) :
    visible(true),
    parent(nullptr),
	screenParent(screenParent)
{
}

void UIBase::draw(sf::RenderTarget & target)
{
	if (visible)
	{
		target.draw(*this, getViewTransformOffSet());
	}
}

void UIBase::setScreenParent(UIScreen * screenParent)
{
	this->screenParent = screenParent;
}

void UIBase::setParent(UIBase * parent)
{
	this->parent = parent;
}

void UIBase::addChild(UIBase *child)
{
    // set this as parent
    child->setParent(this);
    childs.push_back(child);
}

void UIBase::removeChild(UIBase *child)
{
    for (int i = 0; i < childs.size(); ++i)
    {
        if(childs[i] == child)
        {
            // remove from vector
            auto iter = childs.begin();
            std::advance(iter, i);
            childs.erase(iter);
        }
    }
}
//void UIBase::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//
//    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
//
//    // apply the texture
//    states.texture = &m_texture;
//
//    // you may also override states.shader or states.blendMode if you want
//
//    // draw the vertex array
//    target.draw(m_vertices, states);
//}

//UIBase::~UIBase()
//{
//	for (UIBase* c : childs)
//	{
//		delete c;
//	}
//	childs.clear();
//}
