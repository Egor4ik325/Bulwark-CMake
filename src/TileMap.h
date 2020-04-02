#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Layer
{
public:
	int opacity;                      // Непрозрачность
	std::vector<int> tilesId;	      // Айди плиток 
	std::vector<sf::Sprite> tiles;    // Спрайты плиток
};

class TileMap
{
public:
	// Типы плиток
	enum  TileType { GROUND, WALL, WATER, CHEST };       
													     
	bool loadFromFile(std::string filename);          
	void draw(sf::RenderTarget& target);	             
											             
	void setTileSize(const int TileSize);	            
	void setTileType(int id, TileType type);	             
											             
	int getTileId(int x, int y) const;			             
	int getTileId(sf::Vector2i TilePos) const;	             
	TileType getTileType(int x, int y) const;		        
	TileType getTileType(const sf::Vector2i &TilePos) const;   

private:

	int width, height;                     // Ширина и высота карты (в тайлах)
	int tileWidth, tileHeight;             // размер тайла в пикселях
	int firstTileID;				       
	sf::FloatRect drawingBounds;           // Часть карты которую мы будем рисовать и которая соответствует view
	sf::Texture tilesetImage;              // TileSet	
	std::vector<Layer> layers;             // Слои
	TileType typeArr[20] = { GROUND };     // Типы для ID;
};


