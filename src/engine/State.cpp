//
// Created by Samuel Gallay on 2019-06-02.
//

#include "State.h"
#include "GameEngine.h"

void State::build(
        const std::shared_ptr<GameEngine> &engine,
        const std::shared_ptr<sf::RenderWindow> &window) {
    stateEngine = engine;
    State::window = window;
}

void State::initialize() {

}

