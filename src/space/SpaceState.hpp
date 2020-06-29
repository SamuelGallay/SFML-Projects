#ifndef SPACESTATE_H
#define SPACESTATE_H

#include "engine.h"
#include <vector>

#include "Spaceship.hpp"
#include "Planet.hpp"

class SpaceState : public State{
public:
    virtual void update(sf::Time dt);

    virtual void handleEvent(sf::Event event);

    virtual void draw();

    virtual void initialize();

private:
    std::vector<std::shared_ptr<Planet> > planets;

    std::shared_ptr<Planet> earth;
    
    std::shared_ptr<Spaceship> spaceship;
    
    sf::Font myFont;
    sf::View view;
    sf::Text text;

    float G;

    int cameraMode;
    float timespeed;
    int fps;
    float timesinceupdate;
    int framessinceupdate;

    sf::VertexArray traj;
    sf::CircleShape mark;

//void gravity_forces(std::vector<std::shared_ptr<Planet> > &planets, std::shared_ptr<Spaceship> &spaceship, sf::Time dt);
//bool collisions(std::vector<std::shared_ptr<Planet> > &planets, std::shared_ptr<Spaceship> &spaceship);
//sf::VertexArray runge_kutta(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f posEarth, float massEarth);

};


#endif
