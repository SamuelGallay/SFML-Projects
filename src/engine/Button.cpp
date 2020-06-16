#include "Button.h"

void Button::set(std::string t,
               const sf::Font &f,
               std::shared_ptr<sf::RenderWindow> w,
               std::function<void(void)> c){
    text.setString(t);
    text.setFont(f);
    window = w;
    callback = c;

    sf::FloatRect flRect = text.getGlobalBounds();
    rect.setPosition(flRect.left - 20, flRect.top - 20);
    rect.setSize(sf::Vector2f(flRect.width + 40, flRect.height + 40));
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(3.f);
}

void Button::update(){
    sf::Vector2f mp = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    sf::FloatRect fr = getTransform().transformRect(rect.getGlobalBounds());

    if (fr.contains(mp)){
        rect.setFillColor(sf::Color(100, 100, 100));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            callback ();
    }
    else
        rect.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(rect, states);
    target.draw(text, states);
}
