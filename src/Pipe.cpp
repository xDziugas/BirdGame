//
// Created by dziug on 6/27/2024.
//

#include "../include/Pipe.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

sf::Texture Pipe::pipe_texture;

Pipe::Pipe(float speed) : speed(speed), gap(150.0f) {
    initSprites();
}

bool Pipe::loadTexture(const std::string& texture_file) {
    if (!pipe_texture.loadFromFile(texture_file)) {
        std::cerr << "Failed to load image \"" << texture_file << "\". Reason: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

void Pipe::initSprites() {
    pipe_top.setTexture(pipe_texture);
    pipe_bottom.setTexture(pipe_texture);
    pipe_bottom.setRotation(180); // Rotate bottom pipe
}

void Pipe::spawnPipe(float x, float screenHeight, float groundHeight) {
    float min_height = 0.3f * screenHeight;
    float max_height = 0.7f * screenHeight + gap - groundHeight;

    // Generate a random height for the top pipe within the specified bounds
    float top_pipe_end = min_height + rand() % static_cast<int>(max_height - min_height);

    // Set the position of the top pipe
    pipe_top.setPosition(x, top_pipe_end);

    // Set the position of the bottom pipe
    pipe_bottom.setPosition(x + pipe_bottom.getGlobalBounds().width, top_pipe_end - gap);
}

void Pipe::update(float dt) {
    float movement = speed * dt;
    pipe_top.move(-movement, 0);
    pipe_bottom.move(-movement, 0);
}

void Pipe::render(sf::RenderWindow& window) {
    window.draw(pipe_top);
    window.draw(pipe_bottom);
}

bool Pipe::isOffScreen() const {
    return pipe_top.getPosition().x + pipe_top.getGlobalBounds().width < 0;
}

std::vector<sf::FloatRect> Pipe::getBounds() const {
    return { pipe_top.getGlobalBounds(), pipe_bottom.getGlobalBounds() };
}

bool Pipe::isPassed() const {
    return passed;
}

void Pipe::markAsPassed() {
    passed = true;
}

sf::Vector2f Pipe::getPosition() const {
    return pipe_top.getPosition() + sf::Vector2f(pipe_top.getGlobalBounds().width, 0);
}

