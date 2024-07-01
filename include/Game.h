//
// Created by dziug on 6/30/2024.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bird.h"
#include "Background.h"
#include "Ground.h"
#include "Pipe.h"
#include "State.h"
#include "InputHandler.h"
#include "HighScoreManager.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    void resetGame();
    void spawnPipe();
    void checkCollisions();

    sf::RenderWindow window;
    State gameState;
    Bird bird;
    Background background;
    Ground ground;
    std::vector<Pipe> pipes;
    sf::Clock clock;
    sf::Clock pipeSpawnClock;
    sf::Time pauseTime;
    sf::Time totalPauseTime;
    float pipeSpawnInterval;
    int score;
    bool isPaused;
    sf::Font font;
    sf::Text scoreText;
    sf::Text startMessageText;
    sf::Text pauseMessageText;
    sf::Text settingsMessageText;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    InputHandler inputHandler;
    HighScoreManager highScoreManager;
};

#endif //GAME_H
