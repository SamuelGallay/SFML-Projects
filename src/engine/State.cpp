#include "State.h"
#include "GameEngine.h"

void State::build(
        const std::shared_ptr<GameEngine>       &engine,
        const std::shared_ptr<sf::RenderWindow> &window,
        const std::shared_ptr<Holder>           &holder) {
    stateEngine = engine;
    State::window = window;
    State::holder = holder;
}
