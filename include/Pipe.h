//
// Created by dziug on 6/27/2024.
//

#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Pipe {
public:
    Pipe(float speed);
    void spawnPipe(float x, float screenHeight);
    void update(float dt);
    void render(sf::RenderWindow& window);
    bool isOffScreen() const;
    std::vector<sf::FloatRect> getBounds() const;

    static bool loadTexture(const std::string& texture_file);

private:
    static sf::Texture pipe_texture;
    sf::Sprite pipe_top;
    sf::Sprite pipe_bottom;
    float speed;
    float gap;

    void initSprites();
};

#endif //PIPE_H
