//
// Created by dziug on 6/24/2024.
//

#include "../include/Ground.h"

#include "Ground.h"

Ground::Ground(const std::string& texture_file, float speed) : speed(speed) {
    if (!ground_texture.loadFromFile(texture_file)) {
        // Handle error
    }
    ground_texture.setRepeated(true);
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);

    // Resize the ground to fit
    float window_width = 800.0f; // window width -> todo: get window width from window object
    float ground_height = 100.0f; // Adjust for the ground height -> todo: get ground height from texture or smth

    ground_sprite1.setTextureRect(sf::IntRect(0, 0, window_width, ground_height));
    ground_sprite2.setTextureRect(sf::IntRect(0, 0, window_width, ground_height));

    ground_sprite1.setPosition(0, 510); // Adjust the vertical position
    ground_sprite2.setPosition(window_width, 510);
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
