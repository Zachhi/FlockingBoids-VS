#include "boids.h"

//----------------------CONSTRUCTOR----------------------
Boid::Boid(std::string boidType, sf::Texture& thatTexture)	//have to pass texture as a parameter, otherwise, we get the "white square problem".
{
	//update boids attributes according to its type passed (different speeds for rotation, mvmt, animation. also the bool value "isPredator")
	setAttributesBasedOnType(boidType);
	//generate random rotation in range 0->360. update direction (since direction is based off rotation) and update velocity (since direction is a part of velocity)
	setRandomRotationDirectionVelocity();
	//update the sprite and texture
	setSprite(thatTexture);
	//now everything is initialized. gameSpeed and windowDimensions are defined outside of the class
}

//------------SETTERS AND GETTERS------------
void Boid::setPosition(float xPos, float yPos)
{
	position.x = xPos;
	position.y = yPos;
	sprite.setPosition(position);
}
void Boid::setRotation(float rot)
{
	currRotation = rot;
	desiredRotation = currRotation;
	sprite.setRotation(currRotation);
}
sf::Vector2f Boid::getPosition()
{
	return position;
}
void Boid::setWindow(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}
void Boid::setGameSpeed(float gameSpeed)
{
	updateGameSpeed(gameSpeed);
}
//will give the boid a random rotation, and update its direction and velocity accordingly
void Boid::setRandomRotationDirectionVelocity()
{
	//randomize a rotation value between [0,360] first
	currRotation = rand() % 361 + 0;
	//update desired rotation to be the same
	desiredRotation = currRotation;
	//change from degrees to radians
	float rotInRad = (currRotation * (M_PI / 180));
	//now we can update direction since direction is calculated off of rotation in radians
	direction.x = cos(rotInRad);
	direction.y = sin(rotInRad);
	//now update velocity since it relies on direction
	velocity.x = direction.x * currMvmtSpeed;
	velocity.y = direction.y * currMvmtSpeed;
}
//sets the boids speed of mvmt, rotation, animation, etc. based on its type 
void Boid::setAttributesBasedOnType(std::string type)
{
	//first, update boidColor
	boidType = type;

	//based on the boid color, we will set it's desired attributes
	//we will set is mvmt, rotation, and anim speed.
	//we will also set the bool value "isPredator" depending on if it is a predator or not
	if (boidType == "green")
	{
		mvmtSpeedFactor = .95;
		rotationSpeedFactor = .95;
		animSpeedFactor = 0.04f;
		isPredator = false;
	}
	else if (boidType == "pink")
	{
		mvmtSpeedFactor = 1;
		rotationSpeedFactor = 1.2;
		animSpeedFactor = 0.035f;
		isPredator = false;
	}
	else if (boidType == "yellow")
	{
		rotationSpeedFactor = 1.4;
		mvmtSpeedFactor = 1.2;
		animSpeedFactor = 0.02f;
		isPredator = false;
	}
	else if (boidType == "white")
	{
		mvmtSpeedFactor = 0.7;
		rotationSpeedFactor = 1;
		animSpeedFactor = 0.065f;
		isPredator = false;
	}
	else if (boidType == "blue")
	{
		mvmtSpeedFactor = 0.85;
		rotationSpeedFactor = 0.85;
		animSpeedFactor = 0.045f;
		isPredator = false;
	}
	else//if predator
	{
		rotationSpeedFactor = 0.75;
		mvmtSpeedFactor = 0.9;
		baseRotationSpeed = 250;
		animSpeedFactor = .065f;
		isPredator = true;
	}

	//update the current speeds down here based off the speedFactors we just set
	currRotationSpeed = baseRotationSpeed * rotationSpeedFactor;
	currMvmtSpeed = baseMvmtSpeed * mvmtSpeedFactor;
	currAnimSpeed = baseAnimSpeed * animSpeedFactor;

	//set the gameSpeed values so we can switch game speed with ease
	gameSpeedRotationHold = rotationSpeedFactor;
	gameSpeedMvmtHold = mvmtSpeedFactor;
	gameSpeedAnimHold = animSpeedFactor;
}
//sets sprites texture and  rect (for the animation/image)
void Boid::setSprite(sf::Texture& thatTexture)
{
	//set the sprites texture and texture rect
	sprite.setTexture(thatTexture);
	sprite.setTextureRect(rectSprite);
	sprite.setOrigin(33, 14);
	sprite.setRotation(currRotation);

	if (!isPredator)
	{
		rectSprite.height = 30;
		rectSprite.width = 65;
	}
	else
	{
		rectSprite.height = 26;
		rectSprite.width = 67;
	}

	rectSprite.left = 0;
	rectSprite.top = 0;
}
//sets the "isPredatorOnScreen" variable
void Boid::setIsPredatorOnScreen(bool isPredOnScreen)
{
	isPredatorOnScreen = isPredOnScreen;
}

