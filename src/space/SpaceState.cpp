#include "SpaceState.hpp"
#include "utilitary.hpp"
#include "ResourceHolder.h"
#include <cmath>
#include <iostream>


void gravity_forces(std::vector<std::shared_ptr<Planet> > &planets, std::shared_ptr<Spaceship> &spaceship, sf::Time dt)
{
    float G = 6.67 * pow(10,-11);
    for(unsigned int i=0; i<planets.size()-1; i++)
    {

        for(unsigned int j=i+1; j<planets.size(); j++){
            sf::Vector2f vij = planets[j]->getPosition()-planets[i]->getPosition();
            sf::Vector2f uij = vij/norme(vij);
            float F = G*planets[i]->getMass()*planets[j]->getMass()/norme(vij)/norme(vij);
            planets[i]->setVelocity(planets[i]->getVelocity() + F/planets[i]->getMass()*dt.asSeconds()*uij);
            planets[j]->setVelocity(planets[j]->getVelocity() + F/planets[j]->getMass()*dt.asSeconds()*-uij);
        }
    }
    for (auto const &i : planets){
        sf::Vector2f v = i->getPosition()-spaceship->getPosition();
        sf::Vector2f u = v/norme(v);
        spaceship->setVelocity(spaceship->getVelocity()+G*i->getMass()/norme(v)/norme(v)*dt.asSeconds()*u);
    }
}

bool collisions(std::vector<std::shared_ptr<Planet> > &planets, std::shared_ptr<Spaceship> &spaceship)
{
    bool col = false;
    for (auto const &i : planets){
        sf::Vector2f v = spaceship->getPosition()-i->getPosition();
        if (norme(v) < i->getRadius()){
            col = true;
            spaceship->setAngularVelocity(0);
            spaceship->setVelocity(sf::Vector2f(0, 0));
            spaceship->setPosition(v/norme(v)*i->getRadius()+i->getPosition() + 10.f*v/norme(v));
        }
    }
    return col;
}

sf::VertexArray runge_kutta(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f posEarth, float massEarth){
    float G = 6.67 * pow(10,-11);

    float h = 10.f; //Temps d'un pas en secondes
    int nPoints = 1000;

    sf::VertexArray lines(sf::LineStrip, nPoints);
    lines[0].position = pos;
    lines[0].color = sf::Color::Yellow;

    bool collision = false;

    for(int i=1; i<nPoints; i++){

        if(collision == false){
        sf::Vector2f v1 = posEarth - pos;
        sf::Vector2f u1 = v1/norme(v1);
        sf::Vector2f k1 = G*massEarth/norme(v1)/norme(v1)*u1;

        sf::Vector2f v2 = posEarth - (pos+h/2.f*vel);
        sf::Vector2f u2 = v2/norme(v2);
        sf::Vector2f k2 = G*massEarth/norme(v2)/norme(v2)*u2;

        sf::Vector2f v3 = posEarth - (pos+h/2.f*vel + h*h/4.f*k1);
        sf::Vector2f u3 = v3/norme(v3);
        sf::Vector2f k3 = G*massEarth/norme(v3)/norme(v3)*u3;

        sf::Vector2f v4 = posEarth - (pos + h*vel + h*h/2.f*k2);
        sf::Vector2f u4 = v4/norme(v4);
        sf::Vector2f k4 = G*massEarth/norme(v4)/norme(v4)*u4;

        pos += h*vel + h*h/6.f*(k1+k2+k3);
        vel += h/6.f*(k1 + 2.f*k2 + 2.f*k3 + k4);

        lines[i].position = pos;
        lines[i].color = sf::Color::Yellow;

        if (norme(pos - posEarth) < 6371000.f){
          collision = true;
        }
        }
        else{
          lines[i].position = pos;
          lines[i].color = sf::Color::Yellow;
        }
    }
    return lines;
}



