#include <SFML/Graphics.hpp>

class Line
{
private:

sf::Vertex l[2];

public:

Line();

~Line();

void create(sf::Vector2f PointA, sf::Vector2f PointB);

void drawTo(sf::RenderWindow &win);

};
