#include <SFML/Graphics.hpp>
#include "Circle.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "vectormath.h"
#include "hsv.h"

bool Circle::seeded = false; // definition of static member variable 

Circle::Circle()
	: Shape()
{
	// Ensure srand() is called only once
	if (!seeded) { srand(time(0)); seeded = true; }

	// Number of different sized circles to produce
	int N = 10;

	float rng = static_cast<float>(rand() % (N + 1));
	m_radius = valBetween(9, 120, rng, N);
	m_mass = 100.f*(3.14f)*pow(m_radius, 2);
	m_speed = valBetween(2, 6, rng, N, true); // negatively proportional to rng
	m_color = hsv(rand(), 1.f, 1.f);
	m_position = sf::Vector2f(100,100);
	m_velocity = sf::Vector2f(m_speed, m_speed);
	
	m_shape.setPointCount(40);
	m_shape.setRadius(m_radius);
	m_shape.setFillColor(m_color);
	m_shape.setPosition(m_position);
}

Circle::Circle(sf::Vector2f position, float speed, float radius,
	sf::Color color, float mass)
	: Shape(position, speed, color)
{
	m_shape.setPointCount(64);
	m_radius = radius;
	m_shape.setRadius(m_radius);
	m_velocity = sf::Vector2f(m_speed, m_speed);
	m_mass = mass;
}

// Use this function to handle rebounding the sides of the screen
// as well as the sides of the Square
void Circle::reboundSides(int frameAdvance)
{
	m_position.x -= frameAdvance*m_velocity.x;
	m_velocity.x = -m_velocity.x;
}

// Use this function to handle rebounding the top/bottom of the screen
// as well as the top/bottom of the Square
void Circle::reboundTopBottom(int frameAdvance)
{
	m_position.y -= frameAdvance*m_velocity.y;
	m_velocity.y = -m_velocity.y;
}

void Circle::move()
{
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
}

sf::Vector2f Circle::getVelocity()
{
	return m_velocity;
}

void Circle::setVelocity(sf::Vector2f &newVelocity)
{
	m_velocity = newVelocity;
}

sf::Vector2f Circle::getCenter()
{
	float cX = getPosition().left + m_radius;
	float cY = getPosition().top + m_radius;
	return sf::Vector2f(cX, cY);
}

// Dctor
Circle::~Circle()
{
}


/*** Collision with circles and square and handle rebounding off circles ***/
// (Friend Functions to class Circle) 

bool isCollision(Circle &circle, Square &square)
{
	// Center of circle (cX, cY)
	float cX = circle.getCenter().x;
	float cY = circle.getCenter().y;

	// closest point on rectangle to circle's center (px, py)
	float px, py;

	// Determine px
	if (cX < square.getPosition().left)
		px = square.getPosition().left;
	else if (cX > square.getPosition().left + square.getPosition().width)
		px = square.getPosition().left + square.getPosition().width;
	else px = cX;

	// Determine py
	if (cY < square.getPosition().top)
		py = square.getPosition().top;
	else if (cY > square.getPosition().top + square.getPosition().height)
		py = square.getPosition().top + square.getPosition().height;
	else py = cY;

	// if (px,py) lies within circle, we have collision
	return distance(px, py, cX, cY) < circle.m_radius;
}

bool isCollision(Circle &c1, Circle &c2)
{
	// Center of circles
	float c1X = c1.getCenter().x;
	float c1Y = c1.getCenter().y;
	float c2X = c2.getCenter().x;
	float c2Y = c2.getCenter().y;

	return distance(c1X, c1Y, c2X, c2Y) - (c1.m_radius + c2.m_radius) < 0;
}

void reboundCircles(Circle &c1, Circle &c2)
{
	// Center of circles (c1x,c1y) and (c2x,c2y)
	float c1x = c1.getCenter().x;
	float c1y = c1.getCenter().y;
	float c2x = c2.getCenter().x;
	float c2y = c2.getCenter().y;

	// Distance between circles' centers
	float d = sqrtf(pow(c1x - c2x, 2) + pow(c1y - c2y, 2));
	
	// Normal vector at collision point
	float nx = (c2x - c1x) / d;
	float ny = (c2y - c1y) / d;

	// Intermediate value p to incorporate masses (derived from COE and COM) 
	float p = 2 * (c1.m_velocity.x * nx + c1.m_velocity.y * ny -
		c2.m_velocity.x * nx - c2.m_velocity.y * ny) /
		(c1.m_mass + c2.m_mass);

	// Resultant velocities
	float v1x = c1.m_velocity.x - p * c2.m_mass * nx;
	float v1y = c1.m_velocity.y - p * c2.m_mass * ny;
	float v2x = c2.m_velocity.x + p * c1.m_mass * nx;
	float v2y = c2.m_velocity.y + p * c1.m_mass * ny;

	// Set the velocities
	c1.setVelocity(sf::Vector2f(v1x, v1y));
	c2.setVelocity(sf::Vector2f(v2x, v2y));
}

