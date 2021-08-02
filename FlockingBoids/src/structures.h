#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h> 
#include <math.h>
#include "repulsions.h"
#include "boids.h"

//all structs that simulation.h uses

//struct of all the boid counts
struct Counts
{
	int boidBlueCount = 0;
	int boidDBlueCount = 0;
	int boidPinkCount = 0;
	int boidYellowCount = 0;
	int boidWhiteCount = 0;
	int boidPredatorCount = 0;
};
//struct of textures for every object 
struct Textures
{
	sf::Texture boidTextureBlue;
	sf::Texture boidTextureDBlue;
	sf::Texture boidTexturePink;
	sf::Texture boidTextureYellow;
	sf::Texture boidTextureWhite;
	sf::Texture boidTexturePredator;
	sf::Texture textureRepulsion;
};
//struct of boid behavior
struct Behavior
{
	//the coefficients of the 3 rules. We change the flocking pattern by editing these coefficients, as well as the sight range and rule1distance
	float rule1Ratio = 0.8f;
	float rule2Ratio = 0.45f;
	float rule3Ratio = 0.9f;
	int rule1Distance = 60; // how far boids will keep distance while flocking
	int sightRange = 110; //how far boids can detect each other
	int whichPattern = 0; //tracks which flocking pattern is currently in effect.....0 for normal, 1 for close together, 2 for far apart
	bool isBorder = true; //tracks if borders are on or off
};
//struct tracking the active rules
struct Rules
{
	bool separationBool = true; //rule 1
	bool cohesionBool = true; //rule 2
	bool allignmentBool = true; //rule 3
};
//struct of all the music
struct Music
{
	//all music here
	sf::Music claireDeLune;
	sf::Music ameilie;
	sf::Music gymnopeide;
	sf::Music fairyFountain;
};
//struct of all the sound effects 
struct SoundEffects
{
	//all sound effects here
	sf::SoundBuffer smallSplashBuff;
	sf::Sound smallSplash;
	sf::Sound largeSplash;
	sf::SoundBuffer waterSoundBuff;
	sf::Sound waterSound;
};
//struct of borders
struct Borders
{
	//just 4 rectandles that will hug the ends of the screen
	sf::RectangleShape topBorder;
	sf::RectangleShape bottomBorder;
	sf::RectangleShape leftBorder;
	sf::RectangleShape rightBorder;
};
//struct of the colors we need
struct Colors
{
	sf::Color blueBoidColor;
	sf::Color darkBlueBoidColor;
	sf::Color greenBoidColor;
	sf::Color pinkBoidColor;
	sf::Color yellowBoidColor;
	sf::Color whiteBoidColor;
	sf::Color predatorColor;
	sf::Color bgColor; //background color
	sf::Color borderColor; //border color
};
//struct of all the texts we need
struct simulationTexts
{
	//text objects to display the counts
	sf::Text boidBlueCountText;
	sf::Text boidDBlueCountText;
	sf::Text boidPinkCountText;
	sf::Text boidYellowCountText;
	sf::Text boidWhiteCountText;
	sf::Text boidPredatorCountText;
	//text objects to display the 3 rules
	sf::Text rules;
	sf::Text rule1;
	sf::Text rule2;
	sf::Text rule3;
	//text objects to display the current object user is placing
	sf::Text currObjectType;
	sf::Text currObject;
	//text object to display controls when controls are shown
	sf::Text simulationControls;
	//text object to display how to open controls
	sf::Text openControls;
	//text object to display the game speed
	sf::Text gameSpeedText;
	//text object to display the flocking type
	sf::Text flockingTypeText;
	//text object to display the fps
	sf::Text fpsText;
};
//struct 

#endif //STRUCTURES_H