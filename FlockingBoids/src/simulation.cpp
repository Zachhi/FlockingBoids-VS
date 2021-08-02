#define _USE_MATH_DEFINES 
#include "simulation.h"

//constructor
Simulation::Simulation() :
	window(sf::VideoMode(windowWidth, windowHeight), "Flocking Boids", sf::Style::Fullscreen) {}
//initialize the needed values
void Simulation::initialize()
{
	//set a frame limit 
	window.setFramerateLimit(60);
	//this forces the frame rate to stay relatively near 60. 
	window.setVerticalSyncEnabled(true);
	//update window width and height (if it is in fullscreen mode, we need the new values)
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;

	//antialiasing will make rotations more smooth, will also make the sprites less pixelated
	settings.antialiasingLevel = 8;

	
	//set texture for preys
	textures.boidTextureBlue.loadFromFile("FlockingBoids/resources/sprites/boidBlue.png"); //67x26
	textures.boidTextureBlue.setSmooth(true);	//set smooth will make the sprites less pixelated
	textures.boidTextureDBlue.loadFromFile("FlockingBoids/resources/sprites/boidBlueish.png");
	textures.boidTextureDBlue.setSmooth(true);
	textures.boidTexturePink.loadFromFile("FlockingBoids/resources/sprites/boidPink.png");
	textures.boidTexturePink.setSmooth(true);
	textures.boidTextureYellow.loadFromFile("FlockingBoids/resources/sprites/boidYellow.png");
	textures.boidTextureYellow.setSmooth(true);
	textures.boidTextureWhite.loadFromFile("FlockingBoids/resources/sprites/boidWhite.png");
	textures.boidTextureWhite.setSmooth(true);
	//set texture for predator
	textures.boidTexturePredator.loadFromFile("FlockingBoids/resources/sprites/boidPredator.png");
	textures.boidTexturePredator.setSmooth(true);
	//set texture for repulsions
	textures.textureRepulsion.loadFromFile("FlockingBoids/resources/sprites/repulsionRed.png");
	textures.textureRepulsion.setSmooth(true);

	//set font
	font.loadFromFile("FlockingBoids/resources/fonts/mainFont.otf");

	//set music
	music.claireDeLune.openFromFile("FlockingBoids/resources/music/claireDeLune.wav");
	music.claireDeLune.setLoop(true);	//looping will make it loop to beggining when the music/sound effect ends
	music.ameilie.openFromFile("FlockingBoids/resources/music/ameilie.wav");
	music.ameilie.setLoop(true);
	music.gymnopeide.openFromFile("FlockingBoids/resources/music/gymnopeide.wav");
	music.gymnopeide.setLoop(true);
	music.fairyFountain.openFromFile("FlockingBoids/resources/music/fairyFountain.wav");
	music.fairyFountain.setLoop(true);
	music.claireDeLune.play();	//play claireDeLune right when program starts

	//set sound effects
	soundEffects.smallSplashBuff.loadFromFile("FlockingBoids/resources/soundEffects/smallSplash.wav");
	soundEffects.smallSplash.setBuffer(soundEffects.smallSplashBuff);
	soundEffects.smallSplash.setVolume(15.0f);
	soundEffects.largeSplash.setBuffer(soundEffects.smallSplashBuff);
	soundEffects.largeSplash.setVolume(40.0f);
	soundEffects.waterSoundBuff.loadFromFile("FlockingBoids/resources/soundEffects/waterStream.wav");
	soundEffects.waterSound.setBuffer(soundEffects.waterSoundBuff);
	soundEffects.waterSound.setVolume(45.0f);
	soundEffects.waterSound.setLoop(true);
	
	//initialize color values
	colors.blueBoidColor = sf::Color(0, 152, 204);
	colors.darkBlueBoidColor = sf::Color(0, 76, 196);
	colors.greenBoidColor = sf::Color(0, 230, 0);
	colors.pinkBoidColor = sf::Color(190, 0, 234);
	colors.yellowBoidColor = sf::Color(255, 232, 56);
	colors.whiteBoidColor = sf::Color(217, 217, 217);
	colors.predatorColor = sf::Color(204, 0, 0);
	colors.borderColor = sf::Color(140, 137, 137);
	colors.bgColor = sf::Color::Black;

	//set the text to display prey and predator counts
	texts.boidBlueCountText.setCharacterSize(20);
	texts.boidBlueCountText.setPosition(10, windowHeight - 205);
	texts.boidBlueCountText.setFont(font);
	texts.boidBlueCountText.setFillColor(colors.blueBoidColor);
	texts.boidBlueCountText.setString("Blue Count: " + std::to_string(counts.boidBlueCount));
	texts.boidBlueCountText.setStyle(sf::Text::Regular);

	texts.boidDBlueCountText.setCharacterSize(20);
	texts.boidDBlueCountText.setPosition(10, windowHeight - 170);
	texts.boidDBlueCountText.setFont(font);
	texts.boidDBlueCountText.setFillColor(colors.darkBlueBoidColor);
	texts.boidDBlueCountText.setString("DBlue Count: " + std::to_string(counts.boidDBlueCount));
	texts.boidDBlueCountText.setStyle(sf::Text::Regular);

	texts.boidPinkCountText.setCharacterSize(20);
	texts.boidPinkCountText.setPosition(10, windowHeight - 135);
	texts.boidPinkCountText.setFont(font);
	texts.boidPinkCountText.setFillColor(colors.pinkBoidColor);
	texts.boidPinkCountText.setString("Pink Count: " + std::to_string(counts.boidPinkCount));
	texts.boidPinkCountText.setStyle(sf::Text::Regular);

	texts.boidYellowCountText.setCharacterSize(20);
	texts.boidYellowCountText.setPosition(10, windowHeight - 100);
	texts.boidYellowCountText.setFont(font);
	texts.boidYellowCountText.setFillColor(colors.yellowBoidColor);
	texts.boidYellowCountText.setString("Yellow Count: " + std::to_string(counts.boidYellowCount));
	texts.boidYellowCountText.setStyle(sf::Text::Regular);

	texts.boidWhiteCountText.setCharacterSize(20);
	texts.boidWhiteCountText.setPosition(10, windowHeight - 65);
	texts.boidWhiteCountText.setFont(font);
	texts.boidWhiteCountText.setFillColor(colors.whiteBoidColor);
	texts.boidWhiteCountText.setString("White Count: " + std::to_string(counts.boidWhiteCount));
	texts.boidWhiteCountText.setStyle(sf::Text::Regular);

	texts.boidPredatorCountText.setCharacterSize(20);
	texts.boidPredatorCountText.setPosition(10, windowHeight - 30);
	texts.boidPredatorCountText.setFont(font);
	texts.boidPredatorCountText.setFillColor(colors.predatorColor);
	texts.boidPredatorCountText.setString("Predator Count: " + std::to_string(counts.boidPredatorCount));
	texts.boidPredatorCountText.setStyle(sf::Text::Regular);

	//set border sizes
	borders.topBorder.setSize(sf::Vector2f(windowWidth, 5.f));
	borders.bottomBorder.setSize(sf::Vector2f(windowWidth, 5.f));
	borders.leftBorder.setSize(sf::Vector2f(5.f, windowHeight));
	borders.rightBorder.setSize(sf::Vector2f(5.f, windowHeight));

	//set the 4 borders position and color
	borders.topBorder.setFillColor(colors.borderColor);
	borders.topBorder.setPosition(0, 0);
	borders.bottomBorder.setFillColor(colors.borderColor);
	borders.bottomBorder.setPosition(0, windowHeight - 5);
	borders.leftBorder.setFillColor(colors.borderColor);
	borders.leftBorder.setPosition(0, 0);
	borders.rightBorder.setFillColor(colors.borderColor);
	borders.rightBorder.setPosition(windowWidth - 5, 0);

	//set the text to display the the 3 rules to see if they are on or off
	texts.rules.setCharacterSize(20);
	texts.rules.setPosition(windowWidth - 195, 10);
	texts.rules.setFont(font);
	texts.rules.setFillColor(sf::Color::White);
	texts.rules.setString("Separation:\nCohesion:\nAllignment:");
	texts.rules.setStyle(sf::Text::Regular);

	texts.rule1.setCharacterSize(20);
	texts.rule1.setPosition(windowWidth - 45, 10);
	texts.rule1.setFont(font);
	texts.rule1.setFillColor(colors.greenBoidColor);
	texts.rule1.setString("ON");
	texts.rule1.setStyle(sf::Text::Regular);

	texts.rule2.setCharacterSize(20);
	texts.rule2.setPosition(windowWidth - 65, 37);
	texts.rule2.setFont(font);
	texts.rule2.setFillColor(colors.greenBoidColor);
	texts.rule2.setString("ON");
	texts.rule2.setStyle(sf::Text::Regular);

	texts.rule3.setCharacterSize(20);
	texts.rule3.setPosition(windowWidth - 45, 64);
	texts.rule3.setFont(font);
	texts.rule3.setFillColor(colors.greenBoidColor);
	texts.rule3.setString("ON");
	texts.rule3.setStyle(sf::Text::Regular);

	//set the text to display the current object user is placing
	texts.currObjectType.setCharacterSize(20);
	texts.currObjectType.setPosition(windowWidth - 140, windowHeight - 30);
	texts.currObjectType.setFont(font);
	texts.currObjectType.setFillColor(colors.blueBoidColor);
	texts.currObjectType.setString("Blue boid");
	texts.currObjectType.setStyle(sf::Text::Regular);

	texts.currObject.setCharacterSize(20);
	texts.currObject.setPosition(windowWidth - 330, windowHeight - 30);
	texts.currObject.setFont(font);
	texts.currObject.setFillColor(sf::Color::White);
	texts.currObject.setString("Current Object:");
	texts.currObject.setStyle(sf::Text::Regular);

	//set text to display the control menu
	texts.simulationControls.setCharacterSize(20);
	texts.simulationControls.setPosition(10, 10);
	texts.simulationControls.setFont(font);
	texts.simulationControls.setFillColor(sf::Color::White);
	texts.simulationControls.setString("CONTROLS:	\nLeft Mouse: Spawn current type of object (boid or predator)\nRight Mouse: Spawn/Delete Repulsion\n1: Toggle rule 1\n2: Toggle rule 2\n3: Toggle rule 3\nRight Arrow: Next boid color\nLeft Arrow: Previous boid color\nP: Toggle current object to Predator and back\nSpace: Spawn 20 boids\nC: Clear everything\nV: Clear Current Boid Type\nR: Clear Repulsions\nB: Toggle Borders\nTab: Cycle Flocking Pattern\nUp Arrow: Increase Game Speed\nDown Arrow: Decrease Game Speed\nEscape: Exit Program\nControl: Hide HUD\nN: Next Song\nO: Draw Circle of Repulsions\nI: Change Type of Circle");
	texts.simulationControls.setStyle(sf::Text::Regular);

	//set text to display how to open control menu
	texts.openControls.setCharacterSize(18);
	texts.openControls.setPosition(10, 10);
	texts.openControls.setFont(font);
	texts.openControls.setFillColor(sf::Color::White);
	texts.openControls.setString("shift for controls");
	texts.openControls.setStyle(sf::Text::Regular);

	//set text to display gameSpeed
	texts.gameSpeedText.setCharacterSize(15);
	texts.gameSpeedText.setPosition(windowWidth - 170, 90);
	texts.gameSpeedText.setFont(font);
	texts.gameSpeedText.setFillColor(colors.whiteBoidColor);
	texts.gameSpeedText.setStyle(sf::Text::Regular);
	texts.gameSpeedText.setString("Game Speed: 1.0x");

	//set text to display current flocking pattern
	texts.flockingTypeText.setCharacterSize(15);
	texts.flockingTypeText.setPosition(windowWidth - 160, 110);
	texts.flockingTypeText.setFont(font);
	texts.flockingTypeText.setFillColor(colors.whiteBoidColor);
	texts.flockingTypeText.setStyle(sf::Text::Regular);
	texts.flockingTypeText.setString("Flocking Type: 1");

	//set text to display current fps
	texts.fpsText.setCharacterSize(15);
	texts.fpsText.setPosition(windowWidth - 80, 130);
	texts.fpsText.setFont(font);
	texts.fpsText.setFillColor(colors.whiteBoidColor);
	texts.fpsText.setString("FPS: 100");
	texts.fpsText.setStyle(sf::Text::Regular);
}
//initialize and run the simulation with this function
void Simulation::runSimulation()
{
	//initialize all variables declared above
	initialize();

	//while game is running...
	while (window.isOpen())
	{
		updateFps(); //update the frames at the start of each loop

		checkForUserInput(); //check all user input here, and take action accordingly

		//clear window -> update objects -> draw objects -> display window
		window.clear(colors.bgColor); //clear and set background color

		//important: callRules must be called first. This will tell the boids where they desire to go based off of every other boids current position, as well as the external factors
		// such as coefficients, sight range, borders, rules, etc.
		//the we must update game speed before updating the boids, so we know how fast/slow they should move, rotate, and animate before updating
		//finally, we update each boid. important we call the rules for each boid before updating a single boid, otherwise boids will calculate their next mvmt based off a boid already ahead by one update
		callRules(); //call the rules for each individual prey and predator

		updateGameSpeed(); //update game speed for all objects here
		updateObjects(); //update each boid and repulsion after calling rules. Then draw them to the window

		updateBoidCountText(); //update the different boids counts display
		updateGameSpeedText(); //update game speed display
		updateFlockingPatternText(); //update flocking type display

		drawHUD(); //draw the HUD if bool value "showHUD" is true
		drawBorder(); //draw the border if bool value "isBorder" is true

		window.display(); //display final results 
	}
}