//--------------UPDATE BOID FUNCTIONS---------------
void Boid::updateBoid(sf::RenderWindow& window, bool isPredOnScreen)
{
	//update each necasaary value and then draw the boid to the window
	if (!isPredator)
		updatePreyAnim();
	else
		updatePredatorAnim();

	setIsPredatorOnScreen(isPredOnScreen);
	updateRotation();
	updateDirection();
	updateVelocity();
	updatePosition();

	window.draw(sprite);
}
void Boid::updatePredatorAnim()
{
	if (animPredatorClock.getElapsedTime().asSeconds() > currAnimSpeed * animSpeedFactor) //allows us to control speed of animation
	{
		updatePredatorRectSprite();

		sprite.setTextureRect(rectSprite);
		animPredatorClock.restart();
	}
}
void Boid::updatePreyAnim()
{
	if (animPreyClock.getElapsedTime().asSeconds() > currAnimSpeed * animSpeedFactor) //allows us to control speed of animation
	{
		updatePreyRectSprite();

		sprite.setTextureRect(rectSprite);
		animPreyClock.restart();
	}
}
void Boid::updatePosition()
{
	//first change the actual position
	//velocity is direction + magnitude (so direction it is headed in * its speed)
	position.x -= velocity.x;
	position.y -= velocity.y;
	//now set the sprites position
	sprite.setPosition(position);
}
void Boid::updateRotation()
{
	//rotation will be from [0,360]

	//get a value from a clock so frames dont affect rotation speed
	float elapsedRotTime = rotSpeedClock.getElapsedTime().asSeconds();
	rotSpeedClock.restart();
	float rotIncVal = currRotationSpeed * rotationSpeedFactor * elapsedRotTime;

	if (isPredatorOnScreen) //I have decided it looks better, that if there is any predator on screen, everyones rotation speed is multiplied by .025 instead of elapsed rot time
		rotIncVal = currRotationSpeed * rotationSpeedFactor * .025;

	//requirement 1: the difference between the current rotation and desired rotation must be within the rotation increment
	// 	   example: if rotation increment (rotIncVal) is 3, currRotation - desiredRotation has to be greater than 3
	// 	   I did this so we can use float instead of int, giving us more control over rotation speed, and allowing us to 
	// 	   account for frame rate.
	// 	   if we used int, we could simply say currRotation!=desiredRotation instead
	// 
	//requirement 2: enough time has passed (controls speed of rotation)
	if ((abs(currRotation - desiredRotation) > (rotIncVal)) && (rotClock.getElapsedTime().asSeconds() > 0.01f))
	{
		//we have degrees in range [0,360]. distanceBetween is the distance from desiredRotation->rotation in CW direction. distanceInverse is the distance of desiredRotation->rotation in CCW direction
		int distanceBetween = (currRotation - desiredRotation);
		int distanceInverse = 360 - abs(distanceBetween);

		//four cases: draw a circle on paper and test the four cases to see for yourself
		//basically makes sure we rotate from currRotation->desiredRotation the most efficient way possible. either CW or CCW
		if (abs(distanceBetween) < distanceInverse && distanceBetween < 0)
			currRotation += rotIncVal;
		else if (abs(distanceBetween) < distanceInverse && distanceBetween > 0)
			currRotation -= rotIncVal;
		else if (abs(distanceBetween) > distanceInverse && distanceBetween < 0)
			currRotation -= rotIncVal;
		else if (abs(distanceBetween) > distanceInverse && distanceBetween > 0)
			currRotation += rotIncVal;
		else // the fifth case is if distanceBetween = distanceInverse, in which case we must rotate 180 degrees. In this case just turn CW
			currRotation += rotIncVal;

		//if rotation = -1, make it 359. 
		//example: currRotation = 2, desiredRotation = 350
		//we will subtract from 2 until we reach 350. instead of 2..0..-2..-4..-6 it will be 2..0..358..356..etc. 
		if (currRotation < 0)
			currRotation = currRotation + 360;

		//this is the opposite of the above
		else if (currRotation > 360)
			currRotation = currRotation - 360;

		rotClock.restart();
	}
	sprite.setRotation(currRotation);
}
void Boid::updateVelocity()
{
	float elapsedTimeMvmt = mvmtClock.getElapsedTime().asSeconds(); //use clock so frames dont affect speed
	mvmtClock.restart();
	velocity.x = direction.x * currMvmtSpeed * elapsedTimeMvmt * mvmtSpeedFactor; //velocity is direction + mvmtSpeed
	velocity.y = direction.y * currMvmtSpeed * elapsedTimeMvmt * mvmtSpeedFactor;
}
void Boid::updateDirection()
{
	float rotInRad = (currRotation * (M_PI / 180)); //change rotation from degrees to radians so we can get the direction
	direction.x = cos(rotInRad);
	direction.y = sin(rotInRad);
}
void Boid::updatePreyRectSprite()
{
	//setting the path for animation to follow
	if (rectSprite.top == 30 && rectSprite.left == 650)
	{
		rectSprite.top = 0;
		rectSprite.left = 0;
	}
	else if (rectSprite.left == 650) //670 536 1403 //750
	{
		rectSprite.top += 30;
		rectSprite.left = 0;
	}
	else
	{
		rectSprite.left += 65;
	}
}
void Boid::updatePredatorRectSprite()
{
	if (rectSprite.top == 26 && rectSprite.left == 536)
	{
		rectSprite.top = 0;
		rectSprite.left = 0;
	}
	else if (rectSprite.left == 536) //670 536 1403 //750
	{
		rectSprite.top += 26;
		rectSprite.left = 0;
	}
	else
	{
		rectSprite.left += 67;
	}
}
void Boid::updateGameSpeed(float gameSpeed)
{
	//take the holds (values that dont change) and multiply by game speed and set equal to the factors. This will make changes in speed even throughout
	mvmtSpeedFactor = gameSpeedMvmtHold * gameSpeed;
	rotationSpeedFactor = gameSpeedRotationHold * gameSpeed;
	animSpeedFactor = gameSpeedAnimHold / gameSpeed;
}

