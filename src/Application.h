#pragma once
#include <SFML/Graphics.hpp>
#include "UIs.h"
#include "Player.h"
#include "LayerStack.h"
#include "Map/MapLayer.h"

class ItemLayer;
///////////////////////////////////////
///  Just an application class
///  It will handle everything
///////////////////////////////////////

class Application
{
public:
    // Window
    sf::RenderWindow window;
	bool gamePlay;

private:
    // App static instance
    static Application* application_instance;
    // Player
	Player player;
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
    // Game map layer
    MapLayer* map;

	// current window width and height
	int TileSize;

	sf::Vector2i mousePos;
	bool mouseLeave=false;

public:
	Application();

	void onPullWindowEvents();
	void onUpdate();
	void onRender();
	
	void onPullEventsMenu();
	void onUpdateMenu();
	void onRenderMenu();

	void onWindowClosed();                       // WindowClosedEvent
	void onWindowResized(sf::Event& event);      // WindowResizedEvent
	void onMouseMoved(sf::Event& event);         // MouseMovedEvent
	void onMouseButtonPressed(sf::Event& event); // MouseButtonPressedEvent
	void onMouseWheelScrolled(sf::Event& event); // MouseWheelScrolledEvent
	void onKeyPressed(sf::Event& event);         // KeyPressedEvent

	static inline Application& get()    { return *application_instance;}
	inline sf::RenderWindow& getWindow(){ return window; }
	inline int getTileSize()            { return TileSize; }
	inline sf::Vector2f getMousePos()   { return sf::Vector2f(mousePos); }
	inline sf::Vector2f getViewOffSet() { return window.mapPixelToCoords(sf::Vector2i(0, 0)); }
private:
	void createUI();
	void createItem();
	void onRenderText(const char *string, float num, sf::Vector2f position);
};

//#define GETMOUSELOCAL(window) (sf::Vector2f)sf::Mouse::getPosition(window)
//#define ISMOUSELEFT sf::Mouse::isButtonPressed(sf::Mouse::Left)
//#define TILE_SIZE Application::get().getTileSize()