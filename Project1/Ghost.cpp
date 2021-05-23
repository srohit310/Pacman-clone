#include "Ghost.h"

bool Ghost::isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

bool Ghost::isUnBlocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

bool Ghost::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

std::string Ghost::random_direction_generator(sf::Sprite &sprite,std::string direction, Map& mapresloader)
{
    std::vector<std::string> direc;
    int count = 0;
    collider = mapresloader.spacedetector(sprite, 0 ,0.570);
    if (*collider == 0 && *(collider + 1) == 0) {
        if (direction.compare("Left") != 0) {
            direc.push_back("Right");
            count++;
        }
    }
    if (*(collider + 2) == 0 && *(collider + 3) == 0) {
        if (direction.compare("Up") != 0) {
            direc.push_back("Down");
            count++;
        }
    }
    if (*(collider + 4) == 0 && *(collider + 5) == 0) {
        if (direction.compare("Right") != 0) {
            direc.push_back("Left");
            count++;
        }
    }
    if (*(collider + 6) == 0 && *(collider + 7) == 0) {
        if (direction.compare("Down") != 0) {
            direc.push_back("Up");
            count++;
        }
    }
    srand(time(0));
    direction = direc[rand() % count];
    return direction;

}

float Ghost::calculateHValue(int row, int col, Pair dest)
{
	return ((double)sqrt((row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}

std::string Ghost::tracePath(cell cellDetails[][COL], Pair dest, Pair src)
{
    int row = dest.first;
    int col = dest.second;
    int adjx, adjy;
    while (1)
    {
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        if (temp_row == src.first && temp_col == src.second) {

            adjx = row;
            adjy = col;
            break;
        }
        row = temp_row;
        col = temp_col;
    }


    int x = adjx - src.first;
    int y = adjy - src.second;
    if (x < 0) {
        return "Right";
    }
    if (x > 0) {
        return "Left";
    }
    if (y > 0) {
        return "Down";
    }
    if (y < 0) {
        return "Up";
    }

    return " ";
}

std::string Ghost::revdirection(std::string direction)
{
    if (direction.compare("Right")==0) {
        return "Left";
    }
    else if (direction.compare("Left")==0) {
        return "Right";
    }
    else if (direction.compare("Up")==0) {
        return "Down";
    }
    else if (direction.compare("Down")==0) {
        return "Up";
    }
}

std::pair<int, int> Ghost::targetTileaheadofpacman(Pair src, Texture& texture, std::string direction, int& loop, int Mode, int spaces, Map& mapresloader)
{
    if (direction.compare("Up") == 0) {
        if (loop == spaces) {
            return src;
        }
        if (mapresloader.detectwall(src.first - 1, src.second - 2)) {
            if (Mode == 0) {
                src = targetTileaheadofpacman(src, texture, "Right", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Left", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Down", loop, 1, spaces, mapresloader);
                return src;
            }
            else {
                return src;
            }
        }
        else {
            src.second -= 1;
            loop++;
            return targetTileaheadofpacman(src, texture, "Up", loop, 0, spaces, mapresloader);
        }
    }
    if (direction.compare("Down") == 0) {
        if (loop == spaces) {
            return src;
        }
        if (mapresloader.detectwall(src.first - 1, src.second)) {
            if (Mode == 0) {
                src = targetTileaheadofpacman(src, texture, "Left", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Right", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Up", loop, 1, spaces, mapresloader);
                return src;
            }
            else {
                return src;
            }
        }
        else {
            src.second += 1;
            loop++;
            return targetTileaheadofpacman(src, texture, "Down", loop, 0, spaces, mapresloader);
        }

    }
    if (direction.compare("Left") == 0) {
        if (loop == spaces) {

            return src;
        }
        if (mapresloader.detectwall(src.first, src.second - 1)) {
            if (Mode == 0) {
                src = targetTileaheadofpacman(src, texture, "Down", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Up", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Right", loop, 1, spaces, mapresloader);
                return src;
            }
            else {
                return src;
            }
        }
        else {
            src.first += 1;
            loop++;
            return targetTileaheadofpacman(src, texture, "Left", loop, 0, spaces, mapresloader);
        }

    }
    if (direction.compare("Right") == 0) {
        if (loop == spaces) {
            return src;
        }
        if (mapresloader.detectwall(src.first - 2, src.second - 1)) {
            if (Mode == 0) {
                src = targetTileaheadofpacman(src, texture, "Up", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Down", loop, 1, spaces, mapresloader);
                src = targetTileaheadofpacman(src, texture, "Left", loop, 1, spaces, mapresloader);
                return src;
            }
            else {
                return src;
            }
        }
        else {
            src.first -= 1;
            loop++;
            return targetTileaheadofpacman(src, texture, "Right", loop, 0, spaces, mapresloader);
        }

    }
}

bool Ghost::aStarSearch( Pair src, Pair dest, std::string& Ghostdirection, sf::Sprite &sprite, Map& mapresloader)
{
    if (isDestination(src.first, src.second, dest) == true)
    {
        Ghostdirection = random_direction_generator(sprite,Ghostdirection, mapresloader);
        return true;
    }
  
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[ROW][COL];
    short unsigned int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = 32555;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 1;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    std::set<pPair> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();
        astar temppair;
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        float hNew, fNew;
        short unsigned int gNew;

        //----------- 1st Successor (North) ------------ 

        if (isValid(i - 1, j) == true)
        {
            if (isDestination(i - 1, j, dest) == true)
            {
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                Ghostdirection = tracePath(cellDetails, dest, src);
                foundDest = true;
                return false;
            }
            else if (closedList[i - 1][j] == false &&
                isUnBlocked(mapresloader.grid, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;
                if (cellDetails[i - 1][j].f == FLT_MAX ||
                    cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                        std::make_pair(i - 1, j)));
 
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------ 

        if (isValid(i + 1, j) == true)
        {
            if (isDestination(i + 1, j, dest) == true)
            {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                Ghostdirection = tracePath(cellDetails, dest, src);
                foundDest = true;
                return false;
            }
            else if (closedList[i + 1][j] == false &&
                isUnBlocked(mapresloader.grid, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j].f == FLT_MAX ||
                    cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j)));
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------ 

        if (isValid(i, j + 1) == true)
        {
            if (isDestination(i, j + 1, dest) == true)
            {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                Ghostdirection = tracePath(cellDetails, dest, src);
                foundDest = true;
                return false;
            }

            else if (closedList[i][j + 1] == false &&
                isUnBlocked(mapresloader.grid, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j + 1].f == FLT_MAX ||
                    cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                        std::make_pair(i, j + 1)));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------ 
        if (isValid(i, j - 1) == true)
        {
            if (isDestination(i, j - 1, dest) == true)
            {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                Ghostdirection = tracePath(cellDetails, dest, src);
                foundDest = true;
                return false;
            }

            else if (closedList[i][j - 1] == false &&
                isUnBlocked(mapresloader.grid, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == FLT_MAX ||
                    cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(std::make_pair(fNew,
                        std::make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");
    return false;
}

void Ghost::ghostmove(sf::Sprite &sprite, int Mode, float speed[3], int revdirectiontrigger, int reincarnating, std::string &ghostdirection, int spritelocation)
{
    float ghostspeed;
    if (Mode != 1) {
        ghostspeed = speed[0];
        revdirectiontrigger = 1;
    }
    else if (Mode == 1) {
        if (reincarnating != 1) {
            ghostspeed = speed[1];
        }
        else {
            ghostspeed = speed[2];
        }
        if (revdirectiontrigger == 1) {
            ghostdirection = revdirection(ghostdirection);
            revdirectiontrigger = 0;

        }
    }
    if (ghostdirection.compare("Right") == 0) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x + ghostspeed, sprite.getPosition().y));
    }
    else if (ghostdirection.compare("Down") == 0) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + ghostspeed));
    }
    else if (ghostdirection.compare("Left") == 0) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x - ghostspeed, sprite.getPosition().y));
    }
    else if (ghostdirection.compare("Up") == 0) {
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - ghostspeed));
    }
}

