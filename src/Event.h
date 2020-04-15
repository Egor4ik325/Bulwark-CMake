#pragma once
#include <SFML/Graphics.hpp>

/// Own Event class
class Event : public sf::Event
{
public:
    Event();

    bool handled;

    void dispatchEvent(sf::Event::EventType type);

};