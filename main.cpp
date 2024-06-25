#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "Bird.h"
#include "Background.h"
#include "Ground.h"

int main() {
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird Clone");
    window.setFramerateLimit(60); // Cap the frame rate to 60 FPS

    Bird bird("assets/default_bird.png");
    Background background("assets/background.png", 100.0f);
    Ground ground("assets/ground.png", 200.0f);

    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        frameCount++;

        // Print FPS every second
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            fpsClock.restart();
        }

        bird.update(dt);
        background.update(dt);
        ground.update(dt);

        window.clear(sf::Color::Black);
        background.render(window); // Render the background
        bird.render(window); // Render the bird
        ground.render(window); // Render the ground
        window.display(); // Display the contents
    }

    return 0;
}