//--------FUNCTIONS HELPING WITH USER INPUT------------------
//check for all user input and update variables accordingly
void Simulation::checkForUserInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		//if the x is clicked on top right, exit program
		if (event.type == sf::Event::Closed)
			window.close();

		//if escape is pressed, exit program
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			window.close();

		//if left mouse is pressed, make a boid where clicked with random direction
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			int posx = event.mouseButton.x;
			int posy = event.mouseButton.y;

			//create the new boid with the right type
			addNewBoid(posx, posy, -1); //-1 is for a random rotation

			//update sound effects accordingly
			soundEffectManager(soundEffects.smallSplash);
		}

		//if space is pressed, create 20 boids at random positions and directions
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		{
			for (int i = 0; i < 20; i++)
			{
				int posx = rand() % (windowWidth - 100) + 100;
				int posy = rand() % (windowHeight - 100) + 100;

				//create the new boid with the right type
				addNewBoid(posx, posy, -1); //-1 is for a random rotation

				//update sound effects accordingly
				soundEffectManager(soundEffects.largeSplash);
			}
		}

		//if X is clicked, make two boids that will face each other
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::X)
		{
			//add two boids facing each other
			addNewBoid(800, 800, 180);
			addNewBoid(1400, 800, 0);
			//update sound effects accordingly
			soundEffectManager(soundEffects.smallSplash);
		}

		//if right mouse is pressed, make a repulsion where clicked, or delete a repulsion if a repulsion exists where clicked
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			//retrieve position of mouse
			int posx = event.mouseButton.x;
			int posy = event.mouseButton.y;

			//create or delete repulsion
			repulsionHelp(posx, posy);
		}

		//toggle theSseparation rule with 1
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
			toggleRuleHelp(whichRules.separationBool, texts.rule1); //toggle rule 1

		//toggle the Cohesion rule with 2
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
			toggleRuleHelp(whichRules.cohesionBool, texts.rule2); //toggle rule 2

		//toggle the Allignment rule with 3
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num3)
			toggleRuleHelp(whichRules.allignmentBool, texts.rule3); //toggle rule 3

		//if C is pressed, clear everything
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C)
			clearAll(); //clear everything

		//if V is pressed, clear every current object
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::V)
			clearCurrent(); //clear current object

		//if R is pressed, clear every repulsion
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
			repulsions.clear();

		//if right arrow is pressed, cycle to the next boid color
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
			cycleBoid(1); //cycle through with +1

		//if left arrow is pressed, cycle to the previous boid color
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
			cycleBoid(-1); //cycle through with -1

		//toggle isPredator if "p" is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P)
			togglePredator(); //toggle predator on or off

		//toggle controls menu when shift is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
			generalToggle(isControls);

		//toggle borders when b is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
			generalToggle(behavior.isBorder);

		//toggle different flocking behavior when tab is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab)
			cycleFlockPattern(); //cycle to the next flock pattern

		//increase game speed when up arrow is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
		{
			if (currGameSpeed < 2.5)
				currGameSpeed += 0.25;
		}

		//decrease game speed when down arrow is clicked
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
		{
			if (currGameSpeed > 0.25)
				currGameSpeed -= 0.25;
		}

		//if control is clicked, toggle the HUD
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
			generalToggle(isHud);

		//if N is clicked, go to next song
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::N)
			cycleMusic(); //cycle to the next song

		//if O is clicked, draw a circle of repulsions
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O)
			drawCircleRepulsions(circleType.radius, circleType.incValue);

		//if I is clicked, change type of circle repulsion
		else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::I)
			cycleCircle();
	}
}
//to help with creating new boids
void Simulation::addNewBoid(int posx, int posy, int rot)
{
	//if IsPredator, make a predator. else make a boid with the correct color
	if (isPredator)
	{
		Boid newBoid("predator", textures.boidTexturePredator);	//create the boid
		newBoid.setWindow(windowWidth, windowHeight); //set its window dimesnions
		newBoid.setPosition(posx, posy); //set its position
		newBoid.setGameSpeed(currGameSpeed); //set its gamespeed
		if (rot != -1)
			newBoid.setRotation(rot);
		predators.push_back(newBoid); //add to the correct vector
		counts.boidPredatorCount += 1; //update its count
		isPredatorOnScreen = true;
	}
	else if (currBoidType == 0)
	{
		Boid newBoid("blue", textures.boidTextureBlue);
		newBoid.setWindow(windowWidth, windowHeight);
		newBoid.setPosition(posx, posy);
		newBoid.setGameSpeed(currGameSpeed);
		if (rot != -1)
			newBoid.setRotation(rot);
		blueBoids.push_back(newBoid);
		counts.boidBlueCount += 1;
	}
	else if (currBoidType == 1)
	{
		Boid newBoid("green", textures.boidTextureDBlue);
		newBoid.setWindow(windowWidth, windowHeight);
		newBoid.setPosition(posx, posy);
		newBoid.setGameSpeed(currGameSpeed);
		if (rot != -1)
			newBoid.setRotation(rot);
		DBlueBoids.push_back(newBoid);
		counts.boidDBlueCount += 1;
	}
	else if (currBoidType == 2)
	{
		Boid newBoid("pink", textures.boidTexturePink);
		newBoid.setWindow(windowWidth, windowHeight);
		newBoid.setPosition(posx, posy);
		newBoid.setGameSpeed(currGameSpeed);
		if (rot != -1)
			newBoid.setRotation(rot);
		pinkBoids.push_back(newBoid);
		counts.boidPinkCount += 1;
	}
	else if (currBoidType == 3)
	{
		Boid newBoid("yellow", textures.boidTextureYellow);
		newBoid.setWindow(windowWidth, windowHeight);
		newBoid.setPosition(posx, posy);
		newBoid.setGameSpeed(currGameSpeed);
		if (rot != -1)
			newBoid.setRotation(rot);
		yellowBoids.push_back(newBoid);
		counts.boidYellowCount += 1;
	}
	else
	{
		Boid newBoid("white", textures.boidTextureWhite);
		newBoid.setWindow(windowWidth, windowHeight);
		newBoid.setPosition(posx, posy);
		newBoid.setGameSpeed(currGameSpeed);
		if (rot != -1)
			newBoid.setRotation(rot);
		whiteBoids.push_back(newBoid);
		counts.boidWhiteCount += 1;

	}
}
//help to create or delete a repulsion
void Simulation::repulsionHelp(int posx, int posy)
{
	bool isDelete = false;
	for (int i = 0; i < repulsions.size(); i++)
	{
		int posXLeftOffset = repulsions[i].getPosition().x - 15;
		int posXRightOffset = repulsions[i].getPosition().x + 15;
		int posYTopOffset = repulsions[i].getPosition().y - 15;
		int posYBottomOffset = repulsions[i].getPosition().y + 15;

		if ((posx > posXLeftOffset && posx < posXRightOffset) && (posy < posYBottomOffset && posy > posYTopOffset)) //if clicked on a repulsion, delete said repulsion
		{
			isDelete = true;
			repulsions.erase(repulsions.begin() + i);
			if (i > 0)
				i -= 1;
		}

		if ((posx > posXLeftOffset - 20 && posx < posXRightOffset + 20) && (posy < posYBottomOffset + 20 && posy > posYTopOffset - 20)) // if clicked within 25 pixels of a repulsion, do nothing(dont delete repulsion, dont spawn repulsion)
			isDelete = true;
	}

	if (!isDelete) //if no repulsion had to be deleted, and area clicked is valid, then draw one where clicked
	{
		Repulsion newRepulsion(posx, posy, textures.textureRepulsion);
		repulsions.push_back(newRepulsion);
	}
}
//draw a circle of repulsions
void Simulation::drawCircleRepulsions(int radius, float incVal)
{
	sf::Vector2f center;
	center.x = windowWidth / 2; 
	center.y = windowHeight / 2;

	//to get points on a circle depending on its center and radius
	//x = xCenter + radius * cos(angle)
	//y = yCenter + radius * sin(angle)
	for (float i = 1; i < 361; i += incVal)
	{
		float rad = i * (M_PI / 180);
		float currX = center.x + (radius * cos(rad));
		float currY = center.y + (radius * sin(rad));
		repulsionHelp(currX, currY);
	}
}
//to help with managing the sound effects
void Simulation::soundEffectManager(sf::Sound& soundEffect)
{
	//this is for either the small or large splash
	soundEffect.stop();
	soundEffect.setPlayingOffset(sf::seconds(0.22f));
	soundEffect.play();
	//this helps keep the water sound playing or stopped, depending on if there are boids on screen
	if (!isWaterSound)
	{
		isWaterSound = true;
		soundEffects.waterSound.play();
	}
}
//clear all objects
void Simulation::clearAll()
{
	DBlueBoids.clear();
	blueBoids.clear();
	pinkBoids.clear();
	yellowBoids.clear();
	whiteBoids.clear();
	predators.clear();
	repulsions.clear();

	counts.boidDBlueCount = 0;
	counts.boidBlueCount = 0;
	counts.boidYellowCount = 0;
	counts.boidPinkCount = 0;
	counts.boidWhiteCount = 0;
	counts.boidPredatorCount = 0;
	soundEffects.waterSound.stop();
	isWaterSound = false;
	isPredatorOnScreen = false;
}
//clear current object
void Simulation::clearCurrent()
{
	if (isPredator) //if predator
	{
		predators.clear();
		counts.boidPredatorCount = 0;
		isPredatorOnScreen = false;
	}
	else if (currBoidType == 0) //if blue
	{
		blueBoids.clear();
		counts.boidBlueCount = 0;
	}
	else if (currBoidType == 1) //if green
	{
		DBlueBoids.clear();
		counts.boidDBlueCount = 0;
	}
	else if (currBoidType == 2) //if pink
	{
		pinkBoids.clear();
		counts.boidPinkCount = 0;
	}
	else if (currBoidType == 3) //if yellow
	{
		yellowBoids.clear();
		counts.boidYellowCount = 0;
	}
	else // if white
	{
		whiteBoids.clear();
		counts.boidWhiteCount = 0;
	}
	if (counts.boidWhiteCount == 0 && counts.boidBlueCount == 0 && counts.boidYellowCount == 0 && counts.boidPinkCount == 0 && counts.boidDBlueCount == 0 && counts.boidPredatorCount == 0)
	{
		soundEffects.waterSound.stop();
		isWaterSound = false;
	}
}
//general toggling for changing a true to a false and viceVersa
void Simulation::generalToggle(bool& toggable)
{
	if (toggable)
		toggable = false;
	else
		toggable = true;
}
//toggle predator on or off
void Simulation::togglePredator()
{
	if (isPredator)
	{
		isPredator = false;
		if (currBoidType == 0)
		{
			texts.currObjectType.setString("Blue boid");
			texts.currObjectType.setFillColor(colors.blueBoidColor);
		}
		else if (currBoidType == 1)
		{
			texts.currObjectType.setString("DBlue boid");
			texts.currObjectType.setFillColor(colors.darkBlueBoidColor);
		}
		else if (currBoidType == 2)
		{
			texts.currObjectType.setString("Pink boid");
			texts.currObjectType.setFillColor(colors.pinkBoidColor);
		}
		else if (currBoidType == 3)
		{
			texts.currObjectType.setString("Yellow boid");
			texts.currObjectType.setFillColor(colors.yellowBoidColor);
		}
		else
		{
			texts.currObjectType.setString("White boid");
			texts.currObjectType.setFillColor(colors.whiteBoidColor);
		}
	}
	else if (!isPredator)
	{
		isPredator = true;
		texts.currObjectType.setString("Predator");
		texts.currObjectType.setFillColor(colors.predatorColor);
	}
}
//help with toggling rules on or off
void Simulation::toggleRuleHelp(bool& rule, sf::Text& ruleText)
{
	if (rule)
	{
		rule = false;
		ruleText.setFillColor(colors.predatorColor);
		ruleText.setString("OFF");
	}
	else
	{
		rule = true;
		ruleText.setFillColor(colors.greenBoidColor);
		ruleText.setString("ON");
	}
}
//cycle to next flocking pattern
void Simulation::cycleFlockPattern()
{
	behavior.whichPattern += 1;
	if (behavior.whichPattern == 3)
		behavior.whichPattern = 0;

	if (behavior.whichPattern == 0) //realistic, good looking, average
	{
		behavior.rule1Ratio = 0.8f;
		behavior.rule2Ratio = 0.45f;
		behavior.rule3Ratio = 0.9f;
		behavior.rule1Distance = 60;
		behavior.sightRange = 110;
	}
	else if (behavior.whichPattern == 1) //tighter together and nice visual
	{
		behavior.rule1Ratio = 0.6f;
		behavior.rule2Ratio = 0.09f;
		behavior.rule3Ratio = 0.9f;
		behavior.rule1Distance = 40; //60
		behavior.sightRange = 100;
	}
	else if (behavior.whichPattern == 2) //very far apart, easy to breakup. long range
	{
		behavior.rule1Ratio = 16.5f;
		behavior.rule2Ratio = 4.5f;
		behavior.rule3Ratio = 50.5f;
		behavior.rule1Distance = 85;
		behavior.sightRange = 130; //185


	}
}
//help cycle through which boid the user is currently placing
void Simulation::cycleBoid(int cycle)
{
	//just add or subtract one to boid color everytime tab is pressed, reset to 0 or 4 once it reaches its limit
	//boid color is checked everytime a new boid is created, and creates it with the color according to this number
	currBoidType += cycle;
	if (currBoidType == 5)
		currBoidType = 0;
	if (currBoidType == -1)
		currBoidType = 4;

	if (currBoidType == 0 && !isPredator)
	{
		texts.currObjectType.setString("Blue boid");
		texts.currObjectType.setFillColor(colors.blueBoidColor);
	}
	else if (currBoidType == 1 && !isPredator)
	{
		texts.currObjectType.setString("DBlue boid");
		texts.currObjectType.setFillColor(colors.darkBlueBoidColor);
	}
	else if (currBoidType == 2 && !isPredator)
	{
		texts.currObjectType.setString("Pink boid");
		texts.currObjectType.setFillColor(colors.pinkBoidColor);
	}
	else if (currBoidType == 3 && !isPredator)
	{
		texts.currObjectType.setString("Yellow boid");
		texts.currObjectType.setFillColor(colors.yellowBoidColor);
	}
	else if (currBoidType == 4 && !isPredator)
	{
		texts.currObjectType.setString("White boid");
		texts.currObjectType.setFillColor(colors.whiteBoidColor);
	}
}
//help cycle through mucis
void Simulation::cycleMusic()
{
	currMusic += 1;
	if (currMusic == 4)
		currMusic = 0;

	if (currMusic == 0)
	{
		music.fairyFountain.stop();
		music.claireDeLune.play();
	}
	else if (currMusic == 1)
	{
		music.claireDeLune.stop();
		music.ameilie.play();
	}
	else if (currMusic == 2)
	{
		music.ameilie.stop();
		music.gymnopeide.play();
	}
	else if (currMusic == 3)
	{
		music.gymnopeide.stop();
		music.fairyFountain.play();
	}
}
//help cycle which circle of repulsions we want
void Simulation::cycleCircle()
{
	if (circleType.radius == 200)
	{
		circleType.radius = 250;
		circleType.incValue = 6;
	}
	else if (circleType.radius == 250)
	{
		circleType.radius = 500;
		circleType.incValue = 3;
	}
	else if (circleType.radius == 500)
	{
		circleType.radius = 800;
		circleType.incValue = 6;
	}
	else if (circleType.radius == 800)
	{
		circleType.radius = 200;
		circleType.incValue = 7.5;
	}
}

