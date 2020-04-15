#include "SFML/Graphics.hpp"
#include <iostream>

#include "Application.h"
#include "Content.h"
#include "Global.h"

int main()
{
    // res
    Content::loadContent();

    // Application class
    Application bulwark;

    std::cout << "Application size: " << sizeof(bulwark) << " bytes" << std::endl;

    // Main loop
    while (bulwark.window.isOpen())
    {

        // Clear
        bulwark.window.clear(sf::Color::White);
        //system("cls");

        if (bulwark.gamePlay){
            // Input
            bulwark.onPullWindowEvents();
            // Update
            bulwark.onUpdate();
            // Draw
            bulwark.onRender();
        }
        else {
            bulwark.onPullEventsMenu();
            bulwark.onUpdateMenu();
            bulwark.onRenderMenu();
        }

        bulwark.window.display();
    }
    return 0;
}

