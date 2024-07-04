//
// Created by dziug on 6/27/2024.
//

#include "../include/Pipe.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "GameConfig.h"

sf::Texture Pipe::pipe_texture;

Pipe::Pipe(const GameConfig::PipeConfig& config) : speed(config.speed), gap(config.gap) {
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
    pipe_top.setRotation(180); // Rotate bottom pipe
}

void Pipe::spawnPipe(float x, float screenHeight, float groundHeight, float min, float max) {
    float min_height = min * screenHeight;
    float max_height = max * (screenHeight - groundHeight) - gap;

    // Generate a random height for the top pipe within the specified bounds
    float top_pipe_end = min_height + static_cast<float>(rand() % static_cast<int>(max_height - min_height));

    float top_pipe_height = top_pipe_end;
    float bottom_pipe_height = screenHeight - (top_pipe_end + gap + groundHeight);

    // Scale the pipes to fit the screen height
    float scale_factor_top = top_pipe_height / static_cast<float>(pipe_texture.getSize().y);
    float scale_factor_bottom = bottom_pipe_height / static_cast<float>(pipe_texture.getSize().y);

    if(scale_factor_top > 1.0f) {
        pipe_top.setScale(1.0f, scale_factor_top);
    }

    if(scale_factor_bottom > 1.0f) {
        pipe_bottom.setScale(1.0f, scale_factor_bottom);
    }

    pipe_top.setPosition(x + pipe_bottom.getGlobalBounds().width, top_pipe_end);
    pipe_bottom.setPosition(x, top_pipe_end + gap);
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

