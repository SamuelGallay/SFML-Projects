#include "engine.h"


//---------------------------------------------------------------------//
// ResourceHolder - Not Working Version
//---------------------------------------------------------------------//

/*
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(holder);

void stream_of_file(sf::MemoryInputStream &mystream, std::string path){
    auto fs = cmrc::holder::get_filesystem();

    auto fd = fs.open(path);

    int filesize = reinterpret_cast<uintptr_t>(fd.end()) - reinterpret_cast<uintptr_t>(fd.begin());

    mystream.open(fd.begin(), filesize);
}

template<>
bool ResourceHolder<std::unique_ptr<sf::Music>>::m_loadFromStream(std::unique_ptr<sf::Music> &elt, sf::MemoryInputStream &s){
    elt = std::make_unique<sf::Music>();
    return elt->openFromStream(s);
}
*/

//---------------------------------------------------------------------//
// ResourceHolder - Simple Working Version
//---------------------------------------------------------------------//
void stream_of_file(sf::FileInputStream &mystream, std::string path){
    mystream.open(path);
}

template<>
bool ResourceHolder<sf::Music>::m_loadFromStream(std::shared_ptr<sf::Music> elt, sf::FileInputStream &s){
    return elt->openFromStream(s);
}



//---------------------------------------------------------------------//
// State
//---------------------------------------------------------------------//
void State::build(
    const std::shared_ptr<GameEngine>       &engine,
    const std::shared_ptr<sf::RenderWindow> &window,
    const std::shared_ptr<Holder>           &holder) {
    stateEngine = engine;
    State::window = window;
    State::holder = holder;
}


//---------------------------------------------------------------------//
// GameEngine
//---------------------------------------------------------------------//
void GameEngine::popState(){
    states.pop_back();
}

std::shared_ptr<State> GameEngine::currentState(){
    if (states.empty())
        return nullptr;
    else
        return states.back();
}

void GameEngine::gameLoop(){
    sf::Clock clock;

    while (window->isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window->pollEvent(event)){
            currentState()->handleEvent(event);
            if (currentState() == nullptr){
                std::cout << "End of game loop." << std::endl;
                return;
            }
        }

        currentState()->update(elapsed);

        window->clear();
        currentState()->draw();
        window->display();
    }
}
