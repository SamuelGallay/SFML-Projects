#include "engine.h"


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

void State::onResize(){

}

//---------------------------------------------------------------------//
// GameEngine
//---------------------------------------------------------------------//
void GameEngine::popState(){
    states.pop_back();
    if (!states.empty())
        currentState()->onResize();
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

        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Resized){
                currentState()->onResize();
            } else {
                currentState()->handleEvent(event);
                if (currentState() == nullptr){
                    std::cout << "End of game loop." << std::endl;
                    return;
                }
            }
        }

        currentState()->update(elapsed);

        window->clear();
        currentState()->draw();
        window->display();
    }
}
