#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "../Ship.h"

class EnemyShip : public Ship{
public:
    EnemyShip(float x, float y);

    virtual void sendEvent(Game* game, sf::RenderWindow* window, sf::Event& ev);

    virtual void draw(Game* game, sf::RenderWindow* window) const;
    virtual void update(Game* game, sf::RenderWindow* window);
};

#endif // ENEMYSHIP_H
