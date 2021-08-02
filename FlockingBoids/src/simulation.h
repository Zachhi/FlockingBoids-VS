#ifndef SIMULATION_H
#define SIMULATION_H
#include "structures.h"

class Simulation {
private:
	//set custom window dimensions here if wanted
	int windowWidth = 3840;		//laptop -> 2880x1800 (for my personal laptop and monitor, these are the sizes that hit fullscreen)
	int windowHeight = 2035;	//monitor -> 3840x2035 (or, just make the style fullscreen)

	sf::RenderWindow window; //sf::Style::Fullscreen for fullscreen, sf::Style::Default for custom window size. if we want it on an external monitor, sfml does not suport fullscreen
	sf::ContextSettings settings; //settings variable so we can add anti-aliasing later
	
	//not going to use a structure on the boid vectors, as these will be large vectors and we would have to constantly
	//access the structure in inner loops, decreasing performance by a signifigant amount
	std::vector<Boid> blueBoids; //Prey vectors to store the preys
	std::vector<Boid> DBlueBoids;
	std::vector<Boid> pinkBoids;
	std::vector<Boid> yellowBoids;
	std::vector<Boid> whiteBoids;
	std::vector<Boid> predators; //predator vector to store the predators
	std::vector<Repulsion> repulsions; //repulsion vector to store the repulsions

	Textures textures; //struct of textures for each texture we need: blue boid, repulsions, etc.
	Counts counts; // struct to help keep track of the count of the different objects
	Behavior behavior; //struct of the behavior the boids should follow
	Rules whichRules; //struct that helps us keep track of which rules are currently active or not
	Borders borders; //struct to keep track of the 4 borders
	Music music;  //struct of all the music we can play
	SoundEffects soundEffects;  //struct of all the sound effects we need
	Colors colors; //struct of all the colors we need
	simulationTexts texts; //struct of all the different text boxes we need

	int currBoidType = 0; //helps keep track of the current boid type (blue, pink, yellow, etc.) we are placing......0 is Blue, 1 is Dark Blue, 2 is Pink, 3 is Yellow, 4 is White
	int currMusic = 0; //keeps track of which music track is currently playing....0 for claire, 1 for ameilie, 2 for gymnopeide, 3 for fairy fountain

	bool isPredator = false; //helps us know if we are currently placing a predator or prey
	bool isHud = true; //tracks if we want to show the HUD (all the text objects) or not
	bool isControls = false; //tracks if we want to show controls or not
	bool isWaterSound = false; //tracks if we want to play water stream sound or not

	float prevGameSpeed = 1.0; //helps control game speed so we can run at anywhere from [.25x, 2.00x] speed
	float currGameSpeed = 1.0;

	sf::Clock fpsClock; //helps track the current fps so we can display it
	sf::Clock fpsTextClock;

	sf::Font font; //the font we will use

public:
	//-------CONTRUCTOR AND RUN-----------------------
	Simulation(); //contructor
	void initialize(); //initialize needed values
	void runSimulation(); //run the simulation with this function

	//--------FUNCTIONS HELPING WITH USER INPUT-----------------
	void checkForUserInput(); //check for all user input and update variables accordingly
	void addNewBoid(int posx, int posy); //to help with creating new boids
	void addTwoNewBoids(); //help tp add two new boids when x is clicked
	void repulsionHelp(int posx, int posy); //help to create or delete a repulsion
	void soundEffectManager(sf::Sound& soundEffect); 	//to help with managing the sound effects
	void clearAll(); //clear all objects
	void clearCurrent(); //clear current object
	void generalToggle(bool& toggable); //general toggling for changing a true to a false and viceVersa
	void togglePredator(); //toggle predator on or off
	void toggleRuleHelp(bool& rule, sf::Text& ruleText); //help with toggling rules on or off
	void cycleFlockPattern(); //cycle to next flocking pattern
	void cycleBoid(int cycle); //help cycle through which boid the user is currently placing
	void cycleMusic(); //help cycle through mucis

	//-----------FUNCTIONS HELPING WITH RUNNING THE ACTUAL PROGRAM-----------------
	void updateFps(); //to help update the fps every loop
	void callRules(); //calls the rules for prey and predators (determines which direction, velocity, rotation, and position they should update to later on in updateBoids())
	void updateGameSpeed(); //updates the game speed for all objects
	void updateObjects(); //updates each boids position, direction, velocity, rotation, and animation. Then draws the boid to the window. Also updates and draws repulsions
	void updateBoidCountText(); //update the display of boid counts
	void updateGameSpeedText(); //update the display of game speed
	void updateFlockingPatternText(); //update the display of the flocking pattern
	void drawHUD(); //draw the HUD
	void drawBorder(); //draw the borders
};
#endif //SIMULATION_H