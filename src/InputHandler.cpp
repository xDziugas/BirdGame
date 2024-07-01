//
// Created by dziug on 7/1/2024.
//

#include "../include/InputHandler.h"
#include "Game.h"

void InputHandler::handleInput(sf::Event& event, State& gameState, sf::Clock& clock, sf::Clock& pipeSpawnClock, bool& isPaused,
                               sf::Time& pauseTime, sf::Time& totalPauseTime, std::vector<Pipe>& pipes, int& score,
                               const std::function<void()>& resetGameCallback) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            if (gameState.get() == StartScreen) {
                gameState.set(Playing);
                clock.restart();
                pipeSpawnClock.restart();
                pipes.clear();
                score = 0;
            } else if (gameState.get() == GameOver) {
                resetGameCallback();
            } else if (gameState.get() == Pause) {
                gameState.set(Playing);
                totalPauseTime += clock.getElapsedTime() - pauseTime;
                clock.restart();
            } else if (gameState.get() == Settings) {
                gameState.set(StartScreen);
            }
        } else if (event.key.code == sf::Keyboard::P) {
            if (gameState.get() == Playing) {
                gameState.set(Pause);
                pauseTime = clock.getElapsedTime();
            } else if (gameState.get() == Pause) {
                gameState.set(Playing);
                totalPauseTime += clock.getElapsedTime() - pauseTime;
                clock.restart();
            }
        } else if (event.key.code == sf::Keyboard::S && gameState.get() != Playing && gameState.get() != Pause) {
            gameState.set(Settings);
        }
    }
}