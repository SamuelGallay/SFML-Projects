#include "MenuState.h"
#include "PongState.hpp"
#include "SpaceState.hpp"
#include "BrownianState.h"
#include "MandelbrotState.h"

#include <iostream>

void MenuState::update(sf::Time dt) {
    button.update();
    button2.update();
    button3.update();
    button4.update();
}

void MenuState::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
        stateEngine->popState();
    }
}

void MenuState::draw(){
    window->draw(button);
    window->draw(button2);
    window->draw(button3);
    window->draw(button4);
}

void MenuState::initialize() {
    button.set("Brownian", holder->font.get("FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<BrownianState>();});
    button.setPosition(300, 150);
    
    button2.set("Space", holder->font.get("FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<SpaceState>();});
    button2.setPosition(300, 250);

    button3.set("Pong", holder->font.get("FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<PongState>();});
    button3.setPosition(300, 350);

    button4.set("Mandlebrot", holder->font.get("FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<MandelbrotState>();});
    button4.setPosition(300, 450);
}
