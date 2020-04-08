#include "Bulwark.h"
#include "Content.h"
#include "Global.h"
#include "DebugRect.h"
#include "Item/ItemLayer.h"
#include "UI/UIItem.h"
#include <cstdio>

Bulwark::Bulwark() :
    time(0.f),
    menuLayer(nullptr), gameLayer(nullptr), win(nullptr), start(nullptr), quit(nullptr),
    itemLayer(nullptr),
    WIDTH(1024), HEIGHT(640),
    stack(window)
{
	// Menu
	gamePlay = false;
	// RenderWindow
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Bulwark", sf::Style::Default);
    window.setPosition(sf::Vector2i(256, 100));
    window.setVerticalSyncEnabled(true);  // VSYNC
#if BW_DEBUG
    window.setFramerateLimit(10);           // Only for debugging
#endif
    // Cursor
    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(false);
    sf::Cursor cursor; cursor.loadFromSystem(sf::Cursor::Arrow);
    window.setMouseCursor(cursor);
    //system("help");

    // TileMap
	map.loadFromFile(Content::CONTENT_DIR + "Map.tmx");   // ����� 30x30
	map.setTileSize(TILE_SIZE);
	// Define wall ids
	map.setTileType(3, TileMap::WALL);
	map.setTileType(5, TileMap::WALL);
	map.setTileType(10, TileMap::WALL);

	// View
	view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
	//view.setViewport(FloatRect(0.0f, 0.0f, 0.5f, 0.5f)); // ������� ����
	//view.setSize(1280, 800);                             // �����������
	//view.reset(FloatRect(offsetX, offsetY, WIDTH, HEIGHT)); // ��������
	//Sprite Map; Map.setTexture(res::MapTexture); Map.setTILE_SIZE(4, 4); Map.setTextureRect(IntRect(16, 0, 16, 16));

	// Init player
	player.setTexture(Content::playerTexture);
	player.setTileMap(map);
	player.setItemLayer(itemLayer);

	DebugRect::enabled = true;

    createUI();
    createItem();
}

void Bulwark::createUI()
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
	start->setPosition((float)WIDTH / 2 - 100, 350);
	start->setColor(sf::Color::Green);

	// ("Quit", sf::Color::Black, res::font);
	quit->setPosition((float)WIDTH / 2 - 100, 470);
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

void Bulwark::createItem()
{
    itemLayer = new ItemLayer(&stack);
    stack.pushLayer(itemLayer);
    // Apple
    Item* item = new Item();
    (*item).construct(Content::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    //ItemLayer::pushItem(uiItem);

    Item* item2 = new Item();
    (*item2).construct(Content::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    item2->setTilePosition(sf::Vector2f(10, 12));

    itemLayer->pushItem(item2);

    // Add UIItem to inventory
    auto* uiItem = new UIItem(item);
    uiItem->setFillColor(sf::Color::Transparent);
    gameLayer->pushControl(uiItem);

    player.inventory->getFirstEmptyCell()->addChild(uiItem);//setItem(uiItem);
}

void Bulwark::onPullEvents()
{
	sf::Event event{};
    // Poll all events from the queue
	while (window.pollEvent(event))
	{
        // Check event type
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                {
                WIDTH = event.size.width;
                HEIGHT = event.size.height;
                // Reset window and view size
                window.setSize(sf::Vector2u(WIDTH, HEIGHT));
                view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
                break;
            }
            case sf::Event::KeyPressed:
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
                break;
            }
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelMoved:
            {
                if (event.mouseWheel.delta == 1 && player.inventory->selectedCell >= 1)
                    --player.inventory->selectedCell;
                else if (event.mouseWheel.delta == -1 && player.inventory->selectedCell <= 3)
                    ++player.inventory->selectedCell;

                break;
            }
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    // ���� ������ �� ��������� ��� �����������
                    // TODO
                    //if (stack.getMouseOver() != nullptr) break;

                    sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    player.goTo(MousePos.x, MousePos.y);
                    break;
                }
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    //if (stack.getMouseOver() != nullptr) break;

                    sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    player.goTo(MousePos.x, MousePos.y);
                    player.setPicking(true);
                    break;
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
                break;
        }
	}
}

void Bulwark::onUpdate()
{
	// Elapsed time
	float deltaTime = clock.getElapsedTime().asSeconds();
	if (deltaTime > 1) deltaTime = 0;
	time = deltaTime;
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
	//std::cout << "MX " << MousePos.x / 64 << " MY " << MousePos.y / TILE_SIZE << std::endl;
}

void Bulwark::draw()
{
	// Map
	map.draw(window);
	// Player
	player.draw(window);
	// Layers
    stack.onDraw(window);
	// Debug
	DebugRect::draw(window);

    drawText("X ",   player.getPosition().x / TILE_SIZE, sf::Vector2f(WIDTH - 154, 550));
    drawText("Y ",   player.getPosition().y / TILE_SIZE, sf::Vector2f(WIDTH - 154, 580));
    drawText("FPS ", (float) 1.f / time,                 sf::Vector2f(WIDTH - 134, 0));
}

void Bulwark::drawText(const char *string, float data, sf::Vector2f position)
{
	sf::Text Text("", Content::font, 40);
	Text.setFillColor(sf::Color::Black);

	char temp[10]; sprintf(temp, "%.2f", data); // Convert float to -> string

	Text.setString(string + std::string(temp));
	Text.setPosition(sf::Vector2f(position));
	// Draw without offset
	window.draw(Text, getViewTransformOffSet(window));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bulwark::onPullEventsMenu()
{
	sf::Event event{};
	// Poll all events from the queue
	while (window.pollEvent(event))
	{
	    // Check event type
	    switch(event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::Resized:
                {
                // TODO change WIDTH and HEIGHT
                WIDTH  = event.size.width; HEIGHT = event.size.height;
                // Reset window and view size
                window.setSize(sf::Vector2u(WIDTH, HEIGHT));
                view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
                break;
                }
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseWheelScrolled:
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
            case sf::Event::MouseButtonReleased:
                break;
        }
	}
}

void Bulwark::onUpdateMenu()
{
	// ���������� ������
    stack.onUpdate();
}

void Bulwark::drawMenu()
{
	// Background
    sf::Sprite grass(Content::tileSet, sf::IntRect(0, 16 * 2, 16, 16));
	grass.setScale(sf::Vector2f(4, 4));
	for (int Y = 0; Y < HEIGHT/TILE_SIZE; Y++)
	{
		for (int X = 0; X  < WIDTH/TILE_SIZE; X++)
		{
			int x = X * TILE_SIZE;
			int y = Y * TILE_SIZE;

			grass.setPosition(x, y);
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
	DebugRect::draw(window);
}