#pragma once
#include <SFML/Graphics.hpp>
#include "Layer.h"

#include <string>
#include <vector>

class LayerStack;

class MapLayer : public Layer
{
public:
	// ���� ������
	enum  TileType { GROUND, WALL, WATER, CHEST };

	explicit MapLayer(LayerStack& stack);

	bool loadFromFile(const std::string& filename);

    void onUpdate() override;
    void onDraw(sf::RenderWindow &win) override;

	void setTileSize(int tileSize);
	void setTileType(int id, TileType type);
											             
	int getTileId(int x, int y) const;
    TileType getTileType(int x, int y) const;
    std::string getName() const override;

private:
    struct TileLayer
    {
        std::vector<sf::Sprite> tiles;     // ������� ������
        std::vector<int> tilesId;	       // ���� ������
        int opacity;
    };
    std::vector<TileLayer> layers;         // Layers

	int width, height;                     // Size of all map
	int tileWidth, tileHeight;             // Size of tile
	int firstTileID;
	sf::FloatRect drawingBounds;           // A part (rect) of map that will be only rendered
	sf::Texture tilesetImage;              // TileSetImage

	TileType typeArr[20]{ GROUND };        // TileType for every id, init by default with GROUND
};