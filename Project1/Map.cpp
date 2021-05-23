#include "Map.h"

Map::Map(Texture& texture) :layoutformat	  { {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
								{30, 30, 30,  0, 13, 13, 13, 13, 13, 13, 13, 13,  1, 30, 30, 30,  8, 32,  9, 30, 30, 30,  0, 13, 13, 13, 13, 17, 28, 13, 13, 13, 13,  1, 30, 30},
								{30, 30, 30,  8, 26, 26, 27, 26, 26, 26, 26, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 26, 26, 27, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2,  3, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26,  2,  3, 26,  6,  7, 26,  2,  3, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 11,  6, 14, 14,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6,  7, 26,  6, 13, 13, 13,  7, 32,  6, 13, 13, 13,  7, 26,  6, 15, 15, 15,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2, 14, 14, 14, 14, 14, 14,  3, 32,  2, 14, 14, 14,  3, 26,  2,  3, 26,  2, 14, 14,  7, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  6, 15, 15,  3,  2, 15, 15,  7, 32,  6, 15, 15, 15,  7, 26, 11, 10, 26,  6, 15, 15,  3, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 26, 26, 26, 11, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  2,  3, 26, 11, 10, 32, 18, 12, 12, 12, 19, 32,  2,  3, 26, 11, 10, 26,  2,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26, 11, 10, 26,  6,  7, 32,  9, 30, 30, 30,  8, 32, 11, 10, 26,  6,  7, 26, 11, 10, 26,  6,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 11, 10, 26, 32, 32, 32, 31, 30, 32, 30,  8, 32, 11, 10, 26, 26, 26, 26, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30, 24, 14, 14, 14,  3, 26, 11,  6, 14, 14,  3, 32, 31, 30, 32, 30,  8, 32, 11,  6, 14, 14,  3, 32, 11,  6, 14, 14,  3, 26,  9, 30, 30},
								{30, 30, 30, 16, 15, 15, 15,  7, 26, 11,  2, 15, 15,  7, 32, 31, 32, 32, 30,  8, 32, 11,  2, 15, 15,  7, 32, 11,  2, 15, 15,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 11, 10, 26, 32, 32, 32, 31, 30, 32, 30,  8, 32, 11, 10, 26, 26, 26, 26, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26, 11, 10, 26,  2,  3, 32,  9, 30, 30, 30,  8, 32, 11, 10, 26,  2,  3, 26, 11, 10, 26,  2,  3, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  6,  7, 26, 11, 10, 32, 22, 13, 13, 13, 23, 32,  6,  7, 26, 11, 10, 26,  6,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 26, 26, 26, 11, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26,  2, 14, 14,  7,  6, 14, 14,  3, 32,  2, 14, 14, 14,  3, 26, 11, 10, 26,  2, 14, 14,  7, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6, 15, 15, 15, 15, 15, 15,  7, 32,  6, 15, 15, 15,  7, 26,  6,  7, 26,  6, 15, 15,  3, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  2, 14,  3, 26,  2,  3, 26,  2, 12, 12, 12,  3, 32,  2, 12, 12, 12,  3, 26,  2, 14, 14, 14,  3, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 11,  2, 15, 15,  7, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 11, 30, 10, 26, 11, 10, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 11, 10, 26, 26, 26, 26, 11, 10, 26,  9, 30, 30},
								{30, 30, 30,  8, 26,  6, 15,  7, 26,  6,  7, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26,  6,  7, 26,  2,  3, 26,  6,  7, 26,  9, 30, 30},
								{30, 30, 30,  8, 26, 26, 27, 26, 26, 26, 26, 26,  9, 30, 30, 30,  8, 32,  9, 30, 30, 30,  8, 26, 26, 26, 27, 11, 10, 26, 26, 26, 26,  9, 30, 30},
								{30, 30, 30,  4, 12, 12, 12, 12, 12, 12, 12, 12,  5, 30, 30, 30,  8, 32,  9, 30, 30, 30,  4, 12, 12, 12, 12, 25, 20, 12, 12, 12, 12,  5, 30, 30},
								{30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30} 

}
{
	for (int i = 0; i < ROW; i++) {
		std::vector<sf::Sprite> tempvector;
		for (int j = 0; j < COL; j++) {
			sf::Sprite tempsprite;
			tempsprite = texture.getspriteatpos(getlayouttexture(i, j));
			tempsprite.setPosition(sf::Vector2f(i * 16.0f, j * 16.0f));
			tempvector.push_back(tempsprite);
		}
		maze_layout.push_back(tempvector);
	}
	//ghost ai addons
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if ((layoutformat[i][j] == 26 || layoutformat[i][j] == 27 || layoutformat[i][j] == 32 || layoutformat[i][j] == 33 || layoutformat[i][j] == 34)) {
				grid[i][j] = 1;
			}
			else
				grid[i][j] = 0;
		}
	}
	
	grid[15][15] = 1;
	//ghost ai addons

	pelletsleft = 244;
	std::cout << "Finished genrating map\n";
}

