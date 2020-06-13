#include "Physical.hpp"

Physical::Physical()
{
    velocity = sf::Vector2f(0, 0);
    angularVelocity = 0;
    mass = 0;
}

Physical::Physical(Physical const& orig) : velocity(orig.velocity), angularVelocity(orig.angularVelocity), mass(orig.mass)
{
    setPosition(orig.getPosition());
}

void Physical::update(sf::Time dt){
    move(dt.asSeconds() * velocity);
    rotate(dt.asSeconds() * angularVelocity);
}
