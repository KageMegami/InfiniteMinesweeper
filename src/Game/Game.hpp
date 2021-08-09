#include <SFML/Graphics.hpp>

class Game {

public:
    Game();
    ~Game();

private:
    sf::RenderWindow _window;
    bool _moveCamera;
    void start();
};