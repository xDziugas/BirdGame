//
// Created by dziug on 6/24/2024.
//

#include "../include/Background.h"

#include "GameConfig.h"

Background::Background(const std::string& texture_file, float speed, const GameConfig::WindowConfig& config) : speed(speed), config(config) {
    if(!background_texture.loadFromFile(texture_file)) {
        // Handle Error
    }
    background_texture.setRepeated(true);
    background_sprite1.setTexture(background_texture);
    background_sprite2.setTexture(background_texture);

    // Resize the background
    background_sprite1.setScale(
        static_cast<float>(config.width) / background_texture.getSize().x,
        static_cast<float>(config.height) / background_texture.getSize().y
    );
    background_sprite2.setScale(
        static_cast<float>(config.width) / background_texture.getSize().x,
        static_cast<float>(config.height) / background_texture.getSize().y
    );

    background_sprite2.setPosition(config.width, 0);
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

