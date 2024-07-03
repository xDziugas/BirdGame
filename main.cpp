
#include <iostream>

#include "Game.h"
#include "GameConfig.h"

int main() {
    GameConfig config;
    if(!config.loadFromFile("config.json")) {
        std::cerr << "Failed to load configuration file" << std::endl;
        return EXIT_FAILURE;
    }

    Game game(config);
    game.run();
    return 0;
}
