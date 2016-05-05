#include <iostream>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game.h"
#include "PlayerShip.h"
#include "EnemyShip.h"

using namespace std;

int main(){
    srand(time(0));

    bool running = true;
    sf::RenderWindow window;
    Game game;

    window.create(sf::VideoMode(500,500), "HammerFight", sf::Style::Close);
    window.setFramerateLimit(80);
    window.setMouseCursorVisible(false);

    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glOrtho(0,window.getSize().x, window.getSize().y,0,0,1);
    glMatrixMode(GL_PROJECTION);

    game.ships.push_back(&PlayerShip::getPlayerShip());
    for(int i=150; i<400; i+=50)
        for(int j=150; j<400; j+=50)
            game.ships.push_back(new EnemyShip(i,j));

    while(running){
        sf::Event ev;
        while(window.pollEvent(ev)){
            switch(ev.type){
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape)
                    running = false;
                break;
            }
            game.sendEvent(&window, ev);
        }

        game.update(&window);

        window.clear(sf::Color::White);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.draw(&window);
        window.display();

        this_thread::sleep_for(chrono::milliseconds(13));
    }

    return 0;
}
