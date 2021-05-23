#pragma once
#include <map>
#include <string>
#include <set>
#include <stdlib.h>
#include <time.h>
#include "Texture.h"
#include "levelparams.h"
#include "Map.h"

class Ghost : public levelparams
{
protected:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int>> pPair;
	typedef std::pair<bool, std::string> astar;
	//for reversing direction
	int revdirectiontrigger;
	//for forming scatterpoints
	std::vector<Pair> scatterpairs;
	//to know which scatterpoint the ghost is visiting
	int scatterpoint;
	//direction of the ghost
	std::string ghostdirection;
	//location of the sprite in the texture
	int spritelocation;
	sf::Clock Timer, animateclock;
	bool TriggerMode;
	int scatterset;
	int callonce;
	int resetvalue;
	int leftintrect;
	int loop;
	int entered;
	#pragma pack(1) 
	struct cell
	{
		short unsigned int parent_i;
		short unsigned int parent_j;
		short unsigned int g;
		float f;
	};
	struct location {
		int N, S, E, W;
	};
	double ghostgap;
	int* collider;
	bool isValid(int row, int col);
	bool isUnBlocked(int grid[][COL], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	std::string random_direction_generator(sf::Sprite &sprite, std::string direction, Map& mapresloader);
	float calculateHValue(int row, int col, Pair dest);
	std::string tracePath(cell cellDetails[][COL], Pair dest, Pair src);
	std::string revdirection(std::string direction);
	bool aStarSearch( Pair src, Pair dest, std::string &Ghostdirection, sf::Sprite &sprite,Map& mapresloader);
	void ghostmove(sf::Sprite &sprite, int Mode, float speed[3], int revdirectiontrigger, int reincarnating, std::string &ghostdirection, int spritelocation);
	void animate(sf::Sprite& sprite, sf::Clock &animateclock, int& leftintrect, int resetvalue, int spritelocation, int blinkmode);
	void reset(int& Mode, int& revdirectiontrigger, int& scatterpoint, int& reincarnating, int& scatterset, int& callonce, int& entered, std::string& ghostdirection,sf::Clock &clock, float speed[3], float scatterTimings[7], int Level);
	bool iscapture(sf::Sprite& sprite, Texture& texture);
public:
	int Level;
	std::pair<int, int> targetTileaheadofpacman(Pair src, Texture& texture, std::string direction, int& loop, int Mode, int spaces, Map& mapresloader);

};

