#ifndef Level_hpp
#define Level_hpp

#include "TileMap.hpp"
#include <vector>
#include <SFML/Audio.hpp>

#include "engine.h"

struct Inventory{
    int gold;
};

class Level : public sf::Drawable, public sf::Transformable{
    public:
        Level(std::shared_ptr<Holder> holder);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool operator()(sf::Vector2i pos);
    
        Inventory getInventory();

        ~Level();
    
    private:
        TileMap map;
        std::vector<std::vector<int> > level;
        sf::Vector2i dim;
    
        sf::VertexArray goldMap;
        std::vector<sf::Vector2i> goldList;
        std::shared_ptr<sf::Texture> goldTexture;
        sf::Sound coinSound;
        Inventory stuff;
        void goldListToMap();
        std::shared_ptr<Holder> holder;
};

#endif /* Level_hpp */
