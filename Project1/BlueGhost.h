#pragma once
#include "Ghost.h"
class BlueGhost: public Ghost
{
	Pair src;
	Pair dest;
	float speed[3];
	float scatterTimings[7];
public:
	/*
		0 - chase mode
		1 - frightened mode
		2 - scatter mode
	*/
	int Mode;
	int prevmode;
	int reincarnating;
	sf::Clock bluescattertrigger;
	BlueGhost();
	void reset();
	void scatter();
	void frightenedstatebeg();
	void frightenedstateend(Texture& texture, Map& mapresloader);
	void bluemove(Texture& texture);
	std::pair<int, int> target(Texture& texture, std::string direction, Map& mapresloader);
	void ghostprops(Texture& texture, std::string direction, Map& mapresloader);
	void ghostintersecmove(Texture& texture, std::string direction, Map& mapresloader);
	bool iscapture(Texture& texture);
};

