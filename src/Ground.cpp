//
// Created by dziug on 6/24/2024.
//

#include "../include/Ground.h"

#include "Ground.h"

#include <iostream>

Ground::Ground(const std::string& texture_file, float speed, float width, float height, float y) : speed(speed) {
    if (!ground_texture.loadFromFile(texture_file)) {
        // Handle error
    }
    ground_texture.setRepeated(true);
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);

    ground_sprite1.setTextureRect(sf::IntRect(0, 0, width, height));
    ground_sprite2.setTextureRect(sf::IntRect(0, 0, width, height));

    ground_sprite1.setPosition(0, y); // Adjust the vertical position
    ground_sprite2.setPosition(width, y);
}

void Ground::update(float dt) {
    float movement = speed * dt;
    ground_sprite1.move(-movement, 0);
    ground_sprite2.move(-movement, 0);

    if (ground_sprite1.getPosition().x + ground_sprite1.getGlobalBounds().width < 0) {
        ground_sprite1.setPosition(ground_sprite2.getPosition().x + ground_sprite2.getGlobalBounds().width, 510);
    }
    if (ground_sprite2.getPosition().x + ground_sprite2.getGlobalBounds().width < 0) {
        ground_sprite2.setPosition(ground_sprite1.getPosition().x + ground_sprite1.getGlobalBounds().width, 510);
    }
}

void Ground::render(sf::RenderWindow& window) {
    window.draw(ground_sprite1);
    window.draw(ground_sprite2);
}

float Ground::getGroundHeight() const {
    return ground_sprite1.getGlobalBounds().height;
}
