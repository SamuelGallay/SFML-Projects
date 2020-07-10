#ifndef TileMap_h
#define TileMap_h

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
    bool load(std::shared_ptr<sf::Texture> t, sf::Vector2u tileSize, std::vector<std::vector<int> > tiles, unsigned int width, unsigned int height);
    
private:
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif /* TileMap_h */
