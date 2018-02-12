#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>
#include "Shape.h"

class Square : public Shape<sf::RectangleShape>
{
private:
	float m_sideLength;
public:
	Square(sf::Vector2f position, float speed, float sideLength,
		sf::Color color);

	// Unique to Square
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Dctor
	~Square();
};

#endif
