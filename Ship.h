class Ship;

#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

#include "Game.h"

class Ship{
protected:
    float _gravity;
    sf::Vector2f _velocity;

    float _life;
    float _radius;

public:
    sf::Vector2f pos;

    Ship(sf::Vector2f _pos = sf::Vector2f());
    Ship(float x, float y);
    virtual ~Ship();

    float getLife() const;
    float setLife(float life);

    float getRadius() const;
    void setRadius(float radius);

    virtual void sendEvent(Game* game, sf::RenderWindow* window, sf::Event& ev) = 0;

    virtual void draw(Game* game, sf::RenderWindow* window) const = 0;
    virtual void update(Game* game, sf::RenderWindow* window) = 0;

    virtual void addVelocity(sf::Vector2f v);

};

#endif // SHIP_H
