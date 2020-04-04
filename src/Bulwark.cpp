#include "Bulwark.h"
#include "Content.h"
#include "Global.h"
#include "DebugRect.h"
#include "ItemManager.h"
#include "UIItem.h"
#include <cstdio>

Bulwark::Bulwark() : time(0.f),
    menuScreen(nullptr), gameScreen(nullptr), win(nullptr), start(nullptr), quit(nullptr)
{
	// Menu
	gamePlay = false;
	// TileMap
	map.loadFromFile(ContentManager::CONTENT_DIR + "Map.tmx");   // ����� 30x30
	map.setTileSize(TILE_SIZE);
	map.setTileType(3, TileMap::WALL); map.setTileType(5, TileMap::WALL); map.setTileType(10, TileMap::WALL);

	// View
	view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
	//view.setViewport(FloatRect(0.0f, 0.0f, 0.5f, 0.5f)); // ������� ����
	//view.setSize(1280, 800);                             // �����������
	//view.reset(FloatRect(offsetX, offsetY, WIDTH, HEIGHT)); // ��������
	//Sprite Map; Map.setTexture(Content::MapTexture); Map.setTILE_SIZE(4, 4); Map.setTextureRect(IntRect(16, 0, 16, 16));

	// Init player
	player.setTexture(ContentManager::playerTexture);
	player.setTileMap(map);

	DebugRect::enabled = true;

    createUI();

	// ������
	Item* item = new Item();
	(*item).construct(ContentManager::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	//ItemManager::addItem(uiItem);

	Item* item2 = new Item();
	(*item2).construct(ContentManager::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	item2->setTilePosition(sf::Vector2f(10, 12));
	ItemManager::addItem(item2);

	// Add uiItem to inventory
	auto* uiItem = new UIItem(item);
	uiItem->setFillColor(sf::Color::Transparent);
	gameScreen->addControl(uiItem);

	player.inventory->getFirstEmptyCell()->addChild(uiItem);//setItem(uiItem);
}

void Bulwark::createUI()
{
    menuScreen = new UIScreen;
    gameScreen = new UIScreen;
    player.inventory = new Inventory(gameScreen);
    start = new UIButton(menuScreen);
    quit = new UIButton(menuScreen);
    win = new UIWindow(gameScreen);

    //("Start", sf::Color::Black, ContentManager::font);
	start->setPosition(WIDTH / 2 - 100, 350);
	start->setColor(sf::Color::Green);

	// ("Quit", sf::Color::Black, ContentManager::font);
	quit->setPosition(WIDTH / 2 - 100, 470);
	quit->setColor(sf::Color::Green);

    gameScreen->addControl(player.inventory);
	menuScreen->addControl(start);
	menuScreen->addControl(quit);
    gameScreen->addControl(win);

	menuScreen->visible = true;
	///////////////////////////////////////////
	win->setPosition(100, 100);

	gameScreen->visible = false;

	/////////////////////////////////////////

}

void Bulwark::pollEnvent()
{
	sf::Event event;
    // Poll all events from the queue
	while (window.pollEvent(event))
	{
        // Check event type
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::Resized:
            {
                // TODO add
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
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    // ���� ������ �� ��������� ��� �����������
                    if (UIManager::getMouseOver() == nullptr)
                    {
                        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        player.goTo(MousePos.x, MousePos.y);
                    }
                }

                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    if (UIManager::getMouseOver() == nullptr)
                    {
                        sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        player.goTo(MousePos.x, MousePos.y);
                        player.setPicking(true);
                    }
                }


                break;
            }
            case sf::Event::MouseButtonReleased:
                break;
        }

		if (event.type == sf::Event::Closed)

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{

			}
			if (event.key.code == sf::Mouse::Right)
			{
				// ���� ������ �� ��������� ��� �����������

			}
		}
		
		if (event.type == sf::Event::MouseLeft)
		{

		}
		if (event.type == sf::Event::MouseEntered)
		{

		}
		// �������� ������� ����
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta == 1 && player.inventory->selectedCell >= 1)
				--player.inventory->selectedCell;
			else if (event.mouseWheel.delta == -1 && player.inventory->selectedCell <= 3)
				++player.inventory->selectedCell;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			player.inventory->selectedCell = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			player.inventory->selectedCell = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			player.inventory->selectedCell = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			player.inventory->selectedCell = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			player.inventory->selectedCell = 4;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			InventoryCell* cell = player.inventory->getSelectedCell();
			player.dropUp(cell);
		}
	}
}

void Bulwark::update()
{
	// Elapsed time
	float deltaTime = clock.getElapsedTime().asSeconds();
	if (deltaTime > 1) deltaTime = 0;
	time = deltaTime;
	// Restart the clock
	deltaTime *= 60;
	clock.restart();

	// ���������� ������
	UIManager::update();
	player.update(deltaTime);

	// Window follow view
	window.setView(view);
	// View follow player
	view.setCenter(player.getPosition());

	// Mouse position
	//sf::Vector2f MousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	//std::cout << "MX " << MousePos.x / 64 << " MY " << MousePos.y / TILE_SIZE << std::endl;
}

void Bulwark::draw()
{
	// Map
	map.draw(window);
	// Player
	player.draw(window);
	// UI
	UIManager::draw(window);
	// Debug
	DebugRect::draw(window);
	// Item
	ItemManager::draw(window);

	// Text TODO make better
	drawText("X ", player.getPosition().x / TILE_SIZE, sf::Vector2i(WIDTH - 154, 550));
	drawText("Y ", player.getPosition().y / TILE_SIZE, sf::Vector2i(WIDTH - 154, 580));
	drawText("FPS ", (float) 1.f / time, sf::Vector2i(WIDTH - 134, 0));
}

void Bulwark::drawText(const char* text, float data, const sf::Vector2i position, const char* count)
{
	sf::Text Text; Text.setString(""); Text.setFont(ContentManager::font); Text.setCharacterSize(40); Text.setFillColor(sf::Color::Black);

	char temp[10];
	sprintf(temp, "%f", data); // convert float -> string

	Text.setString(text + std::string(temp));

	Text.setPosition(sf::Vector2f(position));

	window.draw(Text, getViewTransformOffSet());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bulwark::pollEnventMenu()
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
            case sf::Event::Resized: {
                // TODO change WIDTH and HEIGHT
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
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    UIBase *over = UIManager::getMouseOver();
                    if (over == nullptr) break;

                    if (over == start) {
                        gamePlay = true;
                        UIManager::deleteScreen(menuScreen);
                        gameScreen->visible = true;
                    }
                    if (over == quit) {
                        window.close();
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // TODO add
                }

                break;
            }
            case sf::Event::MouseButtonReleased:
                break;
        }
	}
}

void Bulwark::updateMenu()
{
	// ���������� ������
	UIManager::update();
}

void Bulwark::drawMenu()
{
	// Background
    sf::Sprite grass(ContentManager::tileSet, sf::IntRect(0, 16 * 2, 16, 16));
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
	sf::Sprite logo(ContentManager::menuTexture);
	logo.setPosition(0, 0);
	window.draw(logo);
	// UI
	UIManager::draw(window);
	// Item
	ItemManager::draw(window);
	// Debug
	DebugRect::draw(window);
}

bool Bulwark::isGamePlay() const
{
	return gamePlay;
}



