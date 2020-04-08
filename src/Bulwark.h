#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map/TileMap.h"
#include "UIs.h"
#include "LayerStack.h"

class ItemLayer;
///////////////////////////////////////
///  Just an application class
///  It will handle everything
///////////////////////////////////////
// TODO create Event
class Bulwark
{
public:
    // Window
    sf::RenderWindow window;
	bool gamePlay;

private:
    // Player
	Player player;
    // Game map
	TileMap map;
	// Current view
	sf::View view;
	// Elapsed time
	sf::Clock clock;
	float time;
	//std::list <Effect> Effects;  Manager
	LayerStack stack;

	// UI
	UILayer* menuLayer, *gameLayer;
	UIWindow* win;
	UIButton* start, *quit;
	// Item
	ItemLayer* itemLayer;

	// current window width and height
	unsigned int HEIGHT, WIDTH;

public:
	Bulwark();
	void onPullEvents();
	void onUpdate();
	void draw();
	
	void onPullEventsMenu();
	void onUpdateMenu();
	void drawMenu();

	//bool isGamePlay() const;
private:
	void createUI();
	void createItem();
	void drawText(const char *string, float data, sf::Vector2f position);
};

