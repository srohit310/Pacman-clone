#include "BlueGhost.h"

BlueGhost::BlueGhost() : speed{ 0.9 * 0.75 ,0.4,1.6 }, scatterTimings{ 7.0f, 20.0f, 7.0f, 20.0f, 5.0f, 20.0f, 5.0f }
{
    ghostgap = 7.00;
    Mode = 2;
    revdirectiontrigger = 0;
    scatterpairs.push_back(std::make_pair(7, 26));
    scatterpairs.push_back(std::make_pair(2, 32));
    scatterpairs.push_back(std::make_pair(13, 32));
    scatterpairs.push_back(std::make_pair(10, 26));
    scatterpoint = 0;
    reincarnating = 0;
    spritelocation = 45;
    scatterset = 0;
    loop = 0;
    callonce = 0;
    entered = 0;
    Level = 0;
    std::cout << "Blue Ghost Loaded\n";
}

void BlueGhost::reset()
{
    Ghost::reset(Mode, revdirectiontrigger, scatterpoint, reincarnating, scatterset, callonce, entered, ghostdirection,bluescattertrigger,speed,scatterTimings,Level);
}

void BlueGhost::scatter()
{
    if (scatterset < 7) {
        if (Mode != 1) {
            if (bluescattertrigger.getElapsedTime() >= sf::seconds(scatterTimings[scatterset])) {
                if (scatterset % 2 == 0)
                    Mode = 0;
                else Mode = 2;
                scatterset++;
                bluescattertrigger.restart();
            }
        }
        else {
            bluescattertrigger.restart();
        }
    }
}

void BlueGhost::frightenedstatebeg()
{
    if (Mode != 1)
        prevmode = Mode;
    Mode = 1;
    leftintrect = 8 * 15;
    TriggerMode = true;
    if (scatterset < 7)
        scatterTimings[scatterset] -= Timer.getElapsedTime().asSeconds();
    Timer.restart();
}

void BlueGhost::frightenedstateend(Texture& texture, Map& mapresloader)
{
    if (TriggerMode) {
        if (Timer.getElapsedTime().asSeconds() >= levelparameters[Level][7]) {
            TriggerMode = false;
            Mode = prevmode;

        }
        if (reincarnating == 1) {
            Timer.restart();
        }
        if (mapresloader.reachhouse(texture.BlueGhost)) {
            TriggerMode = false;
            Timer.restart();
            Mode = prevmode;
            reincarnating = 0;
            texture.seteyes(0, texture.BlueGhost);
        }
    }
}

void BlueGhost::bluemove(Texture& texture)
{
    Ghost::ghostmove(texture.BlueGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
}

std::pair<int,int> BlueGhost::target(Texture& texture, std::string direction, Map& mapresloader)
{
    Pair temppair;
    temppair = targetTileaheadofpacman(std::make_pair(29 - ((int)(texture.spritepacman.getPosition().x / 16.0) + 1), (texture.spritepacman.getPosition().y / 16.0) + 1), texture, direction, loop, 0, 2, mapresloader);
    loop = 0;
    Pair binkyposition = std::make_pair(29 - (int)((texture.RedGhost.getPosition().x / 16.0) + 1), (texture.RedGhost.getPosition().y / 16.0) + 1);
    int count = calculateHValue(temppair.first, temppair.second, binkyposition);
    if (direction.compare("Right") == 0) {
        direction = "Left";
    }
    else if (direction.compare("Left") == 0) {
        direction = "Right";
    }
    else if (direction.compare("Up") == 0) {
        direction = "Down";
    }
    else if (direction.compare("Down") == 0) {
        direction = "Up";
    }
    temppair = targetTileaheadofpacman(temppair, texture, direction, loop, 0, count, mapresloader);
    loop = 0;
    return temppair;
}

void BlueGhost::ghostprops(Texture& texture, std::string direction, Map& mapresloader)
{
    if (Mode != 1 || reincarnating == 1) {
        Pair dest;
        Pair src = std::make_pair(29 - (int)((texture.BlueGhost.getPosition().x / 16.0) + 1), (texture.BlueGhost.getPosition().y / 16.0) + 1);
        if (Mode == 0) {
            dest = target(texture, direction, mapresloader);
            aStarSearch( src, dest, ghostdirection, texture.BlueGhost, mapresloader);
        }
        if (Mode == 2) {
            dest = scatterpairs[scatterpoint];
            if (aStarSearch( src, dest, ghostdirection, texture.BlueGhost, mapresloader)) {
                scatterpoint = (scatterpoint + 1) % 4;
                dest = scatterpairs[scatterpoint];
                aStarSearch( src, dest, ghostdirection, texture.BlueGhost, mapresloader);
            }
        }
        if (reincarnating == 1) {
            dest = std::make_pair(14, 17);
            aStarSearch( src, dest, ghostdirection, texture.BlueGhost, mapresloader);

        }
    }

    if (reincarnating == 0) {
        //Animation half
        if (ghostdirection.compare("Right") == 0) {
            leftintrect = resetvalue = 6 * 15;
        }
        else if (ghostdirection.compare("Left") == 0) {
            leftintrect = resetvalue = 4 * 15;
        }
        else if (ghostdirection.compare("Down") == 0) {
            leftintrect = resetvalue = 2 * 15;
        }
        else if (ghostdirection.compare("Up") == 0) {
            leftintrect = resetvalue = 0;
        }
        texture.BlueGhost.setTextureRect(sf::IntRect(resetvalue, spritelocation, 15, 15));
    }
}

void BlueGhost::ghostintersecmove(Texture& texture, std::string direction, Map& mapresloader)
{
    bool isintersecright = mapresloader.intersection(((texture.BlueGhost.getPosition().x - ghostgap) / 16.0) + 1, (texture.BlueGhost.getPosition().y / 16.0) + 1);
    bool isintersecleft = mapresloader.intersection(((texture.BlueGhost.getPosition().x + ghostgap) / 16.0) + 1, (texture.BlueGhost.getPosition().y / 16.0) + 1);
    bool isintersecdown = mapresloader.intersection((texture.BlueGhost.getPosition().x / 16.0) + 1, ((texture.BlueGhost.getPosition().y - ghostgap) / 16.0) + 1);
    bool isintersecup = mapresloader.intersection((texture.BlueGhost.getPosition().x / 16.0) + 1, ((texture.BlueGhost.getPosition().y + ghostgap) / 16.0) + 1);
    
    entered = 0;
    if ((ghostdirection.compare("Right") == 0 && isintersecright && isintersecleft)) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.BlueGhost, "Right", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.BlueGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);

    }
    if (ghostdirection.compare("Down") == 0 && isintersecdown && isintersecup) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.BlueGhost, "Down", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.BlueGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Left") == 0 && isintersecleft && isintersecright) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.BlueGhost, "Left", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.BlueGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Up") == 0 && isintersecup && isintersecdown) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.BlueGhost, "Up", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.BlueGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (entered == 0) {
        callonce = 0;
    }
    if (reincarnating == 0) {
        if (Mode != 1) {
            animate(texture.BlueGhost, animateclock, leftintrect, resetvalue, spritelocation, 0);
        }
        else {
            if ((levelparameters[Level][7] - Timer.getElapsedTime().asSeconds()) <= 2.0) {
                animate(texture.BlueGhost, animateclock, leftintrect, 8 * 15, 15, 1);
            }
            else
                animate(texture.BlueGhost, animateclock, leftintrect, 8 * 15, 15, 0);
        }
    }
}

bool BlueGhost::iscapture(Texture& texture)
{
    return Ghost::iscapture(texture.BlueGhost, texture);
}
