#include "Application.h"
#include "Content.h"
#include "Global.h"
#include "DebugGraphics.h"
#include "Item/ItemLayer.h"
#include "UI/UIItem.h"
#include <cstdio>
#include <iostream>

Application* Application::application_instance = nullptr;

Application::Application() :
        time(0.f),
        menuLayer(nullptr), gameLayer(nullptr), win(nullptr), start(nullptr), quit(nullptr),
        itemLayer(nullptr),
         TileSize(64),// Width(1024), Height(640),
        stack(window)
{
    application_instance = this;
	// Menu
	gamePlay = false;
    // Window settings
    window.create(sf::VideoMode(1024, 640), "Bulwark", sf::Style::Default);
    window.setPosition(sf::Vector2i(256, 100));
    window.setVerticalSyncEnabled(true);  // VSYNC
#if BW_DEBUG
    window.setFramerateLimit(10);    // Only for debugging
#endif
    // Cursor
    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(false);
    sf::Cursor cursor; cursor.loadFromSystem(sf::Cursor::Arrow);
    window.setMouseCursor(cursor);
    //system("help");

    // MapLayer create
    map = new MapLayer(stack);
    stack.pushLayer(map);
	map->loadFromFile("res/Map.tmx");   // load a map 30x30
	map->setTileSize(TileSize);
	// Define wall ids
	map->setTileType(3, MapLayer::WALL);
	map->setTileType(5, MapLayer::WALL);
	map->setTileType(10, MapLayer::WALL);

	// View settings
	view.reset(sf::FloatRect(0.0f, 0.0f, 1024, 640));
	//view.setViewport(FloatRect(0.0f, 0.0f, 0.5f, 0.5f)); // ������� ����
	//view.setSize(1280, 800);                             // �����������
	//view.reset(FloatRect(offsetX, offsetY, Width, Height)); // ��������
	//Sprite Map; Map.setTexture(res::MapTexture); Map.setTILE_SIZE(4, 4); Map.setTextureRect(IntRect(16, 0, 16, 16));

	// Init player
	player.setTexture(Content::playerTexture);
	player.setTileMap(*map);
	player.setItemLayer(itemLayer);

    DebugGraphics::enabled = true;

    createUI();
    createItem();
}

void Application::createUI()
{
    // Layers
    menuLayer = new UILayer(&stack);
    gameLayer = new UILayer(&stack);
    stack.pushLayer(menuLayer);
    stack.pushLayer(gameLayer);
    // Controls
    player.inventory = new Inventory(gameLayer);
    start = new UIButton(menuLayer);
    quit = new UIButton(menuLayer);
    win = new UIWindow(gameLayer);

    //("Start", sf::Color::Black, res::font);
	start->setPosition((float)window.getSize().x / 2 - 100, 350);
	start->setColor(sf::Color::Green);

	// ("Quit", sf::Color::Black, res::font);
	quit->setPosition((float)window.getSize().x / 2 - 100, 470);
	quit->setColor(sf::Color::Green);

    gameLayer->pushControl(player.inventory);
    menuLayer->pushControl(start);
    menuLayer->pushControl(quit);
    gameLayer->pushControl(win);

    menuLayer->setVisible(true);

    menuLayer->setVisible(true);
	///////////////////////////////////////////
	win->setPosition(100, 100);

    gameLayer->setVisible(false);
}

void Application::createItem()
{
    itemLayer = new ItemLayer(&stack);
    stack.pushLayer(itemLayer);
    // Apple
    Item* item = new Item();
    (*item).construct(Content::itemSet, sf::IntRect(0, 0, TileSize, TileSize));
    //ItemLayer::pushItem(uiItem);

    Item* item2 = new Item();
    (*item2).construct(Content::itemSet, sf::IntRect(0, 0, TileSize, TileSize));
    item2->setTilePosition(sf::Vector2f(10, 12));

    itemLayer->pushItem(item2);

    // Add UIItem to inventory
    auto* uiItem = new UIItem(item);
    uiItem->setFillColor(sf::Color::Transparent);
    gameLayer->pushControl(uiItem);

    player.inventory->getFirstEmptyCell()->addChild(uiItem);//setItem(uiItem);
}

void Application::onPullWindowEvents()
{
	sf::Event event{};

    // Poll all events from the window queue
	while (window.pollEvent(event))
	{
        // push event
        stack.onEvent(event);

	    bool handled = false;
        // Check EventType
        switch(event.type)
        {
            case sf::Event::Closed:
                onWindowClosed();
                break;
            case sf::Event::Resized:
                onWindowResized(event);
                break;
            case sf::Event::EventType::MouseMoved:
                onMouseMoved(event);
                break;
            case sf::Event::MouseButtonPressed:
                //while(!handled)
                //{
                //    handled;
                //}
                onMouseButtonPressed(event);
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::EventType::MouseWheelScrolled:
                onMouseWheelScrolled(event);
                break;
            case sf::Event::KeyPressed:
                onKeyPressed(event);
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::EventType::MouseLeft:
                mouseLeave = true;
                break;
            case sf::Event::EventType::MouseEntered:
                mouseLeave = false;
                break;
        }
	}
}

