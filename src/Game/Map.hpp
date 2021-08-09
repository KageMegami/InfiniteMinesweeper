#include <SFML/Graphics.hpp>
#include "Chunk.hpp"

class Map {
public:
    Map();
    ~Map();
    void draw(sf::RenderWindow &window, sf::Vector2f camera, bool over);
    bool click(sf::Vector2f target, sf::Mouse::Button button);
private:
    Chunk _chunk;
    sf::Sprite _sprites[13];
    sf::Texture _textures[13];

};
