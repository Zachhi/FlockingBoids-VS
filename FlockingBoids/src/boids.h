#ifndef BOIDS_H
#define BOIDS_H
#define _USE_MATH_DEFINES //for pi

#include "boidHelpingFunctions.h"

struct Behavior;
struct Rules;
#include "structures.h"

class Boid {
private:
	
	float currRotation; // direction it is currently in, in degrees. clockwise [0,360]
	float desiredRotation;  //direction it will desire to rotate towards

	//current rotation/mvmt/animation speed it is moving at as of this instant for the boid
	float currRotationSpeed; 
	float currMvmtSpeed; 
	float currAnimSpeed; 

	//base rotatoin/mvmt/animation speed for all boid types ie. predators, blue boid, green boid, etc. 
	//This is the baseline. We will change this based on the factor values below, so we can easily make something move 2x, 1.5x, or 0.5x (etc.) as fast.
	float baseRotationSpeed = 150.0f; 
	float baseMvmtSpeed = 395; 
	float baseAnimSpeed = 1.0f; 

	//factor to control the increase or decrease of rotation/mvmt/animation speed
	float rotationSpeedFactor;
	float mvmtSpeedFactor; 
	float animSpeedFactor; 

	//these values make sure we can change game speed with ease. We need base speeds that will never change. That is these values
	float gameSpeedRotationHold;
	float gameSpeedMvmtHold;
	float gameSpeedAnimHold;

	bool isPredator; //check if the current boid is a predator or not
	bool isPredatorOnScreen = false; //check if there is any predator on screen. This is because I think it looks better when everyones rotation speed is a little higher when a predator is on screen

	std::string boidType; //will hold the type of boid (blue, gree, predator, etc)
	std::string currTracking = "none";

	sf::Sprite sprite;//the individual sprite and its rect for animation
	sf::IntRect rectSprite;

	sf::Clock animPreyClock;	//all the clocks so we dont have to worry about it performing different with different framerates
	sf::Clock animPredatorClock;
	sf::Clock rotClock;
	sf::Clock rotSpeedClock;
	sf::Clock mvmtClock;
	
	sf::Vector2f position;	//will have the x and y position
	sf::Vector2f direction; //will have the weight of x and y direction in radians. rotation is in degrees, direction is in radians
	sf::Vector2f velocity;  //will have velocity (speed and direction) of x and y

	int windowWidth;
	int windowHeight; //these are so we can change window size and still have the boids behave the same

public:
	//----------------------CONSTRUCTOR----------------------
	Boid(std::string boidColor, sf::Texture& thatTexture);	//have to pass texture as a parameter, otherwise, we get the "white square problem".

	//------------SETTERS AND GETTERS------------
	void setPosition(float xPos, float yPos);
	void setRotation(float rot);
	sf::Vector2f getPosition();
	void setWindow(int width, int height);
	void setGameSpeed(float gameSpeed);
	void setRandomRotationDirectionVelocity(); //will give the boid a random rotation, and update its direction and velocity accordingly
	void setAttributesBasedOnType(std::string type); //sets the boids speed of mvmt, rotation, animation, etc. based on its type 
	void setSprite(sf::Texture& thatTexture); //sets sprites texture and the sprites rect
	void setIsPredatorOnScreen(bool isPredOnScreen); //sets the "isPredatorOnScreen" variable

	//--------------UPDATE BOID FUNCTIONS---------------
	//general update function. will call all update functions to update position, animation, rotation, etc (based on its variables that should have been changed from
	//either callBoidRules or callPredatorRules), then will draw it to the window.
	void updateBoid(sf::RenderWindow& window, bool isPredOnScreen);
	void updatePredatorAnim();
	void updatePreyAnim();
	void updatePosition();
	void updateRotation();
	void updateVelocity();
	void updateDirection();
	void updatePreyRectSprite();
	void updatePredatorRectSprite();
	void updateGameSpeed(float gameSpeed); //update the boids game speed

	//--------BOUND CHECKING-------------
	sf::Vector2f boundCheckBorder(); //bound checking when border is on (hard bound checking, not allowed to go out)
	sf::Vector2f boundCheckNoBorder(); //bound checking when border is off (soft bound checking, can go out and will slowly come back)

	//--------REPULSION CHECKING---------
	sf::Vector2f repulsionCheck(std::vector<Repulsion>& repulsions); //will check if any repulsions are nearby...if so, update boid accordingly

	//-----GET NEARBY BOIDS---------------
	std::vector<Boid> getNearbyBoids(std::vector<Boid>& boids, float desiredDis); //will return a vector of nearby boids within the desired distance

	//----------------THE 3 RULES------------------
	sf::Vector2f separation(std::vector<Boid>& nearbyBoids, float desiredDis); //SEPARATION - make sure boids keep a distance from each other (rule 1)
	sf::Vector2f cohesion(std::vector<Boid>& nearbyBoids); //COHESION - make sure boids move toward avg center of mass of nearby boids (rule 2)
	sf::Vector2f allignment(std::vector<Boid>& nearbyBoids); //ALLIGNMENT - make sure boids have average heading direction of nearby boids (rule 3)

	//---------------CALL RULES---------------------
	//will call the three rules on the boid, with the correct behavior. Will also check for predators, repulsions, and border. Will update its desiredRotation and mvmt, rotation, and animation speeds accordingly
	void callBoidRules(std::vector<Boid>& boids, std::vector<Boid>& predators, std::vector<Repulsion> repulsions,Rules& rules, Behavior& behavior); 
	//will call the rules for the predators action. Will check for nearby prey, repulsions, and border. Will update its desiredRotation and mvmt, rotation, and animation speeds accordingly
	void callPredatorRules(std::vector<Boid>& blueBoids, std::vector<Boid>& DBlueBoids, std::vector<Boid>& pinkBoids, std::vector<Boid>& yellowBoids, std::vector<Boid>& predators, std::vector<Repulsion> repulsions);

	//-------------PREY RULE HELPERS---------------------
	sf::Vector2f scatter(std::vector<Boid>& nearbyPredators); //will update boid to scatter away from nearby predators when called
	void updatePreyAttributes(float distance); //updates preys mvmt speed, rotation speed, animation speed when being chased

	//------------PREDATOR RULE HELPERS------------------
	sf::Vector2f centerOfMassPostition(std::vector<Boid>& nearbyBoids); //returns center of mass of all nearby prey
	void updatePredatorAttributes(float distance); //updates predator rotationspeed , mvmt speed, and animation speed when it is chasing prey
	std::vector<Boid> whichBoidToChase(std::vector<Boid>& blueBoids, std::vector<Boid>& DBlueBoids, std::vector<Boid>& yellowBoids, std::vector<Boid>& pinkBoids); //given the blue-white boids, find which boid color to chase after

};

#endif  // BOIDS_H