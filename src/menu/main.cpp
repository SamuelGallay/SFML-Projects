#include "MenuState.h"

int main() {
    auto engine = GameEngine::create();

    engine->buildState<MenuState>();
    engine->gameLoop();
    std::cout << "Back in Main\n";

    return 0;
}
