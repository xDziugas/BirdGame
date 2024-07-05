//
// Created by dziug on 6/30/2024.
//

#include "../include/Game.h"
#include <sstream>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include "State.h"

Game::Game(const GameConfig &config)
    : window(sf::VideoMode(config.window.width, config.window.height), config.window.title),
    config(config),
    gameState(State(StartScreen)),
    bird(config.bird, config.keyBinds),
    background(config.background.texture,config.background.scroll_speed, config.window),
    ground(config.ground.texture, config.ground.scroll_speed, static_cast<float>(config.window.width), config.ground.height, static_cast<float>(config.window.height) - config.ground.height),
    pipeSpawnInterval(config.pipe.spawn_interval), score(0),
    isPaused(false),
    highScoreManager("highscores.txt") {

    window.setFramerateLimit(config.frameRate.fps); // Cap the frame rate to 60 FPS

    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    if (!Pipe::loadTexture(config.pipe.texture)) {
        exit(EXIT_FAILURE);
    }

    gameOverTexture.loadFromFile(config.gameSettings.gameOverTexture);
    gameOverSprite.setTexture(gameOverTexture);

    if (!font.loadFromFile(config.gameSettings.font.file)) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(config.frameRate.size);
    fpsText.setFillColor(config.frameRate.color);
    fpsText.setPosition(config.frameRate.position);

    scoreText.setFont(font);
    scoreText.setCharacterSize(config.gameSettings.scoreMessage.size);
    scoreText.setFillColor(config.gameSettings.scoreMessage.color);
    scoreText.setPosition(config.gameSettings.scoreMessage.position);

    startMessageText.setFont(font);
    startMessageText.setCharacterSize(config.gameSettings.startMessage.size);
    startMessageText.setFillColor(config.gameSettings.startMessage.color);
    startMessageText.setString(config.gameSettings.startMessage.text);

    sf::FloatRect textRect = startMessageText.getLocalBounds();
    startMessageText.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
    startMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f);

    pauseMessageText.setFont(font);
    pauseMessageText.setCharacterSize(config.gameSettings.pauseMessage.size);
    pauseMessageText.setFillColor(config.gameSettings.pauseMessage.color);
    pauseMessageText.setString(config.gameSettings.pauseMessage.text);

    sf::FloatRect pauseTextRect = pauseMessageText.getLocalBounds();
    pauseMessageText.setOrigin(pauseTextRect.left + pauseTextRect.width / 2.0f,
                               pauseTextRect.top + pauseTextRect.height / 2.0f);
    pauseMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f);

    settingsMessageText.setFont(font);
    settingsMessageText.setCharacterSize(config.gameSettings.settingsMessage.size);
    settingsMessageText.setFillColor(config.gameSettings.settingsMessage.color);
    settingsMessageText.setString(config.gameSettings.settingsMessage.text);

    sf::FloatRect settingsTextRect = settingsMessageText.getLocalBounds();
    settingsMessageText.setOrigin(settingsTextRect.left + settingsTextRect.width / 2.0f,
                                  settingsTextRect.top + settingsTextRect.height / 2.0f);
    settingsMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150.0f);

    highScoreManager.loadHighScores(); // Load high scores when the game starts

}

void Game::run() {
    sf::Clock fpsClock;
    int frameCount = 0;

    while (window.isOpen()) {
        processEvents();
        if (gameState.get() == Playing && !isPaused) {
            update(clock.restart());
        }

        // Update FPS every second
        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            fpsText.setString("FPS " + std::to_string(frameCount));
            frameCount = 0;
            fpsClock.restart();
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        inputHandler.handleInput(event, gameState, clock, pipeSpawnClock, isPaused, pauseTime, totalPauseTime, pipes, score, [this]() { resetGame(); }, config.keyBinds);
    }
}