void SpaceState::initialize(){
    earth = std::make_shared<Planet>(sf::Vector2f(0,0), 
        sf::Vector2f(0,0), 
        6371000.f,
        5.972*pow(10, 24), 
        sf::Color::Blue);

    planets.push_back(earth);

    spaceship = std::make_shared<Spaceship>();

    spaceship->setPosition(earth->getPosition().x, earth->getPosition().y - earth->getRadius());
    spaceship->setVelocity(sf::Vector2f(0,0));


    view = window->getDefaultView();
    view.setCenter(0, 0);
    view.zoom(earth->getRadius()/200.f);
    window->setView(view);

    G = 6.67 * pow(10,-11);

    cameraMode = 0;
    timespeed = 1.f;
    fps = 60;
    timesinceupdate = 0;
    framessinceupdate = 0; 
}

void SpaceState::update(sf::Time dt){
    timesinceupdate += dt.asSeconds();
    framessinceupdate++;
    if (timesinceupdate > 1){
        fps = framessinceupdate;
        framessinceupdate = 0;
        timesinceupdate = 0;
    }
    
    if(dt.asSeconds() > 1.f/50.f){
        dt = sf::seconds(1.f/60.f);
    }

    for(int i=0; i<(int)timespeed; i++){
        gravity_forces(planets, spaceship, dt);
        spaceship->input(dt);
        for (auto const &j : planets)
            j->update(dt);
        spaceship->update(dt);
        collisions(planets, spaceship);
    }

    //Marque la position du spaceship en O
    mark.setRadius(view.getSize().x/100.f);
    mark.setFillColor(sf::Color::Red);
    mark.setOrigin(mark.getRadius(), mark.getRadius());
    mark.setPosition(spaceship->getPosition());

    //Vue centrée
    if (cameraMode == 1){
        sf:: Vector2f pos = spaceship->getPosition();
        view.setCenter(0, 0);
        for (auto const &i : planets){
            i->move(-pos);
        }
        spaceship->move(-pos);
    }
    else if (cameraMode == 0){
        sf:: Vector2f pos = earth->getPosition();
        view.setCenter(0, 0);
        for (auto const &i : planets){
            i->move(-pos);
        }
        spaceship->move(-pos);
    }

    traj = runge_kutta(spaceship->getPosition(), spaceship->getVelocity(), earth->getPosition(), earth->getMass());

    text.setString("Altitude : " + to_string_with_precision((norme(spaceship->getPosition()-earth->getPosition())
    -earth->getRadius())/1000) +
                   " km\nVitesse : " + to_string_with_precision(norme(spaceship->getVelocity()/1000.f),3) + " km/s"+
                   "\n FPS : " + std::to_string(fps) );
    
}

void SpaceState::handleEvent(sf::Event event){
    if (event.type == sf::Event::Closed)
        window->close();
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window->close();
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
        view.zoom(1.5f);
        window->setView(view);
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
        view.zoom(1.f/1.5f);
        window->setView(view);
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O){
        cameraMode = 0;
        view = window->getDefaultView();
        view.zoom(earth->getRadius()/200.f);
        window->setView(view);
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
        cameraMode = 1;
        view = window->getDefaultView();
        window->setView(view);
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1){
        timespeed = 1.f;
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2){
        timespeed = 10.f;
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3){
        timespeed = 100.f;
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4){
        timespeed = 1000.f;
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5){
        timespeed = 10000.f;
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6){
        timespeed = 100000.f;
    }
   
}

void SpaceState::draw(){
    window->setView(view);

    window->draw(traj);
    if (cameraMode == 0)
        window->draw(mark);

    for (auto const &i : planets)
        window->draw(*i);
    window->draw(*spaceship);


    window->setView(window->getDefaultView());

    auto myStream = stream_of_file("media/FiraSans-Light.otf");
    myFont.loadFromStream(myStream);
    text.setFont(myFont);
    


    window->draw(text);
}


