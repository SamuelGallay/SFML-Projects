#include "Player.hpp"

Player::Player(std::shared_ptr<sf::Texture> t){
    terraTexture = t;
    terra.setTexture(*terraTexture);
    terra.setTextureRect(sf::IntRect(32, 0, 32, 32));
    terra.setOrigin(16, 16);
}

void Player::changeDirection(sf::Vector2i direction, float temps){
    if(direction == sf::Vector2i(0,1))
        terra.setTextureRect(sf::IntRect(32, 0, 32, 32));
    if(direction == sf::Vector2i(1,0))
        terra.setTextureRect(sf::IntRect(32, 64, 32, 32));
    if(direction == sf::Vector2i(0,-1))
        terra.setTextureRect(sf::IntRect(32, 96, 32, 32));
    if(direction == sf::Vector2i(-1,0))
        terra.setTextureRect(sf::IntRect(32, 32, 32, 32));
    
    tempsDeplacement = temps;
    clock.restart();
}

void Player::update(){
    sf::IntRect a = terra.getTextureRect();
    if(clock.getElapsedTime().asSeconds() < tempsDeplacement/2.f)
        a.left = 0;
    else if(clock.getElapsedTime().asSeconds() < tempsDeplacement)
        a.left = 64;
    else
        a.left = 32;
    terra.setTextureRect(a);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();
    
    // on applique la texture du tileset
    states.texture = &*terraTexture;
    
    target.draw(terra, states);
}

