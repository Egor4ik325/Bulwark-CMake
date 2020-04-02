#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TileMap.h"
#include "UserInterfaces.h"

class Bulwark
{
private:
	Player player;
	TileMap map;
	sf::View view;
	sf::Clock clock; float time{};
	//std::list <Effect> Effects;  Manager

	// UI
	UIScreen menuScreen, gameScreen;
	UIWindow win;
	UIButton start, quit;
	
	bool gamePlay;
public:

	Bulwark();
	void pollEnvent();
	void update();
	void draw();
	
	void pollEnventMenu();
	void updateMenu();
	void drawMenu();

	bool isGamePlay() const;
private:
	void addUI();
	static void drawText(const char* text, float data, sf::Vector2i position, const char* count = "%.4f");
};

