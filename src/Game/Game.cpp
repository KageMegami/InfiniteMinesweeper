#include "Game.hpp"
#include <iostream>

Game::Game(): _window(sf::VideoMode(1920, 1080), "Infinite Minesweeper!"), _moveCamera(false), _isGameOver(false)
{
    _window.setFramerateLimit(30);
    start();

}
    
Game::~Game()
{
}

void Game::start() {


    sf::Vector2f oldPos, newPos;
    bool moved = false;
    // sf::Texture texture;
    // texture.loadFromFile("./assets/gameover.png");
    // sf::Sprite gameover(texture);
    // gameover.setScale(0.5, 0.5);
    sf::View camera(sf::Vector2f(960,540), sf::Vector2f(1920, 1080));
    sf::View camera2(sf::Vector2f(960,540), sf::Vector2f(1920*1.5, 1080*1.5));
    camera2.setViewport(sf::FloatRect(0.7f, 0.7f, 0.3f, 0.3f));
    _window.setView(camera);

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed)
                _window.close();
            if (_isGameOver)
                continue;

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
                camera.setCenter(camera.getCenter() - (newPos - oldPos));
                camera2.setCenter(camera2.getCenter() - (newPos - oldPos));
                oldPos = newPos;
                _window.setView(camera);
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                _moveCamera = false;
                if (moved == false) {
                    _isGameOver = _map.click(_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)), event.mouseButton.button);
                }
            }
        }
        _window.clear();
        // draw game state
        _map.draw(_window, camera.getCenter() - sf::Vector2f(640,360), _isGameOver);
        _window.setView(camera2);
        //draw minimap
        _map.draw(_window, camera.getCenter() - sf::Vector2f(640,360), _isGameOver);
        _window.setView(camera);
        _window.display();
    }
}