#include "../include/line.hpp"

Line::Line(){}

Line::~Line(){}

void Line::create(sf::Vector2f PointA, sf::Vector2f PointB)
{
    l[0].position = PointA;
    l[1].position = PointB;
}

void Line::drawTo(sf::RenderWindow &win)
{
    win.draw(l,2,sf::Lines);
}