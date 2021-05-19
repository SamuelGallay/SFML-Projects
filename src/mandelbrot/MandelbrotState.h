#ifndef MANDELBROT_STATE_H
#define MANDELBROT_STATE_H

#include <SFML/Graphics.hpp>

#include "Parameters.h"
#include "GUI.h"
#include "engine.h"
#include <memory>
#include <thread>

class MandelbrotState : public State
{
    public:
        void initialize();
        void update(sf::Time dt);
        void draw();
        void handleEvent(sf::Event event);
        void onResize();

    private:
        void runWorker();
        void wallpaper(Parameters c_param);
        std::shared_ptr<sf::Image> rendu;
        double vitesse;
        double vitZoom;
        int flou;
        sf::Texture texture;
        sf::Sprite sprite;
        Parameters oldParam;
        Parameters param;
        std::shared_ptr<GUI> gui;
        bool running;
        std::thread worker;
};

#endif
