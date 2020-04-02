#include "Global.h"

sf::RenderWindow window;
const int WIDTH = 1024;
const int HEIGHT = 640;
const int TILE_SIZE = 64;

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

sf::Vector2f GetViewOffSet() 
{
	sf::Vector2f offset;
	offset = window.mapPixelToCoords(sf::Vector2i(0, 0));
	return offset;
}

sf::Transform getViewTransformOffSet()
{
	sf::Transform transformOffSet;
	transformOffSet.translate(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	return transformOffSet;
}

sf::Vector2f getMouseLocalPos()
{
	return (sf::Vector2f)sf::Mouse::getPosition(window);
}

sf::Vector2f getMouseGlobalPos()
{
	sf::Vector2i mouseLocalPos = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mouseLocalPos);
}

bool isMouseLeft()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
