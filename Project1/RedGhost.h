#pragma once
#include "Ghost.h"
class RedGhost : public Ghost
{
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
	sf::Clock redscattertrigger;
	RedGhost();
	void reset();
	void scatter();
	void frightenedstatebeg();
	void frightenedstateend(Texture& texture,Map &mapresloader);
	void Redmove(Texture& texture);
	void ghostprops(Texture &texture, Map& mapresloader);
	void ghostintersecmove(Texture& texture, Map& mapresloader);
	bool iscapture(Texture& texture);
};

