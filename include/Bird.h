//
// Created by dziug on 6/24/2024.
//

#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird {
public:
    explicit Bird(const std::string& texture_file);
    void update(float dt);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset();

private:
    sf::Texture bird_texture;
    sf::Sprite bird_sprite;
    float velocity;
    float gravity;
    float jump_strength;
    float jump_cooldown;
    float jump_cooldown_timer;

    void init(const std::string& texture_file);
};

#endif //BIRD_H
