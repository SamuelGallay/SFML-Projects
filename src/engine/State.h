//
// Created by Samuel Gallay on 2019-06-02.
//

#ifndef GAMEENGINE_STATE_H
#define GAMEENGINE_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>

class GameEngine;

class State {
public:
    virtual void update(const float dt) = 0;

    virtual void handleEvent(sf::Event event) = 0;

    void build(
            const std::shared_ptr<GameEngine> &engine,
            const std::shared_ptr<sf::RenderWindow> &window);

    virtual void draw() = 0;

    virtual void initialize();

protected:
    std::shared_ptr<GameEngine> stateEngine;
    std::shared_ptr<sf::RenderWindow> window;
};


#endif //GAMEENGINE_STATE_H
