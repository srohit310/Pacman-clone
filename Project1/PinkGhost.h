#pragma once
#include "Ghost.h"
class PinkGhost : public Ghost
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
	sf::Clock pinkscattertrigger;
	PinkGhost();
	void reset();
	void scatter();
	void frightenedstatebeg();
	void frightenedstateend(Texture& texture, Map& mapresloader);
	void pinkmove(Texture& texture);
	void ghostprops(Texture& texture, std::string direction, Map& mapresloader);
	void ghostintersecmove(Texture& texture, std::string direction, Map& mapresloader);
	bool iscapture(Texture& texture);
};

