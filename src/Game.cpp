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

Game::Game()
    : window(sf::VideoMode(800, 600), "Flappy Bird Clone"), gameState(State(StartScreen)), bird("assets/default_bird.png"),
      background("assets/background.png", 100.0f), ground("assets/ground.png", 200.0f), pipeSpawnInterval(1.5f), score(0),
      highScoreManager("highscores.txt") {

    window.setFramerateLimit(60); // Cap the frame rate to 60 FPS

    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    if (!std::filesystem::exists("assets/default_bird.png") ||
        !std::filesystem::exists("assets/background.png") ||
        !std::filesystem::exists("assets/ground.png") ||
        !std::filesystem::exists("assets/pipe-green.png") ||
        !std::filesystem::exists("assets/gameover-message.png") ||
        !std::filesystem::exists("assets/arcade.ttf")) {
        std::cerr << "One or more assets not found" << std::endl;
        exit(EXIT_FAILURE);
        }

    if (!Pipe::loadTexture("assets/pipe-green.png")) {
        exit(EXIT_FAILURE);
    }

    gameOverTexture.loadFromFile("assets/gameover-message.png");
    gameOverSprite.setTexture(gameOverTexture);

    if (!font.loadFromFile("assets/arcade.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100, 5);

    startMessageText.setFont(font);
    startMessageText.setCharacterSize(50);
    startMessageText.setFillColor(sf::Color::White);
    startMessageText.setString("Press space to start!");

    sf::FloatRect textRect = startMessageText.getLocalBounds();
    startMessageText.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
    startMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f);

    pauseMessageText.setFont(font);
    pauseMessageText.setCharacterSize(50);
    pauseMessageText.setFillColor(sf::Color::White);
    pauseMessageText.setString("Press space to resume!");

    sf::FloatRect pauseTextRect = pauseMessageText.getLocalBounds();
    pauseMessageText.setOrigin(pauseTextRect.left + pauseTextRect.width / 2.0f,
                               pauseTextRect.top + pauseTextRect.height / 2.0f);
    pauseMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f);

    settingsMessageText.setFont(font);
    settingsMessageText.setCharacterSize(50);
    settingsMessageText.setFillColor(sf::Color::White);
    settingsMessageText.setString("Settings! Press space to go back");

    sf::FloatRect settingsTextRect = settingsMessageText.getLocalBounds();
    settingsMessageText.setOrigin(settingsTextRect.left + settingsTextRect.width / 2.0f,
                                  settingsTextRect.top + settingsTextRect.height / 2.0f);
    settingsMessageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150.0f);

    highScoreManager.loadHighScores(); // Load high scores when the game starts

}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (gameState.get() == Playing && !isPaused) {
            update(clock.restart());
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
        inputHandler.handleInput(event, gameState, clock, pipeSpawnClock, isPaused, pauseTime, totalPauseTime, pipes, score, [this]() { resetGame(); });
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
        scoreText.setPosition(300, 20);
        window.draw(scoreText);

        // Display high scores
        float yOffset = 100;
        for (size_t i = 0; i < highScoreManager.getHighScores().size(); ++i) {
            sf::Text highScoreText;
            highScoreText.setFont(font);
            highScoreText.setCharacterSize(30);
            highScoreText.setFillColor(sf::Color::White);
            highScoreText.setPosition(300, yOffset + i * 40);

            // Format the high score with four digits
            std::stringstream hs_ss;
            hs_ss << std::setw(4) << std::setfill('0') << highScoreManager.getHighScores()[i];
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
        scoreText.setPosition(400, 20);  // Position at the top of the screen
        window.draw(scoreText);
    }

    window.display();
}


void Game::resetGame() {
    bird.reset();
    highScoreManager.updateHighScores(score);
    gameState.set(StartScreen);
}



void Game::spawnPipe() {
    pipes.emplace_back(200.0f);
    pipes.back().spawnPipe(window.getSize().x, window.getSize().y, ground.getGroundHeight());
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

