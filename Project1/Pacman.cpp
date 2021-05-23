#include "Pacman.h"

Pacman::Pacman()
{
	direction = "Right";
	speed = 0.00f;
	gap = 7.05f;
	resetvalue = 135;
	Level = 0;
	std::cout << "Pacman Loaded\n";
}

void Pacman::reset()
{
	direction = "Right";
	speed = 0.0f;
	resetvalue = 135;
	buffereddirec = "Right";
}

void Pacman::polleventresult(std::string direc, Texture &texture)
{
	speed = 1.0 * levelparameters[Level][1];
	if (direc.compare("Right") == 0) {
		if (direction.compare("Right") == 0) {
			return;
		}
		direction = "Right";
		buffereddirec = "Right";
		resetvalue = 135;
		texture.setintrect(resetvalue, 0);
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x + speed, texture.spritepacman.getPosition().y));

	}
	else if (direc.compare("Down") == 0) {
		if (direction.compare("Down") == 0) {
			return;
		}
		direction = "Down";
		buffereddirec = "Down";
		resetvalue = 45;
		texture.setintrect(resetvalue, 0);
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x, texture.spritepacman.getPosition().y + speed));

	}
	else if (direc.compare("Left") == 0) {
		if (direction.compare("Left") == 0)
			return;
		direction = "Left";
		buffereddirec = "Left";
		resetvalue = 90;
		texture.setintrect(resetvalue, 0);
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x - speed, texture.spritepacman.getPosition().y));

	}
	else if (direc.compare("Up") == 0) {
		if (direction.compare("Up") == 0)
			return;
		direction = "Up";
		buffereddirec = "Up";
		resetvalue = 0;
		texture.setintrect(resetvalue, 0);
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x, texture.spritepacman.getPosition().y - speed));

	}
}

void Pacman::collision(Texture& texture, Map& mapresloader)
{
	collider = mapresloader.spacedetector(texture.spritepacman,gap,0.560f);
	if (*collider == 0 && *(collider + 1) == 0) {
		flagright = 0;
	}
	else {
		flagright = 1;
	}
	if (*(collider + 2) == 0 && *(collider + 3) == 0) {
		flagdown = 0;
	}
	else {
		flagdown = 1;
	}
	if (*(collider + 4) == 0 && *(collider + 5) == 0) {
		flagleft = 0;
	}
	else {
		flagleft = 1;
	}
	if (*(collider + 6) == 0 && *(collider + 7) == 0) {
		flagup = 0;
	}
	else {
		flagup = 1;
	}
}

void Pacman::bufferdirec(Texture& texture)
{
	if ((buffereddirec.compare("Right") == 0) && (*collider == 0 && *(collider + 1) == 0) && flagright == 0) {

		resetvalue = 135;
		if (direction.compare("Right") != 0)
			texture.setintrect(resetvalue, 0);
		direction = buffereddirec;

	}
	if ((buffereddirec.compare("Left") == 0) && (*(collider + 4) == 0 && *(collider + 5) == 0) && flagleft == 0) {

		resetvalue = 90;
		if (direction.compare("Left") != 0)
			texture.setintrect(resetvalue, 0);
		direction = buffereddirec;

	}
	if ((buffereddirec.compare("Down") == 0) && (*(collider + 2) == 0 && *(collider + 3) == 0) && flagdown == 0) {

		resetvalue = 45;
		if (direction.compare("Down") != 0)
			texture.setintrect(resetvalue, 0);
		direction = buffereddirec;

	}
	if ((buffereddirec.compare("Up") == 0) && (*(collider + 6) == 0 && *(collider + 7) == 0) && flagup == 0) {

		resetvalue = 0;
		if (direction.compare("Up") != 0)
			texture.setintrect(resetvalue, 0);
		direction = buffereddirec;

	}
}

void Pacman::teleport(Texture &texture)
{
	int posx = texture.spritepacman.getPosition().x;
	int posy = texture.spritepacman.getPosition().y;
	if (posx == 450 && (posy == 264 || posy == 263))
		texture.spritepacman.setPosition(sf::Vector2f(5.0f, texture.spritepacman.getPosition().y));
	if (posx == 1 && (posy == 264 || posy == 263))
		texture.spritepacman.setPosition(sf::Vector2f(445.0f, texture.spritepacman.getPosition().y));
}

void Pacman::move(Texture &texture)
{

	if (direction.compare("Right") == 0 && flagright == 0) {
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x + speed, texture.spritepacman.getPosition().y));

	}
	else if (direction.compare("Down") == 0 && flagdown == 0) {
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x, texture.spritepacman.getPosition().y + speed));

	}
	else if (direction.compare("Left") == 0 && flagleft == 0) {
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x - speed, texture.spritepacman.getPosition().y));

	}
	else if (direction.compare("Up") == 0 && flagup == 0) {
		texture.spritepacman.setPosition(sf::Vector2f(texture.spritepacman.getPosition().x, texture.spritepacman.getPosition().y - speed));

	}
}
