class Game;

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ship.h"

#define PI 3.14159265358979323846

class Game{
public:
    sf::Vector2i dMouse;
    std::vector<Ship*> ships;

    void sendEvent(sf::RenderWindow* window, sf::Event& ev);

    void draw(sf::RenderWindow* window) const;
    void update(sf::RenderWindow* window);
};

#endif // GAME_H
