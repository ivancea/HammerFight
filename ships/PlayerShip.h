#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "../Ship.h"

class PlayerShip : public Ship{

    PlayerShip();

    /// Testing: To Ship class after tested
    sf::Vector2f _weaponPosition,
                 _weaponVelocity;
    float _weaponMaxDistance;
    float _weaponRadius;

public:

    virtual void sendEvent(Game* game, sf::RenderWindow* window, sf::Event& ev);

    virtual void draw(Game* game, sf::RenderWindow* window) const;
    virtual void update(Game* game, sf::RenderWindow* window);

    static PlayerShip& getPlayerShip();


};

#endif // PLAYERSHIP_H
