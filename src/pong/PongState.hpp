#include <memory>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ParticleSystem.hpp"
#include "engine.h"

class PongState : public State
{
    public:
        void initialize();
        void update(sf::Time dt);
        void draw();
        void handleEvent(sf::Event event);
    
    private:
        //-- Les fonctions --//
        void restart();
        void processEvents();
        void paddlesInput(sf::Time deltaTime);
        void updateMessages();
    
        //-- Les constantes --//
        int tailleX;
        int tailleY;
        int tailleBordureRect;
        int rayon;
        int bordureBille;
        float pi;
    
        //-- Les variables --//
        bool enPause;
        float paddleSpeed;
        float vitesseBille;
        float angle;
        sf::Vector2f tailleRect;
        sf::Vector2i score;
    
        //-- Les Objets --//
        sf::View vue;
        sf::VertexArray fond;
        sf::Clock clock;
        std::unique_ptr<ParticleSystem> particles;
        sf::RectangleShape rectangle;
        sf::RectangleShape rectangle2;
        sf::CircleShape cercle;
        sf::Text messageBienvenue;
        sf::Text message2;
        sf::Text message3;
        sf::Text blue;
        sf::Text red;
        sf::Sound ballSound;
};
