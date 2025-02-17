//
// Created by dziug on 6/24/2024.
//

#include "Bird.h"

#include <iostream>
#include <string.h>
#include <cmath>

Bird::Bird(const GameConfig::BirdConfig& config, const GameConfig::KeyBinds& keyBinds) : velocity(0), gravity(config.gravity), jump_strength(config.jump_strength), jump_cooldown(config.jump_cooldown), jump_cooldown_timer(0.0f), config(config), keyBinds(keyBinds) {
    init(config.texture);
}

void Bird::init(const std::string& texture_file) {
    if (!bird_texture.loadFromFile(texture_file)) {
        std::cerr << "Failed to load image \"" << texture_file << "\". Reason: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    bird_sprite.setTexture(bird_texture);

    bird_sprite.setScale(
        config.width / static_cast<float>(bird_texture.getSize().x),
        config.height / static_cast<float>(bird_texture.getSize().y)
    );

    bird_sprite.setPosition(config.default_position);  // Initial position
}

void Bird::update(float dt) {
    jump_cooldown_timer -= dt;
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyBinds.jump)) && jump_cooldown_timer <= 0.0f) {
        velocity = jump_strength;
        jump_cooldown_timer = jump_cooldown;
    }
    velocity += gravity * dt;
    bird_sprite.move(0, velocity * dt);

    if(config.enableRotation) {
        setRotation();
    }
}

void Bird::reset() {
    bird_sprite.setPosition(config.default_position); // Set to starting position
    velocity = 0; // Reset velocity

    if(config.enableRotation) {
       setRotation();
    }
}

void Bird::render(sf::RenderWindow& window) {
    window.draw(bird_sprite);
}

sf::FloatRect Bird::getBounds() const {
    return bird_sprite.getGlobalBounds();
}

sf::Vector2f Bird::getPosition() const {
    return bird_sprite.getPosition();
}

void Bird::setRotation() {
    const float smallPositiveValue = -200.5f;
    const float maxAngle = 80.0f; // Maximum angle for rotation
    const float maxYSpeed = jump_strength; // Maximum Y speed (jump strength)

    float angle = 0.0f;

    if (velocity < smallPositiveValue) {
        angle = -20.0f;
    } else {
        float helpAngle = 90.0f * sin(-velocity * (M_PI / (2.0f * maxYSpeed)));
        angle += 0.3f * (helpAngle - angle);
    }

    // Clamp the angle to be within -maxAngle and maxAngle
    angle = std::clamp(angle, -maxAngle, maxAngle);

    bird_sprite.setRotation(angle);
}

