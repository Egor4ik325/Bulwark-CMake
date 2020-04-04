#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.h"

class TileMap;

class Player
{
private:
	sf::Vector2f position;      // ����������	
	sf::Vector2f velocity;      // ��������	
	const TileMap *map{};         // ����� - ������ ��� ������ ������, ��� �������� � ���������
	const sf::Texture *texture{}; // �������� ������ - ������ ��� ������ ������

	// flags
	bool going{};
	bool picking{};
	bool onTile{};

	// properties
	float speed;
	int health;

	enum DIR { UP = 0, DOWN, RIGHT, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NONE };
	DIR playerDir; DIR targDir;

	// moving
	sf::Vector2i targ;  // ���������� ���� ����
	sf::Vector2i targT; 
	bool goingDirFlag; 
	int goneX{}, goneY{};

	// animation
	float frame;
	sf::Sprite sprite;
	sf::Sprite effect;

public:
	Inventory* inventory;      // ���������, ��� ������� ������ - ���������
public:
	Player();
	// �������� �� ������, �� ���������� ��������� ������
	Player(const sf::Texture& texture); // ������� ������������ - ��� ��� ��� ������ ���������� nullptr ��� ����� ������ ������ ����� -- ����� �������� ������ ����� ������ ���������� �� ������� ����� ������� ������

	void update(float time);
	void draw(sf::RenderTarget & target);
	
	void pickUp();
	void dropUp(InventoryCell* cell);
	void stop();
	
	void moveBy(int TileX, int TileY);

	void goTo(int x, int y);
	void setTexture(const sf::Texture &playerTex); 
	void setTileMap(const TileMap &map);
	void setPicking(bool picking);

	bool isPicking() const;
	sf::Vector2f getPosition() const;
	sf::Vector2i getRoundPos() const;
	sf::Vector2i getTilePos() const;	
	sf::Vector2i getMiddleTilePos() const;
	sf::Vector2f getMiddlePos() const;

private:
	void updateMovement(float time);
	void targTileDiraction();
	void collision();
	void animation(float time);
};