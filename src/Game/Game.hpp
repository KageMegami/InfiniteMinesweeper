#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Game {

public:
    Game();
    ~Game();

private:
    void start();
    sf::RenderWindow _window;
    bool _moveCamera;
    Map _map;
    bool _isGameOver;
};