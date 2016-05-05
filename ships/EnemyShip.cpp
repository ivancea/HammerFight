#include "EnemyShip.h"

#include <iostream>
#include <SFML/OpenGL.hpp>

EnemyShip::EnemyShip(float x, float y):Ship(x,y){
    _gravity = 0.5;
    _radius = 20;
}

void EnemyShip::sendEvent(Game* game, sf::RenderWindow* window, sf::Event& ev){
    switch(ev.type){
    default:
        break;
    }
}

void EnemyShip::draw(Game* game, sf::RenderWindow* window) const{
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(pos.x+sin(i)*_radius,
                       pos.y+cos(i)*_radius);
    glEnd();
}

void EnemyShip::update(Game* game, sf::RenderWindow* window){
    float sq = sqrt(_velocity.x*_velocity.x + _velocity.y*_velocity.y);
    if(sq>10){
        _velocity.x = 10*_velocity.x/sq;
        _velocity.y = 10*_velocity.y/sq;
    }
    if(sq<=0.001)
        return ;

    sf::Vector2f nextPos = pos + _velocity;

    for(Ship* ship : game->ships){
        if(ship==this)
            continue;
        sf::Vector2f t = nextPos-ship->pos;
        float totalRadius = ship->getRadius() + _radius;
        if(t.x*t.x+t.y*t.y < totalRadius*totalRadius){
            nextPos = pos;
            ship->addVelocity(sf::Vector2f(_velocity.x*_radius/totalRadius,_velocity.y*_radius/totalRadius));
            _velocity = sf::Vector2f(-_velocity.x*ship->getRadius()/totalRadius/2,-_velocity.y*ship->getRadius()/totalRadius/2);
            ship->setLife(ship->getLife()-sqrt(_velocity.x/2*_velocity.x/2
                                              +_velocity.y/2*_velocity.y/2));
            setLife(getLife()-sqrt(_velocity.x/2*_velocity.x/2
                                  +_velocity.y/2*_velocity.y/2));
            setRadius(getRadius()-sqrt(_velocity.x/2*_velocity.x/2
                                      +_velocity.y/2*_velocity.y/2));
            ship->setRadius(ship->getRadius()-sqrt(_velocity.x/2*_velocity.x/2
                                                  +_velocity.y/2*_velocity.y/2));
            break;
        }
    }

    /// TODO: Check collisions

    pos = nextPos;

    if(pos.x<0){
        pos.x=0;
        _velocity.x = 0;
    }else if(pos.x>=window->getSize().x){
        pos.x=window->getSize().x-1;
        _velocity.x = 0;
    }
    if(pos.y<0){
        pos.y=0;
        _velocity.y = 0;
    }else if(pos.y>=window->getSize().y){
        pos.y=window->getSize().y-1;
        _velocity.y = 0;
    }

    _velocity.x *= 0.98;
    _velocity.y *= 0.98;
}