void Map::MapReset(Texture &texture)
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (layoutformat[i][j] == 33) {
				layoutformat[i][j] = 26;
				maze_layout[i][j] = texture.getspriteatpos(getlayouttexture(i, j));
				maze_layout[i][j].setPosition(sf::Vector2f(i * 16.0f, j * 16.0f));
			}
			else if (layoutformat[i][j] == 34) {
				layoutformat[i][j] = 27;
				maze_layout[i][j] = texture.getspriteatpos(getlayouttexture(i, j));
				maze_layout[i][j].setPosition(sf::Vector2f(i * 16.0f, j * 16.0f));
			}
		}
	}
	pelletsleft = 244;
}

int Map::pellet(int posx,int posy,Texture &texture)
{
	int x = posx+1;
	int y = posy+1;
	if ((x >= 0 && x < ROW) && (y >= 0 && y < COL)) {
		if (layoutformat[x][y] == 26 || layoutformat[x][y] == 27) {
			int temp = layoutformat[x][y];
			pelletsleft--;
			if (temp == 26) {
				layoutformat[x][y] = 33;
				maze_layout[x][y] = texture.getspriteatpos(getlayouttexture(x, y));
				return 10;
			}
			if (temp == 27) {
				layoutformat[x][y] = 34;
				maze_layout[x][y] = texture.getspriteatpos(getlayouttexture(x, y));
				return 50;
			}
		}
	}
	return 0;
}

int* Map::spacedetector(sf::Sprite &sprite,double gap,float collisionbar)
{
	//right opening
	collide[0] = detectwall(sprite.getPosition().x / 16.0 + collisionbar, (sprite.getPosition().y - gap) / 16.0);
	collide[1] = detectwall(sprite.getPosition().x / 16.0 + collisionbar, (sprite.getPosition().y + gap) / 16.0);
	
	//down opening
	collide[2] = detectwall((sprite.getPosition().x - gap) / 16.0, sprite.getPosition().y / 16.0 + collisionbar);
	collide[3] = detectwall((sprite.getPosition().x + gap) / 16.0, sprite.getPosition().y / 16.0 + collisionbar);
	

	//left opening
	collide[4] = detectwall(sprite.getPosition().x / 16.0 - collisionbar, (sprite.getPosition().y - gap) / 16.0);
	collide[5] = detectwall(sprite.getPosition().x / 16.0 - collisionbar, (sprite.getPosition().y + gap) / 16.0);
	

	//up opening
	collide[6] = detectwall((sprite.getPosition().x - gap) / 16.0, sprite.getPosition().y / 16.0 - collisionbar);
	collide[7] = detectwall((sprite.getPosition().x + gap) / 16.0, sprite.getPosition().y / 16.0 - collisionbar);
	return collide;
}

