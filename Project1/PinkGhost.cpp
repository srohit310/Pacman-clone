#include "PinkGhost.h"

PinkGhost::PinkGhost() : speed{ 0.9*0.75,0.4,1.6 }, scatterTimings{ 7.0f, 20.0f, 7.0f, 20.0f, 5.0f, 20.0f, 5.0f }
{
    ghostgap = 7.00;
    Mode = 2;
    revdirectiontrigger = 0;
    scatterpairs.push_back(std::make_pair(27, 4));
    scatterpairs.push_back(std::make_pair(27, 8));
    scatterpairs.push_back(std::make_pair(22, 8));
    scatterpairs.push_back(std::make_pair(22, 4));
    scatterpoint = 0;
    reincarnating = 0;
    spritelocation = 30;
    scatterset = 0;
    loop = 0;
    callonce = 0;
    entered = 0;
    std::cout << "Pink Ghost Loaded\n";
}

void PinkGhost::reset()
{
    Ghost::reset(Mode, revdirectiontrigger, scatterpoint, reincarnating, scatterset, callonce, entered, ghostdirection,pinkscattertrigger, speed, scatterTimings, Level);
}

void PinkGhost::scatter()
{
    if (scatterset < 7) {
        if (Mode != 1) {
            if (pinkscattertrigger.getElapsedTime() >= sf::seconds(scatterTimings[scatterset])) {
                if (scatterset % 2 == 0)
                    Mode = 0;
                else Mode = 2;
                scatterset++;
                pinkscattertrigger.restart();
            }
        }
        else {
            pinkscattertrigger.restart();
        }
    }
}

void PinkGhost::frightenedstatebeg()
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

void PinkGhost::frightenedstateend(Texture& texture, Map& mapresloader)
{
    if (TriggerMode) {
        if (Timer.getElapsedTime().asSeconds() >= levelparameters[Level][7]) {
            TriggerMode = false;
            Mode = prevmode;

        }
        if (reincarnating == 1) {
            Timer.restart();
        }
        if (mapresloader.reachhouse(texture.PinkGhost)) {
            TriggerMode = false;
            Timer.restart();
            Mode = prevmode;
            reincarnating = 0;
            texture.seteyes(0, texture.PinkGhost);
        }
    }
}

void PinkGhost::pinkmove(Texture& texture)
{
    Ghost::ghostmove(texture.PinkGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
}


void PinkGhost::ghostprops(Texture& texture, std::string direction, Map& mapresloader)
{
    if (Mode != 1 || reincarnating == 1) {
        Pair dest;
        Pair src = std::make_pair(29 - (int)((texture.PinkGhost.getPosition().x / 16.0) + 1), (texture.PinkGhost.getPosition().y / 16.0) + 1);
        if (Mode == 0) {
            dest = targetTileaheadofpacman(std::make_pair(29 - ((int)(texture.spritepacman.getPosition().x / 16.0) + 1), (texture.spritepacman.getPosition().y / 16.0) + 1),texture, direction,loop,0,6, mapresloader);
            loop = 0;
            aStarSearch(src, dest, ghostdirection,texture.PinkGhost, mapresloader);
        }
        if (Mode == 2) {
            dest = scatterpairs[scatterpoint];
            if (aStarSearch(src, dest, ghostdirection, texture.PinkGhost, mapresloader)) {
                scatterpoint = (scatterpoint + 1) % 4;
                dest = scatterpairs[scatterpoint];
                aStarSearch(src, dest, ghostdirection, texture.PinkGhost, mapresloader);
            }
        }
        if (reincarnating == 1) {
            dest = std::make_pair(14, 17);
            aStarSearch( src, dest, ghostdirection, texture.PinkGhost, mapresloader);

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
        texture.PinkGhost.setTextureRect(sf::IntRect(resetvalue, spritelocation, 15, 15));
    }
}

void PinkGhost::ghostintersecmove(Texture& texture, std::string direction, Map& mapresloader)
{
    bool isintersecright = mapresloader.intersection(((texture.PinkGhost.getPosition().x - ghostgap) / 16.0) + 1, (texture.PinkGhost.getPosition().y / 16.0) + 1);
    bool isintersecleft = mapresloader.intersection(((texture.PinkGhost.getPosition().x + ghostgap) / 16.0) + 1, (texture.PinkGhost.getPosition().y / 16.0) + 1);
    bool isintersecdown = mapresloader.intersection((texture.PinkGhost.getPosition().x / 16.0) + 1, ((texture.PinkGhost.getPosition().y - ghostgap) / 16.0) + 1);
    bool isintersecup = mapresloader.intersection((texture.PinkGhost.getPosition().x / 16.0) + 1, ((texture.PinkGhost.getPosition().y + ghostgap) / 16.0) + 1);
    entered = 0;
    if ((ghostdirection.compare("Right") == 0 && isintersecright && isintersecleft)) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.PinkGhost, "Right", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.PinkGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);

    }
    if (ghostdirection.compare("Down") == 0 && isintersecdown && isintersecup) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.PinkGhost, "Down", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.PinkGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Left") == 0 && isintersecleft && isintersecright) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.PinkGhost, "Left", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.PinkGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Up") == 0 && isintersecup && isintersecdown) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, direction, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.PinkGhost, "Up", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, direction, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.PinkGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (entered == 0) {
        callonce = 0;
    }
    if (reincarnating == 0) {
        if (Mode != 1) {
            animate(texture.PinkGhost, animateclock, leftintrect, resetvalue, spritelocation, 0);
        }
        else {
            if ((levelparameters[Level][7] - Timer.getElapsedTime().asSeconds()) <= 2.0) {
                animate(texture.PinkGhost, animateclock, leftintrect, 8 * 15, 15, 1);
            }
            else
                animate(texture.PinkGhost, animateclock, leftintrect, 8 * 15, 15, 0);
        }
    }
}

bool PinkGhost::iscapture(Texture& texture)
{
    return Ghost::iscapture(texture.PinkGhost, texture);
}
