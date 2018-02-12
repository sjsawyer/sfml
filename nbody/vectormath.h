#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <SFML/Graphics.hpp>
#include <cmath>

// x2 and y2 are optional. Default is (x2,y2) = (0,0) so can be used for
// calculating the magnitude of a vector (x1,y1)
float distance(float x1, float y1, float x2 = 0, float y2 = 0);
float distance(sf::Vector2f &p1, sf::Vector2f &p2 = sf::Vector2f(0, 0));

float dot(float x1, float y1, float x2, float y2);
float dot(sf::Vector2f &v1, sf::Vector2f &v2);

sf::Vector2f lNormal(sf::Vector2f &v);

sf::Vector2f rotate(sf::Vector2f &v, float theta);

#endif
