#include "vectormath.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// x2 and y2 are optional. Default is (x2,y2) = (0,0) so can be used for
// calculating the magnitude of a vector (x1,y1)
float distance(float x1, float y1, float x2, float y2) // (x2,y2) = (0,0)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float distance(const sf::Vector2f &p1, const sf::Vector2f &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float dot(float x1, float y1, float x2, float y2)
{
    return x1*x2 + y1*y2;
}

float dot(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

sf::Vector2f normalize(const sf::Vector2f &v)
{
    float magnitude = distance(v);
    return sf::Vector2f(v.x/magnitude, v.y/magnitude);
}

sf::Vector2f normalize(float x1, float x2)
{
    float magnitude = distance(x1, x2);
    return sf::Vector2f(x1/magnitude, x2/magnitude);
}

sf::Vector2f lNormal(const sf::Vector2f &v)
{
    return sf::Vector2f(-v.y, v.x);
}

sf::Vector2f rotate(const sf::Vector2f &v, float theta)
{
    float vx_new = dot(sf::Vector2f(cos(theta), -sin(theta)), v);
    float vy_new = dot(sf::Vector2f(sin(theta), cos(theta)), v);
    return sf::Vector2f(vx_new, vy_new);
}

