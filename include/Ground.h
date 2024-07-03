//
// Created by dziug on 6/24/2024.
//

#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

class Ground {
public:
  Ground(const std::string& texture_file, float speed, float width, float height, float y);
  void update(float dt);
  void render(sf::RenderWindow& window);
  float getGroundHeight() const;

private:
  sf::Texture ground_texture;
  sf::Sprite ground_sprite1;
  sf::Sprite ground_sprite2;
  float speed;
};

#endif //GROUND_H