void Game::update(sf::Time dt) {
    bird.update(dt.asSeconds());
    background.update(dt.asSeconds());
    ground.update(dt.asSeconds());

    // Spawn new pipes at intervals
    if ((pipeSpawnClock.getElapsedTime() - totalPauseTime).asSeconds() >= pipeSpawnInterval) {
        spawnPipe();
        totalPauseTime = sf::Time::Zero;  // Reset total pause time after spawning a pipe
    }

    // Update pipes
    for (auto &pipe : pipes) {
        pipe.update(dt.asSeconds());
    }

    // Increment score when bird passes a pipe
    for (auto &pipe : pipes) {
        if (!pipe.isPassed() && pipe.getPosition().x < bird.getPosition().x) {
            pipe.markAsPassed();
            score++;
        }
    }

    // Remove pipes that are off screen
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe &pipe) {
        return pipe.isOffScreen();
    }), pipes.end());

    checkCollisions();
}

void Game::render() {
    window.clear();

    if (gameState.get() == StartScreen) {
        // Draw game elements without updating
        background.render(window);
        for (auto &pipe : pipes) {
            pipe.render(window);
        }
        ground.render(window);
        bird.render(window);

        // Draw start message
        window.draw(startMessageText);
    } else if (gameState.get() == Pause) {
        // Draw game elements without updating
        background.render(window);
        for (auto &pipe : pipes) {
            pipe.render(window);
        }
        ground.render(window);
        bird.render(window);

        // Draw pause message
        window.draw(pauseMessageText);
    } else if (gameState.get() == Settings) {
        // Draw settings message
        window.draw(settingsMessageText);
    } else if (gameState.get() == GameOver) {
        window.draw(gameOverSprite);

        std::stringstream ss;
        ss << "Score! " << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(
            config.gameSettings.scoreMessage.position.x - scoreText.getLocalBounds().width / 2.0f,
            config.gameSettings.scoreMessage.position.y
        );

        window.draw(scoreText);

        // Display high scores
        float yOffset = 100;
        for (size_t i = 0; i < highScoreManager.getHighScores().size(); ++i) {
            sf::Text highScoreText;
            highScoreText.setFont(font);
            highScoreText.setCharacterSize(30);
            highScoreText.setFillColor(sf::Color::White);
            highScoreText.setPosition(window.getSize().x / 2 -100, yOffset + i * 40);

            // Format the high score with four digits
            std::stringstream hs_ss;
            hs_ss << std::setw(5) << std::setfill('0') << highScoreManager.getHighScores()[i];
            highScoreText.setString(std::to_string(i + 1) + "! " + hs_ss.str());

            window.draw(highScoreText);
        }
    } else {
        background.render(window); // Render the background

        // Render pipes
        for (auto &pipe : pipes) {
            pipe.render(window);
        }

        ground.render(window); // Render the ground
        bird.render(window);   // Render the bird

        std::stringstream ss;
        ss << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(config.gameSettings.scoreMessage.position.x,
                             config.gameSettings.scoreMessage.position.y);
        window.draw(scoreText);
    }

    window.draw(fpsText);

    window.display();
}

void Game::resetGame() {
    bird.reset();
    highScoreManager.updateHighScores(score);
    gameState.set(StartScreen);
}

void Game::spawnPipe() {
    pipes.emplace_back(config.pipe);
    pipes.back().spawnPipe(window.getSize().x, window.getSize().y, ground.getGroundHeight(), config.pipe.minPipeHeightMultiplier, config.pipe.maxPipeHeightMultiplier);
    pipeSpawnClock.restart();
}

void Game::checkCollisions() {
    sf::FloatRect birdBounds = bird.getBounds();
    for (const auto &pipe : pipes) {
        for (const auto &bounds : pipe.getBounds()) {
            if (birdBounds.intersects(bounds)) {
                gameState.set(GameOver);
            }
        }
    }

    // Check for collision with the ground
    if (birdBounds.top + birdBounds.height >= window.getSize().y - ground.getGroundHeight()) {
        gameState.set(GameOver);
    }
}

