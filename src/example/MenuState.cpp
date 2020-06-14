#include "MenuState.h"
#include "BrownianState.h"
#include "GameEngine.h"

#include "SpaceState.hpp"

#include "ResourceHolder.h"

void MenuState::update(sf::Time dt) {
    sf::Vector2f mousePositionFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    if (rectangle.getGlobalBounds().contains(mousePositionFloat))
        rectangle.setFillColor(sf::Color(100, 100, 100));
    else
        rectangle.setFillColor(sf::Color::Black);
}

void MenuState::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        window->close();
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        stateEngine->buildState<BrownianState>();

    if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mousePositionFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (rectangle.getGlobalBounds().contains(mousePositionFloat))
            stateEngine->buildState<BrownianState>();
    }


    if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mousePositionFloat = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (rectangle2.getGlobalBounds().contains(mousePositionFloat))
            stateEngine->buildState<SpaceState>();
    }

}

void MenuState::draw(){
    window->draw(rectangle);
    window->draw(circle);
    window->draw(text);
    window->draw(rectangle2);
    window->draw(text2);
}

void MenuState::initialize() {
    circle.setRadius(100.f);
    text.setString("Hello World !");
    text.setPosition(300, 200);
    
    text2.setString("Hello Xorld !");
    text2.setPosition(300, 350);


    auto myStream = stream_of_file("media/FiraSans-Light.otf");
    myFont.loadFromStream(myStream);
    text.setFont(myFont);
    text2.setFont(myFont);

    auto flRect = text.getGlobalBounds();
    rectangle.setPosition(flRect.left - 20, flRect.top - 20);
    rectangle.setSize(sf::Vector2f(flRect.width + 40, flRect.height + 40));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineThickness(3.f);

    auto flRect2 = text2.getGlobalBounds();
    rectangle2.setPosition(flRect2.left - 20, flRect2.top - 20);
    rectangle2.setSize(sf::Vector2f(flRect2.width + 40, flRect2.height + 40));
    rectangle2.setFillColor(sf::Color::Black);
    rectangle2.setOutlineThickness(3.f);


}