void Application::onUpdate()
{
	// Elapsed time
	float deltaTime = clock.getElapsedTime().asSeconds();
	if (deltaTime > 1 || mouseLeave) deltaTime = 0;
	time = deltaTime;
	// Set FPS at title
	float framesCount = 1 / deltaTime;
    char temp[10]; sprintf(temp, "%.2f", framesCount); // Convert float to -> string
	window.setTitle(std::string("Bulwark    FPS ") + temp);
	// Restart the clock
	deltaTime *= 60;
	clock.restart();

	// ���������� ������
    stack.onUpdate();
	player.update(deltaTime);

	// View follow player
	view.setCenter(player.getPosition());
	// Window follow view
    window.setView(view);

	//sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	//std::cout << "MX " << MousePos.x / 64 << " MY " << MousePos.y / TileSize << std::endl;
}

void Application::onRender()
{
	// Map
	//map.onRender(window);
    stack.onDraw(window);
	// Player
	player.draw(window);
	// Layers

	// Debug
	DebugGraphics::draw(window);

    onRenderText("X ", player.getPosition().x / TileSize, sf::Vector2f(window.getSize().x - 154, 550));
    onRenderText("Y ", player.getPosition().y / TileSize, sf::Vector2f(window.getSize().x - 154, 580));
    onRenderText("FPS ", (float) 1.0f / time, sf::Vector2f(window.getSize().x - 134, 0));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Application::onPullEventsMenu()
{
	sf::Event event{};
	// Poll all events from the queue
	while (window.pollEvent(event))
	{


	    // Check event type
	    switch(event.type) {
            case sf::Event::Closed:
                onWindowClosed();
                break;
            case sf::Event::Resized:
                onWindowResized(event);
                break;
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseButtonPressed:
                {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //UIBase *over = stack.getMouseOver();

                    //if (over == nullptr) break;

                    auto mouseGlobalPos = (sf::Vector2f)sf::Mouse::getPosition(window);

                    if (/*over == start*/ start->getGlobalBounds().contains(mouseGlobalPos))
                    {
                        gamePlay = true;
                        stack.popLayer(menuLayer);
                        delete menuLayer;

                        gameLayer->setVisible(true);
                    }
                    if (/*over == quit*/ quit->getGlobalBounds().contains(mouseGlobalPos))
                    {
                        window.close();
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // TODO add
                }

                break;
            }
        }
	}
}

void Application::onUpdateMenu()
{
	// ���������� ������
    stack.onUpdate();
}

void Application::onRenderMenu()
{
	// Background
    sf::Sprite grass(Content::tileSet, sf::IntRect(0, 16 * 2, 16, 16));
	grass.setScale(sf::Vector2f(4, 4));
	for (int Y = 0; Y < window.getSize().y / TileSize; Y++)
	{
		for (int X = 0; X < window.getSize().x / TileSize; X++)
		{
			int x = X * TileSize;
			int y = Y * TileSize;

			grass.setPosition((float) x,(float) y);
			window.draw(grass);
		}
	}
	// Logo
	sf::Sprite logo(Content::menuTexture);
	logo.setPosition(0, 0);
	window.draw(logo);
	// Layers
    stack.onDraw(window);
	// Debug
	DebugGraphics::draw(window);
}

void Application::onRenderText(const char *string, float num, sf::Vector2f position)
{
    sf::Text Text("", Content::font, 40);
    Text.setFillColor(sf::Color::Black);

    char temp[10]; sprintf(temp, "%.2f", num); // Convert float to -> string

    Text.setString(string + std::string(temp));
    Text.setPosition(sf::Vector2f(position));
    // Draw without offset
    window.draw(Text, getViewTransformOffSet(window));
}

void Application::onWindowClosed()
{
    window.close();
}

void Application::onWindowResized(sf::Event& event)
{
    // Reset window and view size
    window.setSize(sf::Vector2u(event.size.width, event.size.height));
    view.reset(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height));
}

void Application::onMouseMoved(sf::Event &event)
{
    mousePos = {event.mouseMove.x, event.mouseMove.y};
}

void Application::onMouseButtonPressed(sf::Event& event)
{
    player.onMouseButtonPressed(event);
}

void Application::onMouseWheelScrolled(sf::Event& event)
{
    if (event.mouseWheel.delta == 1 && player.inventory->selectedCell >= 1)
        --player.inventory->selectedCell;
    else if (event.mouseWheel.delta == -1 && player.inventory->selectedCell <= 3)
        ++player.inventory->selectedCell;
}

void Application::onKeyPressed(sf::Event& event)
{
    switch(event.key.code)
    {
        case sf::Keyboard::E:
            break;
        case sf::Keyboard::F:
            break;
        case sf::Keyboard::G:
            break;
        case sf::Keyboard::Q:
            player.dropUp(player.inventory->getSelectedCell());
            break;
        case sf::Keyboard::Num1:
            player.inventory->selectedCell = 0;
            break;
        case sf::Keyboard::Num2:
            player.inventory->selectedCell = 1;
            break;
        case sf::Keyboard::Num3:
            player.inventory->selectedCell = 2;
            break;
        case sf::Keyboard::Num4:
            player.inventory->selectedCell = 3;
            break;
        case sf::Keyboard::Num5:
            player.inventory->selectedCell = 4;
            break;
    }
}