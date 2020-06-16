#ifndef GAMEENGINE_STATE_H
#define GAMEENGINE_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "ResourceHolder.h"

class GameEngine;

class State {
public:
    virtual void update(sf::Time dt) = 0;

    virtual void handleEvent(sf::Event event) = 0;

    virtual void draw() = 0;

    virtual void initialize() = 0;
    
    void build(
        const std::shared_ptr<GameEngine>       &engine,
        const std::shared_ptr<sf::RenderWindow> &window,
        const std::shared_ptr<Holder>           &holder);


protected:
    std::shared_ptr<GameEngine>         stateEngine;
    std::shared_ptr<sf::RenderWindow>   window;
    std::shared_ptr<Holder>             holder;
};


#endif
