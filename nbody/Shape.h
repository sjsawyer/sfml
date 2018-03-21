#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>

/*** Base class Shape from which Circle and Square inherit from ***/

template <typename T> // T is sf::RectangleShape or sf::CircleShape
class Shape
{
protected:
    sf::Vector2f m_position;
    float m_speed;
    sf::Color m_color;
    T m_shape;

public:
    Shape();

    Shape(sf::Vector2f position, float speed, sf::Color color);

    void update();

    //virtual void setSize(float size);

    sf::FloatRect getPosition();

    T getShape();

    ~Shape();
};

#endif
