#include "Ship.h"

Ship::Ship(float x, float y):pos(x,y),_life(10),_radius(10){
}

Ship::Ship(sf::Vector2f _pos):pos(_pos),_life(10),_radius(10){
}

Ship::~Ship(){}

void Ship::addVelocity(sf::Vector2f v){
    _velocity += v;
}

float Ship::getLife() const{
    return _life;
}

float Ship::setLife(float life){
    _life = life;
}

float Ship::getRadius() const{
    return _radius;
}

void Ship::setRadius(float radius){
    _radius = radius;
}
