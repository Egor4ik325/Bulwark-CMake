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

    //sf::RenderWindow& window;
public:
    virtual void onUpdate() = 0;
    // TODO argument isn't required
    virtual void onDraw(sf::RenderWindow& win) = 0;

    inline virtual void onEvent(sf::Event& event) {};
    // virtual void onEvent() = 0;

    virtual std::string getName() const = 0;
    inline bool isVisible() const        { return visible; };
    inline void setVisible(bool visible_) { this->visible = visible_; };
};