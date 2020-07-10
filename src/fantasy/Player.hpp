#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>

#include "engine.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player(std::shared_ptr<sf::Texture> t);
    void changeDirection(sf::Vector2i direction, float temps);
    void update();
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    
private:
    std::shared_ptr<sf::Texture> terraTexture;
    sf::Sprite terra;
    sf::Clock clock;
    
    float tempsDeplacement;
};

#endif /* Player_hpp */
