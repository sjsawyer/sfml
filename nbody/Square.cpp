#include <SFML/Graphics.hpp>
#include "Square.h"

// Include the bodies of the constuctors, deconstructors
// and member functions of Square

Square::Square(sf::Vector2f position, float speed, float sideLength,
	sf::Color color)
	: Shape(position, speed, color)
{
	m_sideLength = sideLength;
	m_shape.setSize(sf::Vector2f(m_sideLength, m_sideLength));
}

void Square::moveLeft()
{
	m_position.x -= m_speed;
}

void Square::moveRight()
{
	m_position.x += m_speed;
}

void Square::moveUp()
{
	m_position.y -= m_speed;
}

void Square::moveDown()
{
	m_position.y += m_speed;
}

// Dctor
Square::~Square()
{
}
