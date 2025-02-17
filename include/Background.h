//
// Created by dziug on 6/24/2024.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

#include "GameConfig.h"

class Background {
public:
    Background(const std::string& texture_file, float speed, const GameConfig::WindowConfig& config);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    void loadTexture(const std::string& texture_file);
    void setTextureRepeat(bool repeat);
    void initializeSprites();
    void scaleSprites(int width, int height);
    void setSpritePositions(int width);
    void moveSprites(float dt);
    void resetSpritePositions();

    sf::Texture background_texture;
    sf::Sprite background_sprite1;
    sf::Sprite background_sprite2;
    float speed;
    const GameConfig::WindowConfig& config;
};

#endif //BACKGROUND_H
