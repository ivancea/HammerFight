#include "Game.h"

#include <iostream>
#include <windows.h>
#include <SFML/OpenGL.hpp>

void Game::sendEvent(sf::RenderWindow* window, sf::Event& ev){
    switch(ev.type){
    case sf::Event::MouseMoved:
        if(ev.mouseMove.x==window->getSize().x/2 && ev.mouseMove.y==window->getSize().y/2)
            break;
        SetCursorPos(window->getPosition().x+window->getSize().x/2+3,
                     window->getPosition().y+window->getSize().y/2+26);
        dMouse.x = ev.mouseMove.x-window->getSize().x/2;
        dMouse.y = ev.mouseMove.y-window->getSize().y/2;
        break;
    default:
        break;
    }
    for(int i=0; i<ships.size(); i++)
        ships[i]->sendEvent(this, window, ev);
}

void Game::draw(sf::RenderWindow* window) const{
    for(int i=0; i<ships.size(); i++)
        ships[i]->draw((Game*)this, window);
}

void Game::update(sf::RenderWindow* window){
    for(int i=0; i<ships.size(); i++)
        ships[i]->update((Game*)this, window);
    for(int i=0; i<ships.size(); i++){
        if(ships[i]->getLife()<=0){
            delete ships[i];
            ships.erase(ships.begin()+i);
            --i;
        }
    }
}
