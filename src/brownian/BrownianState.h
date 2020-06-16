#ifndef GAMEENGINE_BROWNIANSTATE_H
#define GAMEENGINE_BROWNIANSTATE_H

#include "State.h"
#include <vector>

class BrownianState : public State{
public:
    virtual void update(sf::Time dt);

    virtual void handleEvent(sf::Event event);

    virtual void draw();

    virtual void initialize();

private:
    int Nparticles;
    sf::CircleShape bigParticle;
    std::vector<sf::Vector2f> velocity;
    sf::VertexArray list;
    sf::Vector2f bigSpeed;
    sf::VertexArray path;
};


#endif
