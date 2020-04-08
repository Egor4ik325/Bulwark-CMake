#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Content
{
public:
	static const std::string CONTENT_DIR;
	
    static sf::Texture tileSet; // ������ 16x16 ��������
	static sf::Texture playerTexture;
	static sf::Texture effectTexture;
	static sf::Texture itemSet;
	static sf::Texture invCellTexture;
	static sf::Texture menuTexture;

	static sf::Font font;

	//// ��������� ������� STATIC //////
	static void loadContent();
};