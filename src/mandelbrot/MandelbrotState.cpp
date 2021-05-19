#include "MandelbrotState.h"

#include "Mandelbrot.h"
#include "utilitary.hpp"

#include <string>
#include <chrono>
#include <iostream>
#include <cmath>
#include <memory>

void MandelbrotState::initialize() {
    window->setFramerateLimit(30);
    vitesse = 0.6;
    vitZoom = 2.0;
    flou = 1;

    rendu = std::make_shared<sf::Image>();
    onResize();

    gui = std::make_shared<GUI>(holder->font.get("FiraSans-Light.otf"));
}

void MandelbrotState::update(sf::Time){
    gui->setParameters(param);

    texture.loadFromImage(*rendu);

    sprite.setTexture(texture);

    oldParam = param;
}


void MandelbrotState::draw(){
    window->setView(sf::View(sf::FloatRect(0, 0, param.definition.x, param.definition.y)));
    window->draw(sprite);
    setStandardView(window);
    window->draw(*gui);
}

void MandelbrotState::runWorker() {
    std::cout << "Creating Thread\n";

    sf::Vector2<unsigned int> oldDefinition = param.definition;
    Parameters oldParam = param;

    running = true;

    while (running) {
        if (param != oldParam) {
            oldParam = param;
            if (param.definition != oldDefinition) {
                oldDefinition = param.definition;
                rendu->create(param.definition.x, param.definition.y, sf::Color::Black);
            }
            mandelbrot(rendu, param);
        } else {
            //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    std::cout << "Closing Thread\n";
}

void MandelbrotState::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed)
        window->close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
        running=false;
        if(worker.joinable())
            worker.join();
        stateEngine->popState();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        param.center.y -= vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        param.center.y += vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        param.center.x += vitesse / param.zoom;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        param.center.x -= vitesse / param.zoom;

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
        flou *= 2;
        param.definition.x = window->getSize().x / flou;
        param.definition.y = window->getSize().y / flou;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && flou > 1) {
        flou /= 2;
        param.definition.x = window->getSize().x / flou;
        param.definition.y = window->getSize().y / flou;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
        param.zoom *= vitZoom;
        param.iterMax = (int) (100 * std::log(param.zoom + 1));
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
        param.zoom /= vitZoom;
        param.iterMax = (int) (100 * std::log(param.zoom + 1));
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
        param.iterMax *= 1.1;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
        param.iterMax /= 1.1;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
        std::thread worker2(&MandelbrotState::wallpaper, this, param);
        worker2.detach();
    }
}

void MandelbrotState::onResize(){
    running=false;
    //if(worker.joinable())
    worker.join();
    //std::cout << "H1\n";
    rendu->create(window->getSize().x, window->getSize().y);
    param.definition.x = window->getSize().x / flou;
    param.definition.y = window->getSize().y / flou;
    worker = std::thread(&MandelbrotState::runWorker, this);
    worker.detach();
}

void MandelbrotState::wallpaper(Parameters c_param) {
    sf::Clock chrono;
    c_param.definition = sf::Vector2<unsigned int>(1920 * 2, 1200 * 2);
    auto temp = std::make_shared<sf::Image>();
    temp->create(1920 * 2, 1200 * 2);
    mandelbrot(temp, c_param);
    sf::Image poster;
    poster.create(1920, 1200);
    for (int y = 0; y < 1200; y++) {
        for (int x = 0; x < 1920; x++) {
            int r = 0, g = 0, b = 0;
            sf::Color c1 = temp->getPixel(x * 2, y * 2);
            sf::Color c2 = temp->getPixel(x * 2 + 1, y * 2);
            sf::Color c3 = temp->getPixel(x * 2, y * 2 + 1);
            sf::Color c4 = temp->getPixel(x * 2 + 1, y * 2 + 1);
            r = (c1.r + c2.r + c3.r + c4.r) / 4;
            g = (c1.g + c2.g + c3.g + c4.g) / 4;
            b = (c1.b + c2.b + c3.b + c4.b) / 4;
            poster.setPixel(x, y, sf::Color(r, g, b));
        }
    }
    poster.saveToFile(std::to_string(time(NULL)) + ".png");
    std::cout << "Wallpaper saved in : " << std::to_string(chrono.restart().asSeconds()) << "s\n";
}
