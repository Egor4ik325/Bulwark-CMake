#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ContentManager 
{
public:

	static const std::string CONTENT_DIR;
	
    static sf::Texture tileSet; // Плитки 16x16 пикселей
	static sf::Texture playerTexture;
	static sf::Texture effectTexture;
	static sf::Texture itemSet;
	static sf::Texture invCellTexture;
	static sf::Texture menuTexture;

	static sf::Font font;

	//// Загрузить контент STATIC //////
	static void loadContent();
};
