#ifndef Earth_hpp
#define Earth_hpp

#include <SFML/Graphics.hpp>
#include "Physical.hpp"

class Planet : public Physical
{
public:
    Planet();
    Planet(Planet const&);
    Planet(sf::Vector2f pos, sf::Vector2f vel, float rad, float mas, sf::Color col);
    float getRadius() const{
        return circle.getRadius();
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::CircleShape circle;
};

#endif /* Earth_hpp */
