#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bulwark.h"
#include "Content.h"
#include "Global.h"

int main()
{
	// Window settings
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Bulwark", sf::Style::Close);
	window.setPosition(sf::Vector2i(256, 16));
	window.setVerticalSyncEnabled(true); //VSYNC
	window.setFramerateLimit(10);
	// Cursor
	window.setMouseCursorVisible(true);
	window.setMouseCursorGrabbed(false);
	sf::Cursor cursor; cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);
	//system("help");

	// Content
	ContentManager::loadContent();
	
	// Main class
	Bulwark program;

	std::cout << "Bulwark size: " << sizeof(program) << " bytes" << std::endl;
	
	// Main loop
	while (window.isOpen())
	{
		
		// Clear	
		window.clear(sf::Color::White);
		//system("cls");

		if (program.isGamePlay()) {
			// Input 
			program.pollEnvent();
			// Update
			program.update();
			// Draw
			program.draw();
		}
		else {
			program.pollEnventMenu();
			program.updateMenu();
			program.drawMenu();
		}

		window.display();
	}
	return 0;
}
