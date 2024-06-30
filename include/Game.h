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

enum GameState { StartScreen, Playing, GameOver };

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void resetGame();
    void handleInput();

    sf::RenderWindow window;
    GameState gameState;

    Bird bird;
    Background background;
    Ground ground;
    std::vector<Pipe> pipes;

    sf::Clock clock;
    sf::Clock pipeSpawnClock;
    float pipeSpawnInterval;

    int score;
    sf::Font font;
    sf::Text scoreText;

    sf::Texture startScreenTexture;
    sf::Texture gameOverTexture;
    sf::Sprite startScreenSprite;
    sf::Sprite gameOverSprite;
};

#endif //GAME_H
