#include "Game.hpp"

#include <iostream>

Game::Game(): _window(sf::VideoMode(1280, 720), "Infinite Minesweeper!"), _moveCamera(false)
{
    start();
}
    
Game::~Game()
{
}

void Game::start() {

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2f oldPos, newPos;

    sf::View camera(sf::Vector2f(640,360), sf::Vector2f(1280, 720));
    _window.setView(camera);
    bool moved = false;


    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                oldPos.x = event.mouseButton.x;
                oldPos.y = event.mouseButton.y;
                moved = false;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    _moveCamera = true;
                }
            }

             if (_moveCamera && event.type == sf::Event::MouseMoved) {
                moved = true;
                newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                camera.setCenter(camera.getCenter() + newPos - oldPos);
                oldPos = newPos;
                _window.setView(camera);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                _moveCamera = false;
                if (moved == false)
                    std::cout << "click" << std::endl;
            }


            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _window.clear();
        _window.draw(shape);
        _window.display();
    }
}