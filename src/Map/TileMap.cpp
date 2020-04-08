#include "TileMap.h"

#include "Map/TinyXML/tinyxml.h"
#include <iostream>
#include <map>
#include "Global.h"


using namespace sf;

bool TileMap::loadFromFile(std::string filename)
{
	TiXmlDocument levelFile(filename.c_str());

	// ��������� XML-�����
	if (!levelFile.LoadFile())
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
		return false;
	}

	// �������� � ����������� map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");

	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - ���� �� �������� � ���������� image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// �������� ��������� �������
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;
		return false;
	}

	// ������� ����� �� ����� (109, 159, 185)
	// ������-�� � �������� ����� ���� ��� ������ �����, �� � �� ����� �������, ��� 16-������ ������
	// ����� "6d9fb9" ������������� � ����
	img.createMaskFromColor(sf::Color(109, 159, 185));
	// ������ �������� �� �����������
	tilesetImage.loadFromImage(img);
	// �������������� ���������
	tilesetImage.setSmooth(false);

	// �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// ������ �� ��������������� ����������� (TextureRect)
	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	// ������ �� ������
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		TileLayer layer;

		// ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		// ��������� <data>
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		// ��������� <tile> - �������� ������ ������� ����
		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			// ���������� ���� ���� ������  � ������
			layer.tilesId.push_back(tileGID);

			int subRectToUse = tileGID - firstTileID;

			// ������������� TextureRect ������� �����
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	return true;
}

void TileMap::draw(sf::RenderTarget & target)
{
	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			target.draw(layers[layer].tiles[tile]);
}

int TileMap::getTileId(int x, int y) const
{
	// ����������� pixel � �����
	int TileX = x / TILE_SIZE;
	int TileY = y / TILE_SIZE;
	// ����� � �������� �����
	if (TileX > width - 1)
		return 0;
	if (TileY > height - 1)
		return 0;
	// ����� Id ������ �������� ����
	int layer = layers.size(); layer--;

	return layers[layer].tilesId[TileX + TileY * width] - 1;
}

int TileMap::getTileId(Vector2i TilePos) const
{
	return getTileId(TilePos.x, TilePos.y);
}

TileMap::TileType TileMap::getTileType(int x, int y) const
{
	return typeArr[getTileId(x, y)];
}

TileMap::TileType TileMap::getTileType(const Vector2i &TilePos) const
{
	return typeArr[getTileId(TilePos.x, TilePos.y)];
}

void TileMap::setTileSize(const int TileSize)
{
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			int xx = layers[layer].tiles[tile].getPosition().x;
			int yy = layers[layer].tiles[tile].getPosition().y;

			int NextPosX = layers[layer].tiles[tile].getPosition().x * (TileSize / tileWidth);
			int NextPosY = layers[layer].tiles[tile].getPosition().y * (TileSize / tileHeight);

			layers[layer].tiles[tile].setPosition(NextPosX, NextPosY);
			layers[layer].tiles[tile].setScale(4, 4); // �� 16x16 ������ 64x64

		}
}

void TileMap::setTileType(int id, TileType type)
{
	typeArr[id] = type;
}