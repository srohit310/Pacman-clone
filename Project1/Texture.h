#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

class Texture 
{
	sf::Texture pacman;
	sf::Texture labyrinth;
	sf::Texture ghosteyes;
	sf::Texture scoring;
	sf::Sprite Red;
	sf::Sprite Pink;
	sf::Sprite Lightblue;
	sf::Sprite Orange;
	std::vector<sf::Sprite> spritelabyrinth;
	sf::IntRect inteyesrect;
	sf::IntRect ghostR;
	sf::IntRect ghostP;
	sf::IntRect ghostB;
	sf::IntRect ghostO;
public:
	sf::IntRect intrect;
	sf::Sprite RedGhost;
	sf::Sprite PinkGhost;
	sf::Sprite BlueGhost;
	sf::Sprite OrangeGhost;
	sf::Sprite spritepacman;
	sf::Sprite sign;
	sf::Sprite eyes;
	sf::Sprite Lives;
	sf::Sprite Number;
	struct fruits {
		sf::Sprite fruit;
		int score;
		sf::Sprite scoresprite;
	}bonus[8];
	Texture();
	void resetpositions();
	void setsign(int no);
	void Load();
	void seteyes(int Mode, sf::Sprite &sprite);
	void setpoints(int ghostcapturepoints, sf::Sprite& sprite);
	sf::Sprite getspriteatpos(int i);
	int getIndex();
	bool fruitcollision(sf::Sprite &sprite);
	void setintrect(int,int);
	int rectleft();
};

