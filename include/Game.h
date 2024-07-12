//
// Created by dziug on 6/30/2024.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bird.h"
#include "Background.h"
#include "GameConfig.h"
#include "Ground.h"
#include "Pipe.h"
#include "State.h"
#include "InputHandler.h"
#include "HighScoreManager.h"

class Game {
public:
    explicit Game(const GameConfig& config);
    void run();

private:
    void initializeWindow();
    void initializeAssets();
    void initializeText(sf::Text& text, const std::string& message, const sf::Vector2f& position, const sf::Color& color, int size) const;
    void updateFPS(sf::Clock& fpsClock, int& frameCount);
    GameConfig config;
    void handleEvent(sf::Event& event);
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handlePipeSpawning();
    void updatePipes(float dt);
    void incrementScore();
    void removeOffScreenPipes();
    void resetGame();
    void spawnPipe();
    void checkCollisions();
    void renderCommonElements();
    void renderStartScreen();
    void renderPauseScreen();
    void renderSettingsScreen();
    void renderGameOverScreen();
    void renderPlayingScreen();
    void renderHighScores();
    void updateHighScores();
    bool checkBirdPipeCollisions() const;
    bool checkBirdGroundCollision() const;
    bool checkBirdSkyCollision() const;

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
    sf::Text fpsText;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    InputHandler inputHandler;
    HighScoreManager highScoreManager;
};

#endif //GAME_H
