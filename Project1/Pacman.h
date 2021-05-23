#pragma once
#include "Texture.h"
#include "Map.h"
#include "levelparams.h"
class Pacman : public levelparams
{
	//represents current direction pacman is moving in
	std::string direction;

	//Spped at which pacman is moving
	float speed;

	//To define the gap width into which pacman can change direction at an intersection
	int* collider;
	
	//The gap width from previous parameter "collide"
	float gap;

public:
	//The cuurent level the game is in
	int Level;
	
	//The current position of pacman texture rectangle (up,down,left,right)
	int resetvalue;

	//Used to check if the directions in which pacman can go is free of obstacle or not
	int flagup, flagright, flagdown, flagleft;

	//To store the buffered direction into which pacman will turn at an intersection
	std::string buffereddirec;

	//constructor
	Pacman();

	void reset();

	//function to carry out user input movements for pacman and also buffer the movements
	void polleventresult(std::string direction,Texture &texture);

	//function to check whether each of the four directions is free of obstacle 
	void collision(Texture &texture, Map& mapresloader);

	//function to carryout the buffered input
	void bufferdirec(Texture &texture);
	
	//function to teleport pacman 
	void teleport(Texture &texture);

	//function to move pacman
	void move(Texture &texture);

	std::string getdirection() {
		return direction;
	}

};

