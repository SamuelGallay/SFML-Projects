#ifndef GAMEENGINE_MENUSTATE_H
#define GAMEENGINE_MENUSTATE_H

#include "State.h"

class MenuState : public State{
public:
    virtual void update(sf::Time dt);

    virtual void handleEvent(sf::Event event);

    virtual void draw();

    virtual void initialize();

private:
    sf::CircleShape circle;
    sf::Text text;
    sf::Text text2;
    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle2;
    sf::Font myFont;
};


#endif