//--------BOUND CHECKING-------------
//bound checking when border is on (hard bound checking, not allowed to go out)
sf::Vector2f Boid::boundCheckBorder()
{
	float radiusX;
	float radiusY;
	float checker;

	float centerWidth = windowWidth / 2.0f;
	float centerHeight = windowHeight / 2.0f;

	//predator will go a little closer to borders than prey
	if (!isPredator)
	{
		radiusX = centerWidth - 50; 
		radiusY = centerHeight - 50; 
		checker = 0.8f;
	}
	else
	{
		radiusX = centerWidth; 
		radiusY = centerHeight; 
		checker = 0.85f;
	}

	//vector of the center
	sf::Vector2f center(centerWidth, centerHeight);
	//now we have a vector of how far it is from center
	sf::Vector2f centerOffset = center - position;

	float checkX = abs(centerOffset.x) / radiusX; //ratio of the how close boid is to x bounds
	float checkY = abs(centerOffset.y) / radiusY; //ratio of how close boid is to y bounds
	float xOrY = std::max(checkX, checkY); //get the max of the two (whichever one is coser to bounds)

	//it is close enough to the center of the screen, dont worry about bounding
	if (checkX < checker && checkY < checker) 
		return sf::Vector2f(0.0f, 0.0f);
	//this means it is too far from the center and needs to change its position/rotation
	else
	{
		//if it goes out of bounds, hardcoded to stay in bounds
		if (position.x < 10)
			position.x = 20;
		else if (position.x > windowWidth- 10)
			position.x = windowWidth - 20;
		if (position.y < 10)
			position.y = 20;
		else if (position.y > windowHeight- 10)
			position.y = windowHeight - 20;

		//change rotation speed depending on how close to the border it is so it never goes out of bounds
		//closer it is to the bounds, higher the rotation speed
		if (xOrY <= 0.82f)
			currRotationSpeed = 175;
		else if (xOrY <= 0.85f)
			currRotationSpeed = 200;
		else if (xOrY <= 0.90f)
			currRotationSpeed = 250;
		else if (xOrY <= 0.92f)
			currRotationSpeed = 300;
		else if (xOrY <= 0.96f)
			currRotationSpeed = 500;
		else if (xOrY <= 0.98f)
			currRotationSpeed = 1000;
		else
			currRotationSpeed = 1500;

		//this returns the the boid a desiredRotation to the center
		return centerOffset;
	}

}
//bound checking when border is off (soft bound checking, can go out and will slowly come back)
sf::Vector2f Boid::boundCheckNoBorder()
{
	float radiusX = windowWidth / 2.0f;
	float radiusY = windowHeight / 2.0f;

	sf::Vector2f center(radiusX, radiusY);
	sf::Vector2f centerOffset = center - position;

	float checkX = abs(centerOffset.x) / radiusX;
	float checkY = abs(centerOffset.y) / radiusY;

	//only return to center if its ratio of x or y from center is greater than 1.5
	if (checkX < 1.5f && checkY < 1.5f) //it is close enough to the center of the screen to not worry about bounding
		return sf::Vector2f(0.0f, 0.0f);
	else								//this means it is too far from the center and needs to change its position/rotation
		return centerOffset;
}

