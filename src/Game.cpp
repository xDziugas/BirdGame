//
// Created by dziug on 6/30/2024.
//

#include "../include/Game.h"
#include <sstream>
#include <iostream>
#include <filesystem>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(800, 600), "Flappy Bird Clone"), gameState(StartScreen), bird("assets/default_bird.png"),
      background("assets/background.png", 100.0f), ground("assets/ground.png", 200.0f), pipeSpawnInterval(1.5f), score(0) {

    window.setFramerateLimit(60); // Cap the frame rate to 60 FPS

    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    if (!std::filesystem::exists("assets/default_bird.png") ||
        !std::filesystem::exists("assets/background.png") ||
        !std::filesystem::exists("assets/ground.png") ||
        !std::filesystem::exists("assets/pipe-green.png") ||
        !std::filesystem::exists("assets/start-screen.png") ||
        !std::filesystem::exists("assets/gameover-message.png") ||
        !std::filesystem::exists("assets/arial.ttf")) {
        std::cerr << "One or more assets not found" << std::endl;
        exit(EXIT_FAILURE);
        }

    if (!Pipe::loadTexture("assets/pipe-green.png")) {
        exit(EXIT_FAILURE);
    }

    startScreenTexture.loadFromFile("assets/start-screen.png");
    gameOverTexture.loadFromFile("assets/gameover-message.png");
    startScreenSprite.setTexture(startScreenTexture);
    gameOverSprite.setTexture(gameOverTexture);

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100, 5);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (gameState == Playing) {
            update(clock.restart());
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            handleInput();
        }
    }
}

void Game::handleInput() {
    if (gameState == StartScreen) {
        gameState = Playing;
        clock.restart();
        pipeSpawnClock.restart();
        pipes.clear();
        score = 0;  // Reset score at the start of the game
    } else if (gameState == GameOver) {
        resetGame();
    }
}

void Game::update(sf::Time dt) {
    bird.update(dt.asSeconds());
    background.update(dt.asSeconds());
    ground.update(dt.asSeconds());

    // Spawn new pipes at intervals
    if (pipeSpawnClock.getElapsedTime().asSeconds() >= pipeSpawnInterval) {
        pipes.emplace_back(200.0f);
        pipes.back().spawnPipe(window.getSize().x, window.getSize().y, ground.getGroundHeight());
        pipeSpawnClock.restart();
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

    // Check for collisions
    sf::FloatRect birdBounds = bird.getBounds();
    for (const auto &pipe : pipes) {
        for (const auto &bounds : pipe.getBounds()) {
            if (birdBounds.intersects(bounds)) {
                gameState = GameOver;
            }
        }
    }

    // Check for collision with the ground
    if (birdBounds.top + birdBounds.height >= window.getSize().y - ground.getGroundHeight()) {
        gameState = GameOver;
    }
}

void Game::render() {
    window.clear();

    if (gameState == StartScreen) {
        window.draw(startScreenSprite);
    } else if (gameState == GameOver) {
        window.draw(gameOverSprite);
        std::stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(300, 20);  // Center the score on the screen
        window.draw(scoreText);
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
    gameState = StartScreen;
}