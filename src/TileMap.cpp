#include "TileMap.h"

#include "tinyxml.h"
#include <iostream>
#include <map>
#include "Global.h"


using namespace sf;

bool TileMap::loadFromFile(std::string filename)
{
	TiXmlDocument levelFile(filename.c_str());

	// Загружаем XML-карту
	if (!levelFile.LoadFile())
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
		return false;
	}

	// Работаем с контейнером map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");

	// Пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// Пытаемся загрузить тайлсет
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;
		return false;
	}

	// Очищаем карту от света (109, 159, 185)
	// Вообще-то в тайлсете может быть фон любого цвета, но я не нашел решения, как 16-ричную строку
	// вроде "6d9fb9" преобразовать в цвет
	img.createMaskFromColor(sf::Color(109, 159, 185));
	// Грузим текстуру из изображения
	tilesetImage.loadFromImage(img);
	// Расплывчатость запрещена
	tilesetImage.setSmooth(false);

	// Получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// Вектор из прямоугольников изображений (TextureRect)
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

	// Работа со слоями
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		// Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		// Контейнер <data>
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		// Контейнер <tile> - описание тайлов каждого слоя
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
			// Записываем айди всех плиток  в вектор
			layer.tilesId.push_back(tileGID);

			int subRectToUse = tileGID - firstTileID;

			// Устанавливаем TextureRect каждого тайла
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
	// Рисуем все тайлы (объекты НЕ рисуем!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			target.draw(layers[layer].tiles[tile]);
}

int TileMap::getTileId(int x, int y) const
{
	// Преобразуем pixel в тайлы
	int TileX = x / TILE_SIZE;
	int TileY = y / TILE_SIZE;
	// Тайлы в пределах карты
	if (TileX > width - 1)
		return 0;
	if (TileY > height - 1)
		return 0;
	// Берем Id самого верхнего слоя
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
			layers[layer].tiles[tile].setScale(4, 4); // Из 16x16 делаем 64x64

		}
}

void TileMap::setTileType(int id, TileType type)
{
	typeArr[id] = type;
}