#ifndef HELPINGFUNCTIONS_H
#define HELPINGFUNCTIONS_H
#define _USE_MATH_DEFINES //for pi
#include "structures.h"

//--------------MATH FUNCTIONS-------------------
//calculate distance between two boids
float calculateDistance(sf::Vector2f a, sf::Vector2f b);

//calculate the normalized vector of a vector
sf::Vector2f normalize(sf::Vector2f vec);

//return length of a vector
float vectorLength(sf::Vector2f vec);

//change from velocity to a rotation in degrees
float updateDesiredRotation(sf::Vector2f newVelocity);

#endif  // HELPINGFUNCTIONS_H