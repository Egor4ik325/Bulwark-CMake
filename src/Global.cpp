#include "Global.h"

//sf::Vector2f GetOffSet(sf::View view) 
//{
//	sf::Vector2f offSet;
//	sf::Vector2f ViewCenter = view.getCenter();
//	sf::Vector2f ViewSize = view.getSize();
//	offSet.x = ViewCenter.x - ViewSize.x / 2.f;
//	offSet.y = ViewCenter.y - ViewSize.y / 2.f;
//
//	return offSet;
//}

sf::Transform getViewTransformOffSet(const sf::RenderTarget &target)
{
	sf::Transform transformOffSet;
	transformOffSet.translate(target.mapPixelToCoords(sf::Vector2i(0, 0)));
	return transformOffSet;
}