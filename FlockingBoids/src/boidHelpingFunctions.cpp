#include "boidHelpingFunctions.h"

//--------------MATH FUNCTIONS-------------------
//calculate distance between two boids
float calculateDistance(sf::Vector2f a, sf::Vector2f b)
{
	float xDis = a.x - b.x;
	float yDis = a.y - b.y;
	float distance = sqrt((xDis * xDis) + (yDis * yDis));
	return distance;
}

//calculate the normalized vector of a vector
sf::Vector2f normalize(sf::Vector2f vec)
{
	sf::Vector2f normalized;

	float denom = sqrt(vec.x * vec.x + vec.y * vec.y);
	float x = vec.x / denom;
	float y = vec.y / denom;

	normalized.x = x;
	normalized.y = y;
	return normalized;
}

//return length of a vector
float vectorLength(sf::Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

//change from a velocity to a rotation in degrees
float updateDesiredRotation(sf::Vector2f newVelocity)
{
	//given the new velocity of the boid after calling the rules, update the desired rotation.
	//boid will then rotate towards this direction.
	float desiredRot;
	newVelocity = normalize(newVelocity);

	sf::Vector2f tempDir;
	tempDir.x = (newVelocity.x);
	tempDir.y = (newVelocity.y);

	
	float desiredRotRadians = atan2f(tempDir.y, tempDir.x); //atan2(y,x) is arctan(y/x). this gives -180->180. returns in  radians
	desiredRot = desiredRotRadians * (180.0 / M_PI);	//convert radians into degrees

	//now if the degree is in the range [-1,-180], convert it into the equal positive degree (so -180 -> 180, -1 -> 359)
	if (desiredRot < 0)
	{
		desiredRot *= -1;
		desiredRot = 360 - desiredRot;
	}

	return desiredRot;
}