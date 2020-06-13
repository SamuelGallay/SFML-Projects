#ifndef Starship_hpp
#define Starship_hpp

#include <SFML/Graphics.hpp>
#include "Physical.hpp"

class Spaceship : public Physical
{
public:
    Spaceship();
    Spaceship(Spaceship const&);
    void input(sf::Time dt);
    
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* Starship_hpp */
