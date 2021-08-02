#include "repulsions.h"

//constructor
Repulsion::Repulsion(int posx, int posy, sf::Texture& thatTexture)
{
	//set the position
	position.x = posx;
	position.y = posy;

	//set the sprite
	repulsionRect.width = 52;
	repulsionRect.height = 52;
	repulsionRect.left = 0;
	repulsionRect.top = 0;
	repulsionSprite.setTexture(thatTexture);
	repulsionSprite.setTextureRect(repulsionRect);
	repulsionSprite.setOrigin(26, 26);
	repulsionSprite.setPosition(position);
}

//update animation and draw it
void Repulsion::updateRepulsion(sf::RenderWindow& window)
{
	//update the rect for the correct animation
	if (repulsionAnimClock.getElapsedTime().asSeconds() > repulsionAnimSpeed)
	{
		if (repulsionRect.top == 208 && repulsionRect.left == 104)
		{
			repulsionRect.top = 0;
			repulsionRect.left = 0;
		}
		else if (repulsionRect.left == 104)
		{
			repulsionRect.top += 52;
			repulsionRect.left = 0;
		}
		else
		{
			repulsionRect.left += 52;
		}
		repulsionSprite.setTextureRect(repulsionRect);
		repulsionAnimClock.restart();
	}
	//and now draw it
	window.draw(repulsionSprite);
}
//return its position
sf::Vector2f Repulsion::getPosition()
{
	return position;
}
//update the game speed for the repulsion
void Repulsion::updateGameSpeed(float gameSpeed)
{
	repulsionAnimSpeed = baseRepulsionAnimSpeed / gameSpeed;
}