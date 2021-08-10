#include "Chunk.hpp"

Chunk::Chunk(int id, sf::Vector2i pos, std::function<bool(sf::Vector2i,sf::Vector2i)> reveal_in_chunk): _id(id), _pos(pos), _reveal_in_chunk(reveal_in_chunk)
{
    int i = 0;

    //set tiles to not reveal
    for (int j = 0; j < 256; j += 1)
        _tiles[j] = 0b00100000;

}

Chunk::~Chunk()
{

}

bool Chunk::addMine(unsigned int pos) {
    // if already is a mine return
    if ((_tiles[pos] & 0b00010000) != 0)
        return false;
    //add a mine
    _tiles[pos] |= 0b00010000;

    // add +1 to the mine counter of the tiles arounds
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

sf::Vector2i const &Chunk::getPos() {
    return _pos;
}


void Chunk::draw(sf::RenderWindow &window, sf::Sprite (&sprites)[13], bool over) {
    int sp = 0;
    
    //draw eatch tiles
    for(int i = 0; i < 256; i += 1) {
        //if not reveal
        if (_tiles[i] & 0b00100000) {
            sp = 12;
            //if game is over and it's a mine
            if (over && _tiles[i] & 0b00010000)
                sp = 10;
            //if it's a flag
            if (_tiles[i] & 0b01000000)
                sp = 9;
        }
        //if the mine was click on 
        else if (_tiles[i] & 0b00010000)
            sp = 11;
        //draw number of mines around
        else
            sp = _tiles[i] & 0b00001111;
        //set sprite position and draw
        sprites[sp].setPosition(i % 16 * 32 + _pos.x * 512, i / 16 * 32 + _pos.y * 512);
        window.draw(sprites[sp]);
    }
}

bool Chunk::click(sf::Vector2i pos, sf::Mouse::Button button)
{
    //convert map coord to chunk coord
    pos /= 32;

    // if right click for flag and not reveal then change flag state
    if (button == sf::Mouse::Right && (_tiles[pos.x + pos.y * 16] & 0b00100000) != 0) {
        _tiles[pos.x + pos.y * 16] ^= 0b01000000; 
        return false;
    }
    // Can't reveal flaged tile
    if ((_tiles[pos.x + pos.y * 16] & 0b01000000) != 0)
        return false;

    // if it's a mine
    if ((_tiles[pos.x + pos.y * 16] & 0b00010000) != 0) {
        _tiles[pos.x + pos.y * 16] &= 0b11011111;
        return true;
    }
    //if revealed and not 0;
    if ((_tiles[pos.x + pos.y * 16] & 0b00100000) == 0 && (_tiles[pos.x + pos.y * 16] & 0b00001111) == 0)
        return false; // check if enough flag aroud
    // else reveal
    reveal(pos.x, pos.y);
    return false;
}

bool Chunk::reveal(int x, int y) {
    // if already revealed do nothing
    if ((_tiles[x + y * 16] & 0b00100000) == 0)
        return false;
    //reveal
    _tiles[x + y * 16] &= 0b11011111;
    if ((_tiles[x + y * 16] & 0b00001111) != 0)
        return false; // TODO if enough flag arround reveal flag

    //if it's a 0 reveal around
    for (int i = x - 1; i < x + 2; i += 1) {
        for (int j = y - 1; j < y + 2; j += 1) {
            if (i < 0 || i > 15 || j < 0 | j > 15) {
                // reveal_in_other_chunk(x, y);
                continue; // reveal in other chunk
            }
            //already revealed
            if ((_tiles[i + j * 16] & 0b01000000) != 0)
                continue;
            // else reveal
            reveal(i, j);
        }
    }
    return false;
}


void Chunk::reveal_in_other_chunk(int x, int y) {
    sf::Vector2i chunk = _pos;
    sf::Vector2i tile(x, y);
    
    if (-1 == x) {
        chunk.x -= 1;
        tile.x = 15;
    }
    if (16 == x) {
        chunk.x += 1;
        tile.x = 1;
    }
    if (-1 == y) {
        chunk.y -= 1;
        tile.y = 15;
        
    }
    if (16 == y) {
        chunk.y += 1;
        tile.x = 1;
    }

    _reveal_in_chunk(chunk, tile);
}