//--------REPULSION CHECKING---------
//check if boid is too close to any repulsions, if so, return a sf::Vector2f of where it should head towards next
sf::Vector2f Boid::repulsionCheck(std::vector<Repulsion>& repulsions)
{
	float desired;
	//if predator, it can get within 100 pixels away. Boids can get within 200 pixels away before trying to swim away from repulsion
	if (isPredator)
		desired = 100;
	else
		desired = 200;

	sf::Vector2f separationVelocity(0.f, 0.f); //the velocity we return that will tell boid where to head to
	float newRotSpeed; //the new rotation speed it will have depending on how close it is
	float minDistance = 0; //closest distance a boid is to a repulsion
	int minIndex = 0; //index of that repulsion it is closest to

	//get the first min distance from repulsions[0]
	if (repulsions.size() > 0)
		minDistance = calculateDistance(position, repulsions[0].getPosition());

	//now loop through repulsions to find the repulsion the boid is closest to
	for (int i = 0; i < repulsions.size(); i++)
	{
		float currDistance = calculateDistance(position, repulsions[i].getPosition());
		if (currDistance <= minDistance)
		{
			minDistance = currDistance;
			minIndex = i;
		}
	}

	//if minDistance is less than the desired diestance, we will now return the correct direction it should head and update its rotation speed
	if (minDistance < desired && repulsions.size() > 0)
	{
		separationVelocity += (repulsions[minIndex].getPosition() - getPosition());
		if (separationVelocity != sf::Vector2f(0, 0))
		{
			separationVelocity += normalize(separationVelocity);
		}

		//update speed according to distance
		if (minDistance > 190)
		{
			newRotSpeed = 150.0f;
			
		}
		else if (minDistance > 150)
		{
			newRotSpeed = 150.0f;
		}
		else if (minDistance > 100)
		{
			newRotSpeed = 250.0f;
		}
		else if (minDistance > 75)
		{
			newRotSpeed = 350.0f;
		}
		else if (minDistance > 50)
		{
			newRotSpeed = 400.0f;
		}
		else
		{
			newRotSpeed = 700.0f;
			currMvmtSpeed = 250.0f; //slow it down if it is really close
		}

		if (newRotSpeed > currRotationSpeed)
			currRotationSpeed = newRotSpeed;
	}

	return separationVelocity;
}

//-----GET NEARBY BOIDS---------------
//return a vector of the boids given in parameter than are within the desiredDis to this current boid
std::vector<Boid> Boid::getNearbyBoids(std::vector<Boid>& boids, float desiredDis)
{
	float nearbyCheck = desiredDis; //adds boid to nearbyBoids vector if they are within nearbyCheck distance
	std::vector<Boid> nearbyBoids;

	for (int i = 0; i < boids.size(); i++)
	{
		float currDistance = calculateDistance(position, boids[i].position);
		//if they are too close together, and if it is not itself, add boid to vector
		if (currDistance <= nearbyCheck && currDistance > 0)
			nearbyBoids.push_back(boids[i]);
	}

	return nearbyBoids; //return vector of nearbyBoids 
}

