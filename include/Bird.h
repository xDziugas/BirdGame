//
// Created by dziug on 6/24/2024.
//

#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

#include "GameConfig.h"

class Bird {
public:
    explicit Bird(const GameConfig::BirdConfig& config);
    void update(float dt);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();
    sf::Vector2f getPosition() const;

private:
    sf::Texture bird_texture;
    sf::Sprite bird_sprite;
    float velocity;
    float gravity;
    float jump_strength;
    float jump_cooldown;
    float jump_cooldown_timer;
    const GameConfig::BirdConfig& config;

    void init(const std::string& texture_file);
};

#endif //BIRD_H
