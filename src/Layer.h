#pragma once
#include <SFML/Graphics.hpp>

class LayerStack;
///////////////////////////////////////
/// A structure witch will
/// keep controls
///////////////////////////////////////
// TODO add UILayer ItemLayer MapLayer
class Layer
{
protected:
    explicit Layer(LayerStack& stack);

    bool visible;

    LayerStack& stack;

public:
    const sf::RenderWindow& window;

    virtual void onUpdate() = 0;
    virtual void onDraw(sf::RenderWindow& win) = 0;

    // TODO onEvent(Event e);
    // virtual void onEvent() = 0;
public:
    virtual std::string getName() const = 0;
    inline bool isVisible() const        { return visible; };
    inline void setVisible(bool visible_) { this->visible = visible_; };


};