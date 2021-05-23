#include "Texture.h"

Texture::Texture()
{
	intrect = sf::IntRect(135, 0, 15, 15);
	ghostR = sf::IntRect(0, 15, 15, 15);
	ghostP = sf::IntRect(0, 30, 15, 15);
	ghostB = sf::IntRect(0, 45, 15, 15);
	ghostO = sf::IntRect(0, 60, 15, 15);
	inteyesrect = sf::IntRect(149, 84, 9, 5);

	if (!pacman.loadFromFile("things.png")) {
		std::cout << "Failed to load file";
	}
	if (!labyrinth.loadFromFile("lab.png")) {
		std::cout << "Failed to load file";
	}
	if (!ghosteyes.loadFromFile("eyes.png")) {
		std::cout << "Failed to load file";
	}
	if (!scoring.loadFromFile("fullset.png")) {
		std::cout << "Failed to load File";
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			sf::Sprite tempsprite;
			tempsprite.setTexture(labyrinth);
			tempsprite.setTextureRect(sf::IntRect(i * 8, j * 8, 8, 8));
			tempsprite.setScale(2.0f, 2.0f);
			spritelabyrinth.push_back(tempsprite);
		}
	}
	RedGhost.setTexture(pacman);
	RedGhost.setTextureRect(ghostR);
	RedGhost.setScale(sf::Vector2f(2.0f, 2.0f));
	RedGhost.setPosition(sf::Vector2f(224, 216.606f));

	spritepacman.setTexture(pacman);
	spritepacman.setTextureRect(intrect);
	spritepacman.setScale(2.0f, 2.0f);
	spritepacman.setPosition(sf::Vector2f(228, 408));

	PinkGhost.setTexture(pacman);
	PinkGhost.setTextureRect(ghostP);
	PinkGhost.setScale(sf::Vector2f(2.0f, 2.0f));
	PinkGhost.setPosition(sf::Vector2f(230, 270));

	BlueGhost.setTexture(pacman);
	BlueGhost.setTextureRect(ghostB);
	BlueGhost.setScale(sf::Vector2f(2.0f, 2.0f));
	BlueGhost.setPosition(sf::Vector2f(195, 270));

	OrangeGhost.setTexture(pacman);
	OrangeGhost.setTextureRect(ghostO);
	OrangeGhost.setScale(sf::Vector2f(2.0f, 2.0f));
	OrangeGhost.setPosition(sf::Vector2f(260, 270));

	sign.setTexture(scoring);
	sign.setTextureRect(sf::IntRect(200, 0, 60, 15));
	sign.setScale(sf::Vector2f(1.5f, 1.5f));
	sign.setPosition(sf::Vector2f(200, 315));

	Lives.setTexture(pacman);
	Lives.setTextureRect(sf::IntRect(10 * 15, 0, 15, 15));
	Lives.setScale(sf::Vector2f(2.0f, 2.0f));
	
	Number.setTexture(scoring);
	Number.setTextureRect(sf::IntRect(15, 180, 10, 15));
	Number.setScale(sf::Vector2f(1.75f, 1.75f));
	for (int i = 0; i < 8; i++) {
		sf::Sprite tempsprite;
		tempsprite.setTexture(scoring);
		tempsprite.setScale(1.5f, 1.5f);
		if (i < 4)
			tempsprite.setTextureRect(sf::IntRect(172, 168 + 20 * i, 20, 17));
		else tempsprite.setTextureRect(sf::IntRect(172 + 40, 168 + 20 * (i - 4), 20, 17));
		tempsprite.setPosition(sf::Vector2f(224, 315));
		bonus[i].fruit = tempsprite;
		if (i < 4) bonus[i].score = 200 + (2 * i - 1) * 100;
		else if (i < 7) bonus[i].score = 1000 + (i - 4) * 1000;
		if (i == 7) bonus[i].score = 5000;
		tempsprite.setTextureRect(sf::IntRect(172, 5 + 20 * i, 20, 17));
		bonus[i].scoresprite = tempsprite;
	}
	std::cout << "Finished Loading Textures\n";
}

void Texture::resetpositions()
{
	RedGhost.setTexture(pacman);
	RedGhost.setTextureRect(ghostR);
	RedGhost.setPosition(sf::Vector2f(224, 216.606f));
	
	spritepacman.setPosition(sf::Vector2f(228, 408));
	
	PinkGhost.setTexture(pacman);
	PinkGhost.setTextureRect(ghostP);
	PinkGhost.setPosition(sf::Vector2f(230, 270));
	
	BlueGhost.setTexture(pacman);
	BlueGhost.setTextureRect(ghostB);
	BlueGhost.setPosition(sf::Vector2f(195, 270));

	OrangeGhost.setTexture(pacman);
	OrangeGhost.setTextureRect(ghostO);
	OrangeGhost.setPosition(sf::Vector2f(260, 270));
}

void Texture::setsign(int no)
{
	if (no == 1) {
		sign.setTextureRect(sf::IntRect(200, 0, 60, 15));
		sign.setPosition(sf::Vector2f(200, 315));
	}
	else if (no == 2) {
		sign.setTextureRect(sf::IntRect(16, 194, 80, 15));
		sign.setPosition(sf::Vector2f(180, 315));
	}
}

void Texture::seteyes(int Mode, sf::Sprite& sprite)
{
	if (Mode == 1) {
		sprite.setTexture(ghosteyes);
		sprite.setTextureRect(inteyesrect);
	}
	else {
		sprite.setTexture(pacman);
	}
	sprite.setScale(2.0f, 2.0f);
}

void Texture::setpoints(int ghostcapturecount, sf::Sprite& sprite)
{
	sprite.setTexture(scoring);
	sprite.setTextureRect(sf::IntRect(5 + 20 * ghostcapturecount, 225, 20, 15));
	sprite.setScale(1.15f, 1.15f);
}

sf::Sprite Texture::getspriteatpos(int i)
{
	return spritelabyrinth[i];
}

int Texture::getIndex()
{
	return spritelabyrinth.size();
}

bool Texture::fruitcollision(sf::Sprite &sprite)
{
	std::pair<int, int> pacman_box = std::make_pair((sprite.getPosition().x / 16.0) + 1, (sprite.getPosition().y / 16.0) + 1);
	std::pair<int, int> fruit_box = std::make_pair((bonus[0].fruit.getPosition().x / 16.0) + 1, (bonus[0].fruit.getPosition().y / 16.0) + 1);
	if ((pacman_box.first == fruit_box.first) && (pacman_box.second == fruit_box.second)) {
		return true;
	}
	return false;
}

void Texture::setintrect(int a,int b)
{
	intrect = sf::IntRect(a, b, 15, 15);
	spritepacman.setTextureRect(intrect);
}

int Texture::rectleft()
{
	return intrect.left;
}


