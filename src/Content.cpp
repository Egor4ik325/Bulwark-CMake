#include "Content.h"
///////////////////   Инициализация переменных   /////////////////

const std::string ContentManager::CONTENT_DIR = "Content/";
sf::Texture ContentManager::tileSet;
sf::Texture ContentManager::playerTexture;
sf::Texture ContentManager::effectTexture;
sf::Texture ContentManager::itemSet;
sf::Texture ContentManager::invCellTexture;
sf::Texture ContentManager::menuTexture;
sf::Font ContentManager::font;

void ContentManager::loadContent()
{
	tileSet.loadFromFile(CONTENT_DIR + "TileSet.png");
	playerTexture.loadFromFile(CONTENT_DIR + "PlayerTexture.png");
	effectTexture.loadFromFile(CONTENT_DIR + "PlayerTexture.png");
	itemSet.loadFromFile(CONTENT_DIR + "ItemSet.png");
	invCellTexture.loadFromFile(CONTENT_DIR + "InvCellSet.png");
	menuTexture.loadFromFile(CONTENT_DIR + "menu.png", sf::IntRect(0,0, 1024, 400));

	// Texture.setSmoth(bool)
    font.loadFromFile(CONTENT_DIR + "Font.ttf");
}