//----------------THE 3 RULES------------------
//SEPARATION - make sure boids keep a distance from each other (rule 1)
sf::Vector2f Boid::separation(std::vector<Boid>& nearbyBoids, float desiredDis)
{
	float desiredDistance = desiredDis;
	sf::Vector2f separationVelocity(0.f, 0.f);

	//each boid will check its distance to every other nearby boid (of same type)
	for (int i = 0; i < nearbyBoids.size(); i++)
	{
		//calculating distance between the two
		float currDistance = calculateDistance(position, nearbyBoids[i].position);

		//if they are too close together
		if (currDistance < desiredDistance)
		{
			//update this boids new velocity
			separationVelocity += (nearbyBoids[i].getPosition() - getPosition());
		}
	}

	//if vector is not 0,0, normalize it so it is in terms of one
	if (separationVelocity != sf::Vector2f(0, 0))
	{
		separationVelocity = normalize(separationVelocity);
	}
	return separationVelocity;
}
//COHESION - make sure boids move toward avg center of mass of nearby boids (rule 2)
sf::Vector2f Boid::cohesion(std::vector<Boid>& nearbyBoids)
{
	//get position all nearby boids (of same type)
	sf::Vector2f centerOfMass(0.f, 0.f);
	for (int i = 0; i < nearbyBoids.size(); i++)
		centerOfMass -= nearbyBoids[i].getPosition();

	//if its not zero...we now have to divide it so it is the center of mass
	if (centerOfMass != sf::Vector2f(0, 0))
	{
		centerOfMass.x /= nearbyBoids.size();
		centerOfMass.y /= nearbyBoids.size();

		centerOfMass += position; //add center of mass to position to account for the boids current position
		centerOfMass = normalize(centerOfMass);
	}
	return centerOfMass; //return the center of mass
}
//ALLIGNMENT - make sure boids have average heading direction of nearby boids (rule 3)
sf::Vector2f Boid::allignment(std::vector<Boid>& nearbyBoids)
{
	//get direction of all nearby boids (of same type)
	sf::Vector2f nearbyVelocity(0.f, 0.f);
	for (int i = 0; i < nearbyBoids.size(); i++)
		nearbyVelocity += nearbyBoids[i].direction;

	//if its not 0...divide it so we get average direction
	if (nearbyVelocity != sf::Vector2f(0, 0))
	{
		nearbyVelocity.x /= nearbyBoids.size();
		nearbyVelocity.y /= nearbyBoids.size();
		nearbyVelocity = normalize(nearbyVelocity);
	}
	return nearbyVelocity; //return the new direction 
}

