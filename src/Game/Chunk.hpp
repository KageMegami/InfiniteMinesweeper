#include <SFML/Graphics.hpp>
#include <functional>
class Chunk {
public:
    Chunk(int id, sf::Vector2i pos, std::function<bool(sf::Vector2i,sf::Vector2i)> reveal_in_chunk);
    ~Chunk();
    void draw(sf::RenderWindow &window, sf::Sprite (&sprites)[13], bool over);
    bool click(sf::Vector2i pos, sf::Mouse::Button button);
    sf::Vector2i const &getPos() ;
    bool reveal(int x, int y);

    unsigned char _tiles[256];
private:
    void reveal_in_other_chunk(int x, int y);
    bool addMine(unsigned int pos);
    int _id;
    const sf::Vector2i _pos;
    //first 4 bits for number of mines around
    //5th bit for mine or not
    //6th bit for reveal or not
    //7th bit for flag or not
    std::function<bool(sf::Vector2i,sf::Vector2i)> _reveal_in_chunk;
};