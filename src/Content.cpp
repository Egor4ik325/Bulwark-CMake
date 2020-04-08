#include "Content.h"
///////////////////   ????????????? ??????????   /////////////////

const std::string Content::CONTENT_DIR = "res/";
sf::Texture Content::tileSet;
sf::Texture Content::playerTexture;
sf::Texture Content::effectTexture;
sf::Texture Content::itemSet;
sf::Texture Content::invCellTexture;
sf::Texture Content::menuTexture;
sf::Font Content::font;

void Content::loadContent()
{
	tileSet.loadFromFile       (CONTENT_DIR + "TileSet.png");
	playerTexture.loadFromFile (CONTENT_DIR + "PlayerTexture.png");
	effectTexture.loadFromFile (CONTENT_DIR + "PlayerTexture.png");
	itemSet.loadFromFile       (CONTENT_DIR + "ItemSet.png");
	invCellTexture.loadFromFile(CONTENT_DIR + "InvCellSet.png");
	menuTexture.loadFromFile   (CONTENT_DIR + "menu.png", sf::IntRect(0,0, 1024, 400));

	// Texture.setSmoth(bool)
    font.loadFromFile          (CONTENT_DIR + "Font.ttf");
}