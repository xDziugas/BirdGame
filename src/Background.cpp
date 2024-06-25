//
// Created by dziug on 6/24/2024.
//

#include "../include/Background.h"

Background::Background(const std::string& texture_file, float speed) : speed(speed) {
    if(!background_texture.loadFromFile(texture_file)) {
        // Handle Error
    }
    background_texture.setRepeated(true);
    background_sprite1.setTexture(background_texture);
    background_sprite2.setTexture(background_texture);

    // Resize the background
    float window_width = 800.0f; // window width -> todo: get window width from window object
    float window_height = 600.0f; // window height -> todo: get window height from window object

    background_sprite1.setTextureRect(sf::IntRect(0, 0, window_width, window_height));
    background_sprite2.setTextureRect(sf::IntRect(0, 0, window_width, window_height));

    background_sprite2.setPosition(window_width, 0);
}

void Background::update(float dt) {
    float movement = speed * dt;
    background_sprite1.move(-movement, 0);
    background_sprite2.move(-movement, 0);

    if(background_sprite1.getPosition().x + background_sprite1.getGlobalBounds().width < 0) {
        background_sprite1.setPosition(background_sprite2.getPosition().x + background_sprite2.getGlobalBounds().width, 0);
    }
    if(background_sprite2.getPosition().x + background_sprite2.getGlobalBounds().width < 0) {
        background_sprite2.setPosition(background_sprite1.getPosition().x + background_sprite1.getGlobalBounds().width, 0);
    }
}

void Background::render(sf::RenderWindow &window) {
    window.draw(background_sprite1);
    window.draw(background_sprite2);
}

