#include "Spaceship.hpp"

#include <cmath>

Spaceship::Spaceship()
{
    texture.loadFromFile("media/spaceship.png");
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width/2.f, sprite.getLocalBounds().height/2.f);
    sprite.scale(0.1, 0.1);
    setPosition(0, -6371000);
    setVelocity(sf::Vector2f(0, 0));
    setMass(3000);
}

Spaceship::Spaceship(Spaceship const& old) : Physical(old), texture(old.texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width/2.f, sprite.getLocalBounds().height/2.f);
    sprite.scale(0.1, 0.1);
}

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Spaceship::input(sf::Time dt){
    float a = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        a += 40;
    float angle = getRotation() * 3.1415 / 180.f;
    sf::Vector2f acc(sin(angle)*a,-cos(angle)*a);
    setVelocity(getVelocity() + acc*dt.asSeconds());
    
    float w = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        w += 30;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        w -= 30;
    setAngularVelocity(getAngularVelocity()+w*dt.asSeconds());
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        setAngularVelocity(0);
}