//---------------CALL RULES---------------------
void Boid::callBoidRules(std::vector<Boid>& boids, std::vector<Boid>& predators, std::vector<Repulsion> repulsions, Rules& rules, Behavior& behavior)
{
	std::vector<Boid> nearbySameBoids;//get a vector of nearby boids that are of the same type (same color, not predator)
	std::vector<Boid> nearbyPredators; //get a vector of nearby predators (so they know when to run away)

	//according to the boids color, they will have a different range for spotting predators
	//predator detets them at 250
	if (boidType == "blue")
		nearbyPredators = getNearbyBoids(predators, 400); //can detect in range 400, but only runs when predator is tracking their type. Which will only be at 250
	else if (boidType == "green")
		nearbyPredators = getNearbyBoids(predators, 200); //can detect in range 200
	else if (boidType == "pink")
		nearbyPredators = getNearbyBoids(predators, 600); //can detect in range 600, but will only run away at 150
	else if (boidType == "yellow")
		nearbyPredators = getNearbyBoids(predators, 400); // can detect in range 400
	else
		nearbyPredators = getNearbyBoids(predators, 400); //can detect in range 400

	nearbySameBoids = getNearbyBoids(boids, 100);

	//this will be the boids desired velocity after calling the 3 rules
	sf::Vector2f newVelocity(0.f, 0.f);

	//this is the bound checking, make sure they dont go off screen
	if (behavior.isBorder)
		newVelocity -= boundCheckBorder();
	else
		newVelocity -= boundCheckNoBorder();

	//if predators nearby, update boids velocity based on predator
	newVelocity += 0.5f * scatter(nearbyPredators); //195

	//add to velocity based on repulsions
	newVelocity += 0.5f * repulsionCheck(repulsions);

	//if borders are turned on and the position goes too far, set the rotation to the desiredRotation (which will be updated already towards away from the border) instantly. This gaurantees the boids will not go off screen, even when being chased by a predator
	if ((position.x > windowWidth || position.x < 0 || position.y < 0 || position.y > windowHeight) && behavior.isBorder)
		currRotation = desiredRotation;

	//if velocity is still 0, that means there was no repulsion, no predator, and no bound checking. therefore, flock.
	if (newVelocity == sf::Vector2f(0, 0))
	{
		//if flocking, rotationSpeed mvmtSpeed and animSpeed should all be their constant base speed. So update it back to the base speeds here
		if (nearbyPredators.size() < 1) //this seems like a useless if statement. however, we need it for pink boids so they do not go back to base speeds if they arent currently running from a predator, but are detecting one. we want pink to move fast until they are 600 away from a predator
		{
			currRotationSpeed = baseRotationSpeed;
			currMvmtSpeed = baseMvmtSpeed;
			currAnimSpeed = baseAnimSpeed;
		}

		//check which rules are active and apply them with correct coefficients
		if (rules.separationBool && rules.cohesionBool && rules.allignmentBool)
		{
			nearbySameBoids = getNearbyBoids(boids, behavior.sightRange);
			newVelocity += behavior.rule1Ratio * separation(nearbySameBoids, behavior.rule1Distance);
			newVelocity += behavior.rule2Ratio * cohesion(nearbySameBoids);
			newVelocity +=behavior.rule3Ratio * allignment(nearbySameBoids);
		}
		else
		{
			if (rules.separationBool)
			{
				//if separation is on, range of 300 works best
				nearbySameBoids = getNearbyBoids(boids, 300);
				//if not all 3 rules are toggled, a separation of 150 works best
				newVelocity += separation(nearbySameBoids, 150);
			}
			//if separation is off, a getNearbySameBoids range of 250 works best
			nearbySameBoids = getNearbyBoids(boids, 250);
			//now just add these to velocity if they are toggled
			if (rules.cohesionBool)
				newVelocity += cohesion(nearbySameBoids);
			if (rules.allignmentBool)
				newVelocity += allignment(nearbySameBoids);
		}
	}

	//after getting velocity, update the direction and desired rotation for the boid. From this, the boids new velocity will be calculated in updateVelocity() which will be called from updateBoid()
	if (newVelocity != sf::Vector2f(0, 0))
	{
		desiredRotation = updateDesiredRotation(newVelocity);
	}
}
void Boid::callPredatorRules(std::vector<Boid>& blueBoids, std::vector<Boid>& DBlueBoids, std::vector<Boid>& pinkBoids, std::vector<Boid>& yellowBoids,  std::vector<Boid>& predators, std::vector<Repulsion> repulsions)
{
	//first, determine which color to chase
	std::vector<Boid> nearbyPrey = whichBoidToChase(blueBoids, DBlueBoids, yellowBoids, pinkBoids); //cant detect white boids
	std::vector<Boid> nearbyPredators = getNearbyBoids(predators, 500);

	float distanceToCenterOfMass;
	sf::Vector2f newVelocity(0.f, 0.f);

	//predator will always stay in bounds, even if borders are off
	newVelocity -= boundCheckBorder();

	//update newVelocity based on repulsions if any are nearby
	newVelocity += 0.5f * repulsionCheck(repulsions);

	//if it doesnt need to be bound checked, then search and chase prey
	if (newVelocity == sf::Vector2f(0, 0))
	{
		if (nearbyPrey.size() > 0)
		{
			//get the distance the predator is to center of mass it are headed towards
			distanceToCenterOfMass = calculateDistance(position, centerOfMassPostition(nearbyPrey));

			//update predator according to how close the prey are
			updatePredatorAttributes(distanceToCenterOfMass);

			//make it swim towards the center of mass of nearby prey
			newVelocity += cohesion(nearbyPrey);
		}
		else //this means there is no bound check, repulsion, or prey to chase. set stats back to baseline
		{
			currTracking = "none";
			currRotationSpeed = baseRotationSpeed;
			currMvmtSpeed = baseMvmtSpeed;
			currAnimSpeed = baseAnimSpeed;
		}

		//keep a distance from other predators
		newVelocity += 0.5f * separation(nearbyPredators, 200);
	}

	//update predators rotation if it is not 0,0. mvmtSpeed and rotationSpeed will already be updated. Velocity, direction and position will be updated based of the rotation
	if (newVelocity != sf::Vector2f(0, 0))
		desiredRotation = updateDesiredRotation(newVelocity);
}

