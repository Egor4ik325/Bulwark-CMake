#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TileLayer
{
public:
	int opacity;                      // ��������������
	std::vector<int> tilesId;	      // ���� ������ 
	std::vector<sf::Sprite> tiles;    // ������� ������
};

class TileMap
{
public:
	// ���� ������
	enum  TileType { GROUND, WALL, WATER, CHEST };       
													     
	bool loadFromFile(std::string filename);          
	void draw(sf::RenderTarget& target);	             
											             
	void setTileSize(int TileSize);
	void setTileType(int id, TileType type);	             
											             
	int getTileId(int x, int y) const;			             
	int getTileId(sf::Vector2i TilePos) const;	             
	TileType getTileType(int x, int y) const;		        
	TileType getTileType(const sf::Vector2i &TilePos) const;   

private:
	int width, height;                     // ������ � ������ ����� (� ������)
	int tileWidth, tileHeight;             // ������ ����� � ��������
	int firstTileID;				       
	sf::FloatRect drawingBounds;           // ����� ����� ������� �� ����� �������� � ������� ������������� view
	sf::Texture tilesetImage;              // TileSet	
	std::vector<TileLayer> layers;             // ����
	TileType typeArr[20] = { GROUND };     // ���� ��� ID;
};


