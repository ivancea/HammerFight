#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

bool getCollision(sf::Vector2f item1, float radius1, sf::Vector2f velocity,
                  sf::Vector2f item2, float radius2, sf::Vector2f* point = nullptr);

#endif // UTILS_H
