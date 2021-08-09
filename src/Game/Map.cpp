#include "Map.hpp"

Map::Map():_chunk(0, sf::Vector2f(0,0))
{
    _textures[0].loadFromFile("./assets/0.png");
    _textures[1].loadFromFile("./assets/1.png");
    _textures[2].loadFromFile("./assets/2.png");
    _textures[3].loadFromFile("./assets/3.png");
    _textures[4].loadFromFile("./assets/4.png");
    _textures[5].loadFromFile("./assets/5.png");
    _textures[6].loadFromFile("./assets/6.png");
    _textures[7].loadFromFile("./assets/7.png");
    _textures[8].loadFromFile("./assets/8.png");
    _textures[9].loadFromFile("./assets/flag.png");
    _textures[10].loadFromFile("./assets/mine.png");
    _textures[11].loadFromFile("./assets/clickedMine.png");
    _textures[12].loadFromFile("./assets/unknow.png");

    _sprites[0].setTexture(_textures[0]);
    _sprites[1].setTexture(_textures[1]);
    _sprites[2].setTexture(_textures[2]);
    _sprites[3].setTexture(_textures[3]);
    _sprites[4].setTexture(_textures[4]);
    _sprites[5].setTexture(_textures[5]);
    _sprites[6].setTexture(_textures[6]);
    _sprites[7].setTexture(_textures[7]);
    _sprites[8].setTexture(_textures[8]);
    _sprites[9].setTexture(_textures[9]);
    _sprites[10].setTexture(_textures[10]);
    _sprites[11].setTexture(_textures[11]);
    _sprites[12].setTexture(_textures[12]);

    for (int i = 0; i < 13; i += 1)
        _sprites[i].setScale(0.25, 0.25);
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window, sf::Vector2f camera, bool over) {
    _chunk.draw(window, _sprites, over);
    
}

bool Map::click(sf::Vector2f target,sf::Mouse::Button button)
{
    return _chunk.click(target, button);
}