//-------------PREY RULE HELPERS---------------------
sf::Vector2f Boid::scatter(std::vector<Boid>& nearbyPredators)
{
	sf::Vector2f separationVelocity(0.f, 0.f);

	//loop through its nearbyPredators
	for (int i = 0; i < nearbyPredators.size(); i++)
	{
		//this will always pass unless it is blue
		//blue will only pass when predator is currently tracking them
		if (nearbyPredators[i].currTracking == boidType || boidType != "blue")
		{
			//calculating distance between the two (current boid and predator)
			float currDistance = calculateDistance(position, nearbyPredators[i].position);
			//update boids speed of rotation and mvmt and animation based on how close predator is to them
			updatePreyAttributes(currDistance);

			//pink will move normal until predator is 150 away. Then they move really fast and away until they are 600 away from predator
			if (boidType != "pink")
			{
				//update this boids new velocity
				separationVelocity += (nearbyPredators[i].getPosition() - getPosition());
			}
			else //if pink
			{
				if (currDistance < 150)
				{
					//update this boids new velocity only if its 150 pixels close and pink
					separationVelocity += (nearbyPredators[i].getPosition() - getPosition());
				}
			}
		}
	}

	//if vecotr is not 0,0, normalize it so it is in terms of one
	if (separationVelocity != sf::Vector2f(0, 0))
	{
		separationVelocity = normalize(separationVelocity);
	}

	return separationVelocity;
}
void Boid::updatePreyAttributes(float distance)
{
	//blue: base line. detects at average distance and runs at average speed
	//white: same as blue, but isnt detected by predators
	//darkBlue/green: detects at lower distance and runs at a slower speed
	//pink: detects at lower distance and runs at a higher speed and runs for longer
	//yellow: detects at higher distance and runs at lower speed
	
	//update mvmt rotation and animation speeds based on how close predator is to them
	if (boidType == "blue" || boidType == "white")
	{
		if (distance > 250)
		{
			currMvmtSpeed = 400;
			currRotationSpeed = 200;
			currAnimSpeed = 1.0f;
		}
		else if (distance > 200)
		{
			currMvmtSpeed = 600;
			currRotationSpeed = 320; //220
			currAnimSpeed = .9f;
		}
		else if (distance > 150)
		{
			currMvmtSpeed = 1000;
			currRotationSpeed = 460;//260
			currAnimSpeed = .8f;
		}
		else if (distance > 100)
		{
			currMvmtSpeed = 1500;
			currRotationSpeed = 500;
			currAnimSpeed = .7f;
		}
		else if (distance > 50)
		{
			currMvmtSpeed = 1750;
			currRotationSpeed = 500;
			currAnimSpeed = .7f;
		}
		else if (distance > 40)
		{
			currMvmtSpeed = 1500;
			currRotationSpeed = 550;
			currAnimSpeed = .8f;
		}
		else if (distance > 30)
		{
			currMvmtSpeed = 1000;
			currRotationSpeed = 550;
			currAnimSpeed = .9f;
		}
		else if (distance > 20)
		{
			currMvmtSpeed = 800;
			currRotationSpeed = 550;
			currAnimSpeed = .8f;
		}
		else
		{
			currMvmtSpeed = 500;
			currRotationSpeed = 550;
			currAnimSpeed = .85f;
		}
	}
	else if (boidType == "green")
	{
		if (distance > 150)
		{
			currMvmtSpeed = 700;//900
			currRotationSpeed = 150;
			currAnimSpeed = 0.04f;
		}
		else if (distance > 100)
		{
			currMvmtSpeed = 1000;
			currRotationSpeed = 200; //220
			currAnimSpeed = 0.038f;
		}
		else if (distance > 50)
		{
			currMvmtSpeed = 1200;
			currRotationSpeed = 200;//260
			currAnimSpeed = 0.034f;
		}
		else
		{
			currMvmtSpeed = 1500;
			currRotationSpeed = 750;
			currAnimSpeed = 0.03f;
		}

	}
	else if (boidType == "pink") //same as blue just much faster //150 rot base 395 mvmt base
	{
		if (distance > 550)
		{
			currMvmtSpeed = 395;
			currRotationSpeed = 150;
			currAnimSpeed = 0.035f;
		}
		else if (distance > 500)
		{
			currMvmtSpeed = 500;
			currRotationSpeed = 150;
			currAnimSpeed = 0.035f;
		}
		else if (distance > 450)
		{
			currMvmtSpeed = 800;
			currRotationSpeed = 150;
			currAnimSpeed = 0.035f;
		}
		else if (distance > 100 && distance < 150)
		{
			currMvmtSpeed = 1300;
			currRotationSpeed = 300;
			currAnimSpeed = 0.025f;
		}
		else if (distance < 101)
		{
			currMvmtSpeed = 1500;
			currRotationSpeed = 700;
			currAnimSpeed = 0.025f;
		}


	}
	else //yellow
	{
		//395 and 150
		if (distance > 300)
		{
			currMvmtSpeed = 395;
			currRotationSpeed = 180;
			currAnimSpeed = 0.02f;
		}
		else if (distance > 200)
		{
			currMvmtSpeed = 395;
			currRotationSpeed = 220;
			currAnimSpeed = 0.019f;
		}
		else if (distance > 100)
		{
			currMvmtSpeed = 450;
			currRotationSpeed = 270;
			currAnimSpeed = 0.015f;
		}
		else
		{
			currMvmtSpeed = 550;
			currRotationSpeed = 800;
			currAnimSpeed = 0.01f;
		}

	}

}