void Ghost::animate(sf::Sprite& sprite, sf::Clock &animateclock, int& leftintrect, int resetvalue, int spritelocation, int blinkmode)
{
    int limit = 15;
        if (animateclock.getElapsedTime().asSeconds() >= 0.15f) {
            if (blinkmode == 1) {
                limit = 30;
            }
            if (leftintrect < resetvalue + limit) {
                   leftintrect = (leftintrect + limit);
            }
            else {
                 leftintrect = resetvalue;
            }
            if (resetvalue == 8 * 15) {
                 spritelocation = 15;
            }
                sprite.setTextureRect(sf::IntRect(leftintrect, spritelocation, 15, 15));
            animateclock.restart();
        }
    
    
}

void Ghost::reset(int &Mode,int &revdirectiontrigger,int &scatterpoint,int &reincarnating,int &scatterset,int &callonce,int &entered,std::string &ghostdirection, sf::Clock& clock, float speed[3], float scatterTimings[7], int Level)
{

    Mode = 2;
    revdirectiontrigger = 0;
    scatterpoint = 0;
    reincarnating = 0;
    scatterset = 0;
    callonce = 0;
    entered = 0;
    ghostdirection = "";
    speed[0] = 0.9 * levelparameters[Level][2];
    for (int i = 0 ; i < 7; i++) {
        if (i % 2 == 0) {
            if (i > 2) {
                scatterTimings[i] = levelparameters[Level][8] - 2.0;
            }
            else
                scatterTimings[i] = levelparameters[Level][8];
        }
        else
            scatterTimings[i] = 20.0f;
    }
    clock.restart();
}

bool Ghost::iscapture(sf::Sprite& sprite, Texture& texture)
{
    std::pair<float, float> l1 = std::make_pair(texture.spritepacman.getPosition().x + 8, texture.spritepacman.getPosition().y + 8);
    std::pair<float, float> r1 = std::make_pair(texture.spritepacman.getPosition().x + 22, texture.spritepacman.getPosition().y + 22);
    std::pair<float, float> l2 = std::make_pair(sprite.getPosition().x + 8, sprite.getPosition().y + 8);
    std::pair<float, float> r2 = std::make_pair(sprite.getPosition().x + 22, sprite.getPosition().y + 22);

    if (l1.first >= r2.first || l2.first >= r1.first)
        return false;
    if (l1.second >= r2.second || l2.second >= r1.second)
        return false;
    return true;
}