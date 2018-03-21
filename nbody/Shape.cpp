#include <SFML/Graphics.hpp>
#include "Shape.h"

template <class T>
Shape<T>::Shape(sf::Vector2f position, float speed, sf::Color color)
    : m_position(position), m_speed(speed), m_color(color)
{
    m_shape.setFillColor(color);
    m_shape.setPosition(position);
}

template <class T>
void Shape<T>::update()
{
    m_shape.setPosition(m_position);
}

template <class T>
sf::FloatRect Shape<T>::getPosition()
{
    return m_shape.getGlobalBounds();
}

//template <class T>
//virtual void Shape<T>::setSize(float size) = 0;

template <class T>
T Shape<T>::getShape()
{
    return m_shape;
}

template <class T>
Shape<T>::~Shape()
{
}
