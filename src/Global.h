#pragma once
#include "SFML/Graphics.hpp"


#define GETMOUSELOCAL(window) (sf::Vector2f)sf::Mouse::getPosition(window)
#define ISMOUSELEFT sf::Mouse::isButtonPressed(sf::Mouse::Left)


extern const int TILE_SIZE;

sf::Transform getViewTransformOffSet(const sf::RenderTarget &target);
inline sf::Vector2f getViewOffSet(sf::RenderTarget &target)     { return target.mapPixelToCoords(sf::Vector2i(0, 0)); }

// Return mouse position by the current window
//inline sf::Vector2f getMouseLocalPos(const sf::RenderWindow &window) { return (sf::Vector2f)sf::Mouse::getPosition(window); }
// Returns absolute mouse position by the Desktop
///inline sf::Vector2f getMouseLocalPos() { return (sf::Vector2f)sf::Mouse::getPosition();}

//inline sf::Vector2f getMouseGlobalPos(sf::RenderWindow& window) { return window.mapPixelToCoords(sf::Mouse::getPosition(window)); }
//inline bool isMouseLeft() { return sf::Mouse::isButtonPressed(sf::Mouse::Left); }