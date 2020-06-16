#include "MenuState.h"
#include "BrownianState.h"
#include "GameEngine.h"

#include "SpaceState.hpp"

#include "ResourceHolder.h"

void MenuState::update(sf::Time dt) {
    button.update();
    button2.update();
}

void MenuState::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        window->close();
}

void MenuState::draw(){
    window->draw(button);
    window->draw(button2);
}

void MenuState::initialize() {

    button.set("Hello World!", holder->font.get("media/FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<BrownianState>();});
    button.setPosition(300, 200);
    
    button2.set("Hello Xorld!", holder->font.get("media/FiraSans-Light.otf"),
               window, [this]{stateEngine->buildState<SpaceState>();});
    button2.setPosition(300, 350);

}
