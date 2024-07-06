//
// Created by dziug on 6/24/2024.
//

#include "../include/Background.h"

#include "GameConfig.h"

Background::Background(const std::string& texture_file, float speed, const GameConfig::WindowConfig& config)
    : speed(speed), config(config) {
    loadTexture(texture_file);
    setTextureRepeat(true);
    initializeSprites();
    scaleSprites(config.width, config.height);
    setSpritePositions(config.width);
}

void Background::loadTexture(const std::string& texture_file) {
    if (!background_texture.loadFromFile(texture_file)) {
        throw std::runtime_error("Failed to load background texture");
    }
}

void Background::setTextureRepeat(bool repeat) {
    background_texture.setRepeated(repeat);
}

void Background::initializeSprites() {
    background_sprite1.setTexture(background_texture);
    background_sprite2.setTexture(background_texture);
}

void Background::scaleSprites(int width, int height) {
    float scaleX = static_cast<float>(width) / static_cast<float>(background_texture.getSize().x);
    float scaleY = static_cast<float>(height) / static_cast<float>(background_texture.getSize().y);
    background_sprite1.setScale(scaleX, scaleY);
    background_sprite2.setScale(scaleX, scaleY);
}

void Background::setSpritePositions(int width) {
    background_sprite2.setPosition(static_cast<float>(width), 0);
}

void Background::update(float dt) {
    moveSprites(dt);
    resetSpritePositions();
}

void Background::moveSprites(float dt) {
    float movement = speed * dt;
    background_sprite1.move(-movement, 0);
    background_sprite2.move(-movement, 0);
}

void Background::resetSpritePositions() {
    if (background_sprite1.getPosition().x + background_sprite1.getGlobalBounds().width < 0) {
        background_sprite1.setPosition(background_sprite2.getPosition().x + background_sprite2.getGlobalBounds().width, 0);
    }
    if (background_sprite2.getPosition().x + background_sprite2.getGlobalBounds().width < 0) {
        background_sprite2.setPosition(background_sprite1.getPosition().x + background_sprite1.getGlobalBounds().width, 0);
    }
}


void Background::render(sf::RenderWindow &window) {
    window.draw(background_sprite1);
    window.draw(background_sprite2);
}

