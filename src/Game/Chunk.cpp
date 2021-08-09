#include "Chunk.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Chunk::Chunk(int id, sf::Vector2f pos): _id(id), _pos(pos)
{
    int i = 0;

    for (int j = 0; j < 256; j += 1)
        _tiles[j] = 0b00100000;

    std::srand(std::time(nullptr));
    while(i < 40) {
        int tmp = std::rand() % 256;
        if (addMine(tmp) == true)
            i += 1;
    }
}

Chunk::~Chunk()
{

}

bool Chunk::addMine(unsigned int pos) {
    if ((_tiles[pos] & 0b00010000) != 0)
        return false;
    _tiles[pos] |= 0b00010000;
    int x = pos % 16;
    int y = (pos - x) / 16;

    for (int i = x - 1; i < x + 2; i += 1) {
        for (int j = y - 1; j < y + 2; j += 1) {
            if (i < 0 || i > 15 || j < 0 | j > 15)
                continue;
            _tiles[j * 16 + i] += 1;
        }
    }
    return true;
}

void Chunk::draw(sf::RenderWindow &window, sf::Sprite (&sprites)[13], bool over) {
    int sp = 0;
    
    for(int i = 0; i < 256; i += 1) {
        if (_tiles[i] & 0b00100000) {
            sp = 12;
            if (over && _tiles[i] & 0b00010000)
                sp = 10;
            if (_tiles[i] & 0b01000000)
                sp = 9;
        }
        else if (_tiles[i] & 0b00010000)
            sp = 11;
        else
            sp = _tiles[i] & 0b00001111;
        sprites[sp].setPosition(i % 16 * 32, i / 16 * 32);
        window.draw(sprites[sp]);
    }
}

bool Chunk::click(sf::Vector2f pos, sf::Mouse::Button button)
{
    int x = (int)pos.x / 32;
    int y = (int)pos.y / 32;

    if (button == sf::Mouse::Right && (_tiles[x + y * 16] & 0b00100000) != 0) {
        _tiles[x + y * 16] ^= 0b01000000; 
        return false;
    }
    if ((_tiles[x + y * 16] & 0b01000000) != 0)
        return false;
    _tiles[x + y * 16] &= 0b11011111;
    if ((_tiles[x + y * 16] & 0b00010000) != 0)
        return true;
    if ((_tiles[x + y * 16] & 0b00001111) == 0)
        reveal(x, y);
    
    return false;
}

void Chunk::reveal(int x, int y) {
    _tiles[x + y * 16] &= 0b11011111;
    for (int i = x - 1; i < x + 2; i += 1) {
        for (int j = y - 1; j < y + 2; j += 1) {
            if (i < 0 || i > 15 || j < 0 | j > 15)
                continue;
            if ((_tiles[i + j * 16] & 0b00001111) == 0 && (_tiles[i + j * 16] & 0b00100000) != 0)
                reveal(i, j);
            else
                _tiles[i + j * 16] &= 0b11011111;
        }
    }
}
