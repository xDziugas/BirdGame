//
// Created by dziug on 6/24/2024.
//

#include "Bird.h"

#include <iostream>
#include <string.h>

Bird::Bird(const std::string& texture_file) : velocity(0), gravity(1000.0f), jump_strength(-350.0f) {
    init(texture_file);
}

void Bird::init(const std::string& texture_file) {
    if (!bird_texture.loadFromFile(texture_file)) {
        std::cerr << "Failed to load image \"" << texture_file << "\". Reason: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    bird_sprite.setTexture(bird_texture);
    bird_sprite.setPosition(100, 300);  // Initial position
}

void Bird::update(float dt) {
    jump_cooldown_timer -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump_cooldown_timer <= 0.0f) {
        velocity = jump_strength;
        jump_cooldown_timer = jump_cooldown;
    }
    velocity += gravity * dt;
    bird_sprite.move(0, velocity * dt);
}

void Bird::render(sf::RenderWindow& window) {
    window.draw(bird_sprite);
}