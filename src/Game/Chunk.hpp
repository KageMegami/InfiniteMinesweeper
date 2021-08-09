#include <SFML/Graphics.hpp>

class Chunk {
public:
    Chunk(int id, sf::Vector2f pos);
    ~Chunk();
    void draw(sf::RenderWindow &window, sf::Sprite (&sprites)[13], bool over);
    bool click(sf::Vector2f pos, sf::Mouse::Button button);

private:
    bool addMine(unsigned int pos);
    void reveal(int x, int y);
    int _id;
    sf::Vector2f _pos;
    unsigned char _tiles[256];
};