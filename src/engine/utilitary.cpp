#include "utilitary.hpp"
float norme(sf::Vector2f v){
    return sqrt(v.x*v.x + v.y*v.y);
}

void setStandardView(std::shared_ptr<sf::RenderWindow> w){
    w->setView(sf::View(sf::Rect<float>(sf::Vector2f(0,0), sf::Vector2f((float) w->getSize().x, (float) w->getSize().y))));
}
