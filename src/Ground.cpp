//
// Created by dziug on 6/24/2024.
//

#include "../include/Ground.h"

Ground::Ground(const std::string& texture_file, float speed, float width, float height, float y) : speed(speed) {
    if (!ground_texture.loadFromFile(texture_file)) {
        // Handle error
    }
    ground_texture.setRepeated(true);
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);

    ground_sprite1.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height) + 12));
    ground_sprite2.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height) + 12));

    ground_sprite1.setScale(
        (width) / static_cast<float>(ground_texture.getSize().x),
        (height) / static_cast<float>(ground_texture.getSize().y)
    );
    ground_sprite2.setScale(
        (width) / static_cast<float>(ground_texture.getSize().x),
        (height) / static_cast<float>(ground_texture.getSize().y)
    );

    ground_sprite1.setPosition(0, y);
    ground_sprite2.setPosition(width, y);
}

void Ground::update(float dt) {
    float movement = speed * dt;
    ground_sprite1.move(-movement, 0);
    ground_sprite2.move(-movement, 0);

    if (ground_sprite1.getPosition().x + ground_sprite1.getGlobalBounds().width < 0) {
        ground_sprite1.setPosition(ground_sprite2.getPosition().x + ground_sprite2.getGlobalBounds().width, ground_sprite1.getPosition().y);
    }
    if (ground_sprite2.getPosition().x + ground_sprite2.getGlobalBounds().width < 0) {
        ground_sprite2.setPosition(ground_sprite1.getPosition().x + ground_sprite1.getGlobalBounds().width, ground_sprite2.getPosition().y);
    }
}

void Ground::render(sf::RenderWindow& window) {
    window.draw(ground_sprite1);
    window.draw(ground_sprite2);
}

float Ground::getGroundHeight() const {
    return ground_sprite1.getGlobalBounds().height;
}
