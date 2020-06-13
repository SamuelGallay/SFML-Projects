#ifndef GAMEENGINE_MENUSTATE_H
#define GAMEENGINE_MENUSTATE_H

#include "State.h"

class MenuState : public State{
public:
    virtual void update(const float dt);

    virtual void handleEvent(sf::Event event);

    virtual void draw();

    virtual void initialize();

private:
    sf::CircleShape circle;
    sf::Text text;
    sf::RectangleShape rectangle;

    sf::Font myFont;
};


#endif //GAMEENGINE_MENUSTATE_H
