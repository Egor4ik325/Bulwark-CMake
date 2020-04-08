#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bulwark.h"
#include "Content.h"
#include "Global.h"

int main()
{
    // res
    Content::loadContent();

    // Application class
    Bulwark app;

    std::cout << "Bulwark size: " << sizeof(app) << " bytes" << std::endl;

    // Main loop
    while (app.window.isOpen())
    {

        // Clear
        app.window.clear(sf::Color::White);
        //system("cls");

        if (app.gamePlay){
            // Input
            app.onPullEvents();
            // Update
            app.onUpdate();
            // Draw
            app.draw();
        }
        else {
            app.onPullEventsMenu();
            app.onUpdateMenu();
            app.drawMenu();
        }

        app.window.display();
    }
    return 0;
}

