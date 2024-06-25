//
// Created by dziug on 6/24/2024.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
public:
    Background(const std::string& texture_file, float speed);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    sf::Texture background_texture;
    sf::Sprite background_sprite1;
    sf::Sprite background_sprite2;
    float speed;
};

#endif //BACKGROUND_H