void Map::teleport(sf::Sprite &sprite)
{
	int posx = sprite.getPosition().x;
	int posy = sprite.getPosition().y;
	if ((posx == 439 || posx == 438) && (posy == 264 || posy == 263))
		sprite.setPosition(sf::Vector2f(9.0f, sprite.getPosition().y));
	if (posx == 8 && (posy == 264 || posy == 263))
		sprite.setPosition(sf::Vector2f(435.0f, sprite.getPosition().y));
}

bool Map::reachhouse(sf::Sprite &sprite)
{
	int posx = (29 - (int)((sprite.getPosition().x / 16.0) + 1));
	int posy = (sprite.getPosition().y / 16.0) + 1;
	if (posx == 14 && posy == 17) {
		return true;
	}
	return false;
}

bool Map::intersection(int x, int y)
{
	if ((x == 2 && y == 4) || (x == 7 && y == 4) || (x == 13 && y == 4) || (x == 16 && y == 4) || (x == 22 && y == 4) || (x == 27 && y == 4)
		|| (x == 2 && y == 8) || (x == 7 && y == 8) || (x == 10 && y == 8) || (x == 13 && y == 8) || (x == 16 && y == 8) || (x == 19 && y == 8) || (x == 22 && y == 8) || (x == 27 && y == 8)
		|| (x == 2 && y == 11) || (x == 7 && y == 11) || (x == 10 && y == 11) || (x == 13 && y == 11) || (x == 16 && y == 11) || (x == 19 && y == 11) || (x == 22 && y == 11) || (x == 27 && y == 11)
		|| (x == 10 && y == 14) || (x == 13 && y == 14) || (x == 16 && y == 14) || (x == 19 && y == 14)
		|| (x == 7 && y == 17) || (x == 10 && y == 17) || (x == 17 && y == 17) || (x == 13 && y == 17) || (x == 16 && y == 17) || (x == 19 && y == 17) || (x == 22 && y == 17) || (x == 27 && y == 17)
		|| (x == 10 && y == 20) || (x == 19 && y == 20)
		|| (x == 2 && y == 23) || (x == 10 && y == 23) || (x == 7 && y == 23) || (x == 13 && y == 23) || (x == 16 && y == 23) || (x == 19 && y == 23) || (x == 22 && y == 23) || (x == 27 && y == 23)
		|| (x == 2 && y == 26) || (x == 4 && y == 26) || (x == 7 && y == 26) || (x == 10 && y == 26) || (x == 13 && y == 26) || (x == 16 && y == 26) || (x == 19 && y == 26) || (x == 22 && y == 26) || (x == 25 && y == 26) || (x == 27 && y == 26)
		|| (x == 2 && y == 29) || (x == 4 && y == 29) || (x == 7 && y == 29) || (x == 10 && y == 29) || (x == 13 && y == 29) || (x == 16 && y == 29) || (x == 19 && y == 29) || (x == 22 && y == 29) || (x == 25 && y == 29) || (x == 27 && y == 29)
		|| (x == 2 && y == 32) || (x == 13 && y == 32) || (x == 16 && y == 32) || (x == 27 && y == 32)
		|| (x == 14 && y == 14)  || (x == 14 && y == 17))
	return true;
	return false;
}

int Map::returnitem(int x, int y)
{
	return layoutformat[x][y];
}

int Map::detectwall(float posx, float posy)
{
	int x = posx +1;
	int y = posy +1;
	if ((x >= 0 && x < 31) && (y >= 0 && y < 36)) {
		if (layoutformat[x][y] !=26  && layoutformat[x][y] != 27 && layoutformat[x][y] != 32 && layoutformat[x][y] != 33 && layoutformat[x][y] != 34) {
			return 1;
		}
	}
	return 0;
}

int Map::getlayouttexture(int x, int y)
{
	if (layoutformat[x][y] == 32 || layoutformat[x][y] == 33 || layoutformat[x][y] == 34)
		return 30;
	else
		return layoutformat[x][y];
}

