#include "SpaceState.hpp"
#include "GameEngine.h"

int main() {
    auto engine = GameEngine::create();

    engine->buildState<SpaceState>();
    engine->gameLoop();

    return 0;
}
