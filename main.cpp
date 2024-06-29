#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <ctime>

#include "Bird.h"
#include "Background.h"
#include "Ground.h"
#include "Pipe.h"

enum GameState { StartScreen, Playing, GameOver };

int main() {

    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    if (!std::filesystem::exists("assets/default_bird.png")) {
        std::cerr << "File not found: assets/default_bird.png" << std::endl;
        return EXIT_FAILURE;
    }
    if (!std::filesystem::exists("assets/background.png")) {
        std::cerr << "File not found: assets/background.png" << std::endl;
        return EXIT_FAILURE;
    }
    if (!std::filesystem::exists("assets/ground.png")) {
        std::cerr << "File not found: assets/ground.png" << std::endl;
        return EXIT_FAILURE;
    }

    if (!std::filesystem::exists("assets/pipe-green.png")) {
        std::cerr << "File not found: assets/pipe-green.png" << std::endl;
        return EXIT_FAILURE;
    }

    if (!Pipe::loadTexture("assets/pipe-green.png")) {
        return EXIT_FAILURE;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird Clone");
    window.setFramerateLimit(60); // Cap the frame rate to 60 FPS

    sf::Texture startScreenTexture, gameOverTexture;
    startScreenTexture.loadFromFile("assets/start-screen.png");
    gameOverTexture.loadFromFile("assets/gameover-message.png");
    sf::Sprite startScreenSprite(startScreenTexture);
    sf::Sprite gameOverSprite(gameOverTexture);

    GameState gameState = StartScreen;

    Bird bird("assets/default_bird.png");
    Background background("assets/background.png", 100.0f); // Adjust speed as needed
    Ground ground("assets/ground.png", 200.0f); // Adjust speed as needed

    std::vector<Pipe> pipes;
    pipes.emplace_back(200.0f);
    pipes.back().spawnPipe(window.getSize().x, window.getSize().y, ground.getGroundHeight());

    sf::Clock clock;
    sf::Clock fpsClock;
    sf::Clock pipeSpawnClock;
    int frameCount = 0;
    float pipeSpawnInterval = 1.5f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (gameState == StartScreen) {
                    gameState = Playing;
                    clock.restart();
                    pipeSpawnClock.restart();
                    pipes.clear();
                } else if (gameState == GameOver) {
                    bird.reset();  // Reset bird position and state
                    gameState = StartScreen;
                }
            }
        }

        if (gameState == StartScreen) {
            window.clear();
            window.draw(startScreenSprite);
            window.display();
            continue;
        }

        if (gameState == GameOver) {
            window.clear();
            window.draw(gameOverSprite);
            window.display();
            continue;
        }

        float dt = clock.restart().asSeconds();
        frameCount++;

        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
                std::cout << "FPS: " << frameCount << std::endl;
                frameCount = 0;
                fpsClock.restart();
            }

            bird.update(dt);
            background.update(dt);
            ground.update(dt);

            // Spawn new pipes at intervals
            if (pipeSpawnClock.getElapsedTime().asSeconds() >= pipeSpawnInterval) {
                pipes.emplace_back(200.0f);
                pipes.back().spawnPipe(window.getSize().x, window.getSize().y, ground.getGroundHeight());
                pipeSpawnClock.restart();
            }

            // Update pipes
            for (auto& pipe : pipes) {
                pipe.update(dt);
            }

            // Remove pipes that are off screen
            pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) {
                return pipe.isOffScreen();
            }), pipes.end());

            // Check for collisions
            sf::FloatRect birdBounds = bird.getBounds();
            for (const auto& pipe : pipes) {
                for (const auto& bounds : pipe.getBounds()) {
                    if (birdBounds.intersects(bounds)) {
                        gameState = GameOver;
                    }
                }
            }

            // Check for collision with the ground
            if (birdBounds.top + birdBounds.height >= window.getSize().y - ground.getGroundHeight()) {
                gameState = GameOver;
            }

            window.clear(sf::Color::Black);
            background.render(window); // Render the background

            // Render pipes
            for (auto& pipe : pipes) {
                pipe.render(window);
            }

            ground.render(window); // Render the ground

            bird.render(window); // Render the bird

            window.display(); // Display the contents

    }


    return 0;
}
