#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>
#include "Shape.h"
#include <vector>
#include "Square.h"

class Circle : public Shape<sf::CircleShape>
{
private:
    float m_radius;
    sf::Vector2f m_velocity;
    float m_mass;
    static bool seeded; // defined in Circle.cpp

    float valBetween(float min, float max, float r, float rmax,
        bool negativelyProportional = false)
    {
        if (negativelyProportional)
            return (min - max) * (r - rmax) / rmax + max;
        else
            // Positively proportional
            return (max - min) * (r - rmax) / rmax + max;
    }

public:
    Circle();

    Circle(sf::Vector2f position, float speed, float radius,
        sf::Color color, float mass);

    // Unique to Circle
    float getMass() const;
    void reboundSides(int frameAdvance = 0);
    void reboundTopBottom(int frameAdvance = 0);
    sf::Vector2f getCenter();
    void moveX();
    void moveY();
    sf::Vector2f getVelocity();
    void setVelocity(const sf::Vector2f &newVelocity);

    // Dctor
    ~Circle();

    /*** Friend functions ***/
    // Handle collisions and rebounding
    friend bool isCollision(Circle &circle, Square &square);
    friend bool isCollision(Circle &circ1, Circle &circ2);
    friend void reboundCircles(Circle &c1, Circle &c2);
    friend void applyGravForce(Circle &c1, Circle &c2);
};




/*** Types for Circle class ***/

// Vector to hold circles
typedef std::vector<Circle> CircleVect;

// Corresponding iterator
typedef CircleVect::iterator CircleIt;

#endif
