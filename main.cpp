#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bird.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird Clone");
    window.setFramerateLimit(60); // Cap the frame rate to 60 FPS

    Bird bird("assets/default_bird.png");

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

        window.clear(sf::Color::Black); // Ensure window is cleared
        bird.render(window); // Render the bird
        window.display(); // Display the contents
    }

    return 0;
}
