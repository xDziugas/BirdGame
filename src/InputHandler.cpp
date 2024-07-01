//
// Created by dziug on 7/1/2024.
//

#include "../include/InputHandler.h"
#include "Game.h"

void InputHandler::handleInput(State& gameState, sf::Clock& clock, sf::Clock& pipeSpawnClock, bool& isPaused,
                               sf::Time& pauseTime, sf::Time& totalPauseTime, std::vector<Pipe>& pipes, int& score,
                               const std::function<void()>& resetGameCallback) {
    if (gameState.get() == StartScreen) {
        gameState.set(Playing);
        clock.restart();
        pipeSpawnClock.restart();
        pipes.clear();
        score = 0;  // Reset score at the start of the game
    } else if (gameState.get() == GameOver) {
        resetGameCallback();  // Use the callback to reset the game
    } else if (gameState.get() == Pause) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameState = Playing;
            totalPauseTime += clock.getElapsedTime() - pauseTime;  // Accumulate the total pause duration
            clock.restart();
        }
    } else if (gameState.get() == Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            gameState = Pause;
            pauseTime = clock.getElapsedTime();  // Record the time when the game was paused
        }
    } else if (gameState.get() == Settings) {
        gameState = StartScreen;
    }
}