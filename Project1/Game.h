#pragma once
#define ROW 29 
#define COL 36
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <string.h>
#include <map>
#include <stack>
#include <vector>
#include <fstream>
#include "Map.h"
#include "Texture.h"
#include "Pacman.h"
#include "Ghost.h"
#include "RedGhost.h"
#include "PinkGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"

class Game
{
	long HighScore;
	long loadedhighscore;
	int liferegen;
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event event;
	Texture texture;
	Map mapresloader;
	sf::Clock clock;
	sf::Clock clock1;
	sf::Clock Timer;
	sf::Clock activateghosts;
	sf::Clock fruitTimer;
	int activeghosts;
	int flag;
	typedef std::pair<int, int> Pair;
	int loop;
	int timing;
	int tempmode;
	bool TriggerMode;
	Pacman pacman;
	RedGhost red;
	PinkGhost pink;
	BlueGhost blue;
	OrangeGhost orange;
	float activateghosttiminings[4];
	void initvariable();
	void initwindow();
	int triggerdeathanimation;
	bool isfrightened[4];
	int Lives;
	int Level;
	int ghostcapturecount;
	bool fruitspawn;

public:
	
	Game();
	void reset();
	void loadhighscore();
	void checkghostcollision();
	void frightentiming();
	const bool getIsWindowOpen();
	void pollevents();
	void fruitspawns();
	void levelincrement();
	void savehighscore();
	int Update();
	int Render();

	virtual ~Game();
};
