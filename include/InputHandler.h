//
// Created by dziug on 7/1/2024.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

#include "Pipe.h"
#include "State.h"
#include <functional>

class InputHandler {
public:
    void handleInput(sf::Event& event, State& gameState, sf::Clock& clock, sf::Clock& pipeSpawnClock, bool& isPaused,
                     sf::Time& pauseTime, sf::Time& totalPauseTime, std::vector<Pipe>& pipes, int& score,
                     const std::function<void()>& resetGameCallback, const GameConfig::KeyBinds& keyBinds);  // Add this parameter
};

#endif //INPUTHANDLER_H
