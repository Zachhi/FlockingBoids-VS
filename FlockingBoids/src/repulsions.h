#ifndef REPULSIONS_H
#define REPULSIONS_H
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Repulsion {
private:

	sf::Vector2f position;

	sf::Clock repulsionAnimClock;
	float repulsionAnimSpeed = 0.025f;
	float baseRepulsionAnimSpeed = 0.025f;	//so we can modify game speed. we need a base that will never change

	sf::Sprite repulsionSprite; //for the animation/image
	sf::IntRect repulsionRect;

public:
	Repulsion(int posx, int posy, sf::Texture& thatTexture); //constructor

	void updateRepulsion(sf::RenderWindow& window); //update the repulsion (animate and draw it)
	sf::Vector2f getPosition(); //return its position
	void updateGameSpeed(float gameSpeed); //update the repulsions game speed
};



#endif //REPULSIONS_H