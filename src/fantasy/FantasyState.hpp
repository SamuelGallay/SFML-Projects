#ifndef Application_hpp
#define Application_hpp


#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Level.hpp"

#include "engine.h"

class FantasyState : public State{
    
    public:
        void initialize();
        void update(sf::Time dt);
        void draw();
        void handleEvent(sf::Event event);


    private:
        sf::Vector2f pt(sf::Vector2i position){return sf::Vector2f(position.x*32+16.f,position.y*32+16.f);}
    
        std::shared_ptr<Level> niveau;
        float tempsDeplacement;
        float zoom;
        sf::Vector2i position;
        sf::Vector2i oldPosition;

        std::shared_ptr<Player> player;
        sf::Vector2i direction;
        sf::Clock clockDeplacement;

        sf::Text text;
        void drawInventory();
};

#endif