//-----------FUNCTIONS HELPING WITH RUNNING THE ACTUAL PROGRAM-----------------
//to help update the fps every loop
void Simulation::updateFps()
{
	int fps;
	fps = 1.f / fpsClock.getElapsedTime().asSeconds();
	fpsClock.restart(); //restart the fpsClock so we can get accurate fps values
	if (fpsTextClock.getElapsedTime().asSeconds() > 0.4f) //every .4 seconds, update the text that displays fps
	{
		texts.fpsText.setString("FPS: " + std::to_string(fps));
		fpsTextClock.restart(); //restart the text clock and wait until .4 seconds pass again
	}
}
//calls the rules for prey and predators (determines which direction, velocity, rotation, and position they should update to later on in updateBoids())
void Simulation::callRules()
{
	//loop through each boid vector and call the rules on every boid in that vector
	//seperating them into their own arrays signifigantly optimizes
	//loop through each boid vector and call the rules on every boid in that vector
	//seperating them into their own arrays signifigantly optimizes
	
	//each boid will take in: its own boid type vector, the predators and repulsions, the rule 1,2,3 bool (saying if they are active or not)
	//, and its behavior (coeffiecients 1,2,3 and its seperation distance and its sight range to other same type boids).
	for (int i = 0; i < DBlueBoids.size(); i++)
		DBlueBoids[i].callBoidRules(DBlueBoids, predators, repulsions, whichRules, behavior);
	for (int i = 0; i < blueBoids.size(); i++)
		blueBoids[i].callBoidRules(blueBoids, predators, repulsions, whichRules, behavior);
	for (int i = 0; i < pinkBoids.size(); i++)
		pinkBoids[i].callBoidRules(pinkBoids, predators, repulsions, whichRules, behavior);
	for (int i = 0; i < yellowBoids.size(); i++)
		yellowBoids[i].callBoidRules(yellowBoids, predators, repulsions, whichRules, behavior);
	for (int i = 0; i < whiteBoids.size(); i++)
		whiteBoids[i].callBoidRules(whiteBoids, predators, repulsions, whichRules, behavior);
	for (int i = 0; i < predators.size(); i++)
		predators[i].callPredatorRules(blueBoids, DBlueBoids, pinkBoids, yellowBoids, predators, repulsions);
}
//updates the game speed for all objects
void Simulation::updateGameSpeed()
{
	if (currGameSpeed != prevGameSpeed) //if the gameSpeed doesnt match what the gameSpeed was in the loop before, update game speed on all objects
	{
		//loop through each boid and repulsion vector and update game speed on each object in the vector
		for (int i = 0; i < counts.boidBlueCount; i++)
			blueBoids[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < counts.boidDBlueCount; i++)
			DBlueBoids[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < counts.boidPinkCount; i++)
			pinkBoids[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < counts.boidYellowCount; i++)
			yellowBoids[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < counts.boidWhiteCount; i++)
			whiteBoids[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < counts.boidPredatorCount; i++)
			predators[i].updateGameSpeed(currGameSpeed);
		for (int i = 0; i < repulsions.size(); i++)
			repulsions[i].updateGameSpeed(currGameSpeed);
	}
	prevGameSpeed = currGameSpeed; //this is used in the next loop, when we check if prevGameSpeed!=currGameSpeed
}
//updates each boids position, direction, velocity, rotation, and animation. Then draws the boid to the window. Also updates and draws repulsions
void Simulation::updateObjects()
{
	//loops through each boids vector and updates each individual boid in the vectors. Does the same for repulsions
	for (int i = 0; i < DBlueBoids.size(); i++)
		DBlueBoids[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < blueBoids.size(); i++)
		blueBoids[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < pinkBoids.size(); i++)
		pinkBoids[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < yellowBoids.size(); i++)
		yellowBoids[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < whiteBoids.size(); i++)
		whiteBoids[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < predators.size(); i++)
		predators[i].updateBoid(window, isPredatorOnScreen);
	for (int i = 0; i < repulsions.size(); i++)
		repulsions[i].updateRepulsion(window);
}
//update the display of boid counts
void Simulation::updateBoidCountText()
{
	texts.boidBlueCountText.setString("Blue Count: " + std::to_string(counts.boidBlueCount));
	texts.boidDBlueCountText.setString("DBlue Count: " + std::to_string(counts.boidDBlueCount));
	texts.boidPinkCountText.setString("Pink Count: " + std::to_string(counts.boidPinkCount));
	texts.boidYellowCountText.setString("Yellow Count: " + std::to_string(counts.boidYellowCount));
	texts.boidWhiteCountText.setString("White Count: " + std::to_string(counts.boidWhiteCount));
	texts.boidPredatorCountText.setString("Predator Count: " + std::to_string(counts.boidPredatorCount));
}
//update the display of game speed
void Simulation::updateGameSpeedText()
{
	std::string currGameSpeedStr = std::to_string(currGameSpeed);
	std::string rounded = currGameSpeedStr.substr(0, currGameSpeedStr.find(".") + 3);
	texts.gameSpeedText.setString("Game Speed: " + rounded + "x");
}
//update the display of the flocking pattern
void Simulation::updateFlockingPatternText()
{
	texts.flockingTypeText.setString("Flocking Type: " + std::to_string(behavior.whichPattern + 1));
}
//draw the HUD
void Simulation::drawHUD()
{
	if (isHud) //if show hud, draw everything (all texts, info, etc.). otherwise we only draw borders
	{
		//update the boid counter text
		window.draw(texts.boidBlueCountText);
		window.draw(texts.boidDBlueCountText);
		window.draw(texts.boidPinkCountText);
		window.draw(texts.boidYellowCountText);
		window.draw(texts.boidWhiteCountText);
		window.draw(texts.boidPredatorCountText);
		//update the rules text
		window.draw(texts.rules);
		window.draw(texts.rule1);
		window.draw(texts.rule2);
		window.draw(texts.rule3);
		//update currObject text
		window.draw(texts.currObject);
		window.draw(texts.currObjectType);
		//update control menu
		if (isControls)
			window.draw(texts.simulationControls);
		else
			window.draw(texts.openControls);
		//draw fps
		window.draw(texts.fpsText);
		//draw game speed
		window.draw(texts.gameSpeedText);
		//draw flocking pattern type
		window.draw(texts.flockingTypeText);
	}
}
//draw the borders
void Simulation::drawBorder()
{
	if (behavior.isBorder)
	{
		window.draw(borders.topBorder);
		window.draw(borders.bottomBorder);
		window.draw(borders.leftBorder);
		window.draw(borders.rightBorder);
	}
}