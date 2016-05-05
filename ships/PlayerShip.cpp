#include "PlayerShip.h"

#include <cmath>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "utils.h"

PlayerShip::PlayerShip():_weaponMaxDistance(70),_weaponRadius(6){
    _gravity = 0.5;
}

PlayerShip& PlayerShip::getPlayerShip(){
    static PlayerShip _player;
    return _player;
}

void PlayerShip::sendEvent(Game* game, sf::RenderWindow* window, sf::Event& ev){
    switch(ev.type){
    case sf::Event::MouseMoved:
    {
        _velocity.x += 0.1*game->dMouse.x;
        _velocity.y += 0.1*game->dMouse.y;

        break;
    }
    default:
        break;
    }
}

void PlayerShip::draw(Game* game, sf::RenderWindow* window) const{
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(pos.x+sin(i)*_radius,
                       pos.y+cos(i)*_radius);
    glEnd();
    glColor3ub(100,100,100);
    glBegin(GL_LINES);
        glVertex2f(_weaponPosition.x,_weaponPosition.y);
        glVertex2f(pos.x,pos.y);
    glEnd();
    glBegin(GL_POLYGON);
        for(float i=0; i<PI*2.01; i+=PI/360)
            glVertex2i(_weaponPosition.x+sin(i)*_weaponRadius,
                       _weaponPosition.y+cos(i)*_weaponRadius);
    glEnd();
    /*sf::Vector2f p, v(-1,-1);
    for(int i=0; i<window->getSize().x; i+=1)
        for(int j=0; j<window->getSize().y; j+=1){
            p.x = i;
            p.y = j;
            glColor3ub(255,255,255);
            for(Ship* ship : game->ships){
                if(ship==this)
                    continue;
                if(getCollision(p, 4, v, ship->pos, 8, nullptr)){
                    glColor3ub(255,0,0);
                    break;
                }
            }
            glBegin(GL_LINES);
            glVertex2f(i,j);
            glVertex2f(i+1,j+1);
            glEnd();
        }*/
}

void PlayerShip::update(Game* game, sf::RenderWindow* window){
    //_velocity.y += _gravity;
    _weaponVelocity.y += _gravity;

    float sq = sqrt(_velocity.x*_velocity.x + _velocity.y*_velocity.y);
    if(sq>15){
        _velocity.x = 10*_velocity.x/sq;
        _velocity.y = 10*_velocity.y/sq;
    }

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

    _weaponPosition += _weaponVelocity;
    sf::Vector2f temp = _weaponPosition - pos;
    sq = sqrt(temp.x*temp.x + temp.y*temp.y);
    if(sq>_weaponMaxDistance){
        temp.x = temp.x*_weaponMaxDistance/sq;
        temp.y = temp.y*_weaponMaxDistance/sq;
        _weaponVelocity.x += (pos.x+temp.x-_weaponPosition.x);
        _weaponVelocity.y += (pos.y+temp.y-_weaponPosition.y);
        _weaponPosition = pos+temp;
    }

    /*for(Ship* ship : game->ships){
        if(ship==this)
            continue;
        sf::Vector2f t;
        if(getCollision(_weaponPosition, 5, _weaponVelocity, ship->pos, 10, &t)){
            _weaponPosition = t;
            _weaponVelocity.x = _weaponVelocity.y = 0;
            break;
        }
    }*/
    for(Ship* ship : game->ships){
        if(ship==this)
            continue;
        sf::Vector2f t = _weaponPosition-ship->pos;
        float totalRadius = ship->getRadius() + _weaponRadius;
        if(t.x*t.x+t.y*t.y < totalRadius*totalRadius){
            _weaponPosition -= _weaponVelocity;
            ship->addVelocity(sf::Vector2f(_weaponVelocity.x*_weaponRadius/totalRadius,_weaponVelocity.y*_weaponRadius/totalRadius));
            _weaponVelocity = sf::Vector2f(-_weaponVelocity.x*ship->getRadius()/totalRadius/2,-_weaponVelocity.y*ship->getRadius()/totalRadius/2);
            ship->setLife(ship->getLife()-sqrt(_weaponVelocity.x/2*_weaponVelocity.x/2
                                              +_weaponVelocity.y/2*_weaponVelocity.y/2));
            ship->setRadius(ship->getRadius()-sqrt(_weaponVelocity.x/2*_weaponVelocity.x/2
                                                  +_weaponVelocity.y/2*_weaponVelocity.y/2));
            setLife(getLife()+sqrt(_weaponVelocity.x/2*_weaponVelocity.x/2
                                  +_weaponVelocity.y/2*_weaponVelocity.y/2)/5);
            setRadius(getRadius()+sqrt(_weaponVelocity.x/2*_weaponVelocity.x/2
                                      +_weaponVelocity.y/2*_weaponVelocity.y/2)/5);
            break;
        }
    }

    _velocity.x *= 0.98;
    _velocity.y *= 0.98;
    _weaponVelocity.x *= 0.99;
    _weaponVelocity.y *= 0.99;
}
