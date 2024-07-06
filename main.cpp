
#include <iostream>

#include "Game.h"
#include "GameConfig.h"

int main() {
    GameConfig config;
    if (!config.loadFromFile("config.json")) {
        std::cerr << "Failed to load configuration file" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        Game game(config);
        game.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