//------------PREDATOR RULE HELPERS------------------
//returns center of mass of all nearby prey
sf::Vector2f Boid::centerOfMassPostition(std::vector<Boid>& nearbyBoids)
{
	//get positions of all prey
	sf::Vector2f centerOfMass(0.f, 0.f);
	for (int i = 0; i < nearbyBoids.size(); i++)
	{
		centerOfMass += nearbyBoids[i].getPosition();
	}

	//if not 0...divide it to get average center of mass
	if (centerOfMass != sf::Vector2f(0, 0))
	{
		centerOfMass.x /= nearbyBoids.size();
		centerOfMass.y /= nearbyBoids.size();
	}
	return centerOfMass;
}
//updates predator rotation, speed, animation when it is chasing prey
void Boid::updatePredatorAttributes(float distance)
{
	//this is for a nearbyPrey of range 250
	//slowly speed up, get real fast when close, then start slowing once prey gets far enough away
	if (distance > 225)	//250-226
	{
		currMvmtSpeed = 550;
		currRotationSpeed = 150;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 215) //225-201
	{
		currMvmtSpeed = 700;
		currRotationSpeed = 180;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 200) //225-201
	{
		currMvmtSpeed = 850;
		currRotationSpeed = 180;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 185) //225-201
	{
		currMvmtSpeed = 1100;
		currRotationSpeed = 180;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 175) ///200 - 176
	{
		currMvmtSpeed = 1150;
		currRotationSpeed = 200;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 150) //175 - 151
	{
		currMvmtSpeed = 1200;
		currRotationSpeed = 220;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 125) //150 - 126
	{
		currMvmtSpeed = 1100;
		currRotationSpeed = 200;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 100) //125 - 101
	{
		currMvmtSpeed = 900;
		currRotationSpeed = 180;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 75) //100 - 76
	{
		currMvmtSpeed = 800;
		currRotationSpeed = 180;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 50) //75 - 51
	{
		currMvmtSpeed = 700;
		currRotationSpeed = 150;
		currAnimSpeed = 0.062f;
	}
	else if (distance > 25) //50 - 26
	{
		currMvmtSpeed = 600;
		currRotationSpeed = 150;
		currAnimSpeed = 0.063f;
	}
	else //25 - 0
	{
		currMvmtSpeed = 500;
		currRotationSpeed = 150;
		currAnimSpeed = 0.065f;
	}



}
//given the blue-white boids, find which boid color to chase after
std::vector<Boid> Boid::whichBoidToChase(std::vector<Boid>& blueBoids, std::vector<Boid>& DBlueBoids, std::vector<Boid>& yellowBoids, std::vector<Boid>& pinkBoids)
{
	//get vectors of all nearby different types prey
	std::vector<Boid> nearbyBluePrey = getNearbyBoids(blueBoids, 250);
	std::vector<Boid> nearbyGreenPrey = getNearbyBoids(DBlueBoids, 250);
	std::vector<Boid> nearbyPinkPrey = getNearbyBoids(pinkBoids, 250);
	std::vector<Boid> nearbyYellowPrey = getNearbyBoids(yellowBoids, 250);
	//store the numbers of the nearby prey
	int numBlue = nearbyBluePrey.size();
	int numGreen = nearbyGreenPrey.size();
	int numPink = nearbyPinkPrey.size();
	int numYellow = nearbyYellowPrey.size();
	//now retrieve the max of these numbers to see which type of prey is largest in number near predator
	std::vector<int> counts;
	counts.push_back(numBlue); counts.push_back(numGreen); counts.push_back(numPink); counts.push_back(numYellow);
	int max = counts[0];
	for (int i = 1; i < 4; i++)
	{
		if (counts[i] > max)
			max = counts[i];
	}
	//now depending on the max, return that vector
	if (max == numBlue)
	{
		currTracking = "blue";
		return nearbyBluePrey;
	}
	else if (max == numGreen)
	{
		currTracking = "green";
		return nearbyGreenPrey;
	}
	else if (max == numPink)
	{
		currTracking = "pink";
		return nearbyPinkPrey;
	}
	else
	{
		currTracking = "yellow";
		return nearbyYellowPrey;
	}

}

