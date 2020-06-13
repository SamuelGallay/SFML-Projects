#include "Planet.hpp"
#include <cmath>

Planet::Planet(){
    setPosition(sf::Vector2f(0,0));
    setVelocity(sf::Vector2f(0,0));
    circle.setRadius(100);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPointCount(10000);
    setMass(1);
    circle.setFillColor(sf::Color::Blue);
}

Planet::Planet(Planet const& old) : Physical(old), circle(old.circle)
{
    
}

Planet::Planet(sf::Vector2f pos, sf::Vector2f vel, float rad, float mas, sf::Color col){
    circle.setRadius(rad);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPointCount(10000);
    circle.setFillColor(col);
    setMass(mas);
    setPosition(pos);
    setVelocity(vel);
}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(circle, states);
}
