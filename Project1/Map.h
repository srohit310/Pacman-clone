#pragma once
#define ROW 30 
#define COL 36

#include "Texture.h"
class Map
{
	int layoutformat[ROW][COL];
	int collide[8];
	int pelletsleft;

public:
	std::vector<std::vector<sf::Sprite>> maze_layout;
	Map(Texture& texture);
	void MapReset(Texture& texture);
	//ghost ai addons
	int grid[ROW][COL];
	//ghost ai addons

	int pellet(int posx,int posy, Texture& texture);
	int retpelletsleft() {
		return pelletsleft;
	}
	int* spacedetector(sf::Sprite &sprite, double gap, float collisionbar);
	void teleport(sf::Sprite &sprite);
	bool reachhouse(sf::Sprite &sprite);
	bool intersection(int x, int y);
	int returnitem(int x, int y);
	int detectwall(float posx, float posy);
	int getlayouttexture(int x, int y);
};

