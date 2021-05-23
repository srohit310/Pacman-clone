#include "OrangeGhost.h"

OrangeGhost::OrangeGhost() : speed{0.9* 0.75,0.4,1.6 }, scatterTimings{ 7.0f, 20.0f, 7.0f, 20.0f, 5.0f, 20.0f, 5.0f }
{
    ghostgap = 7.00;
    Mode = 2;
    revdirectiontrigger = 0;
    scatterpairs.push_back(std::make_pair(22, 26));
    scatterpairs.push_back(std::make_pair(27, 32));
    scatterpairs.push_back(std::make_pair(16, 32));
    scatterpairs.push_back(std::make_pair(19, 26));
    scatterpoint = 0;
    reincarnating = 0;
    spritelocation = 60;
    scatterset = 0;
    callonce = 0;
    entered = 0;
    std::cout << "Orange Ghost Loaded\n";
}

void OrangeGhost::reset()
{
    Ghost::reset(Mode, revdirectiontrigger, scatterpoint, reincarnating, scatterset, callonce, entered, ghostdirection, orangescattertrigger, speed, scatterTimings, Level);
}

void OrangeGhost::scatter()
{
    if (scatterset < 7) {
        if (Mode != 1) {
            if (orangescattertrigger.getElapsedTime() >= sf::seconds(scatterTimings[scatterset])) {
                if (scatterset % 2 == 0)
                    Mode = 0;
                else Mode = 2;
                scatterset++;
                orangescattertrigger.restart();
            }
        }
        else {
            orangescattertrigger.restart();
        }
    }
}

void OrangeGhost::frightenedstatebeg()
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

void OrangeGhost::frightenedstateend(Texture& texture, Map& mapresloader)
{
    if (TriggerMode) {
        if (Timer.getElapsedTime().asSeconds() >= levelparameters[Level][7]) {
            
            TriggerMode = false;
            Mode = prevmode;

        }
        if (reincarnating == 1) {
            Timer.restart();
        }
        if (mapresloader.reachhouse(texture.OrangeGhost)) {
            TriggerMode = false;
            Timer.restart();
            Mode = prevmode;
            reincarnating = 0;
            texture.seteyes(0, texture.OrangeGhost);
        }
    }
}

void OrangeGhost::Orangemove(Texture& texture)
{
    Ghost::ghostmove(texture.OrangeGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);

}

void OrangeGhost::ghostprops(Texture& texture, Map& mapresloader)
{
    if (Mode != 1 || reincarnating == 1) {
        Pair dest;
        Pair src = std::make_pair(29 - (int)((texture.OrangeGhost.getPosition().x / 16.0) + 1), (texture.OrangeGhost.getPosition().y / 16.0) + 1);
        if (Mode == 0) {
            dest = std::make_pair(29 - ((int)(texture.spritepacman.getPosition().x / 16.0) + 1), (texture.spritepacman.getPosition().y / 16.0) + 1);
            double range = calculateHValue(src.first, src.second, dest);
            if (range >= 8) {
                aStarSearch( src, dest, ghostdirection,texture.OrangeGhost, mapresloader);
            }
            if (range < 8) {
                dest = scatterpairs[scatterpoint];
                if (aStarSearch( src, dest, ghostdirection, texture.OrangeGhost, mapresloader)) {
                    scatterpoint = (scatterpoint + 1) % 4;
                    dest = scatterpairs[scatterpoint];
                    aStarSearch( src, dest, ghostdirection, texture.OrangeGhost, mapresloader);
                }
            }
        }
        if (Mode == 2) {
            dest = scatterpairs[scatterpoint];
            if (aStarSearch( src, dest, ghostdirection, texture.OrangeGhost, mapresloader)) {
                scatterpoint = (scatterpoint + 1) % 4;
                dest = scatterpairs[scatterpoint];
                aStarSearch( src, dest, ghostdirection, texture.OrangeGhost, mapresloader);
            }
        }
        if (reincarnating == 1) {
            dest = std::make_pair(14, 17);
            aStarSearch( src, dest, ghostdirection, texture.OrangeGhost, mapresloader);
        }
    }
    //Animation half
    if (reincarnating == 0) {
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
        texture.OrangeGhost.setTextureRect(sf::IntRect(resetvalue, spritelocation, 15, 15));
    }
}

void OrangeGhost::ghostintersecmove(Texture& texture, Map& mapresloader)
{
    bool isintersecright = mapresloader.intersection(((texture.OrangeGhost.getPosition().x - ghostgap) / 16.0) + 1, (texture.OrangeGhost.getPosition().y / 16.0) + 1);
    bool isintersecleft = mapresloader.intersection(((texture.OrangeGhost.getPosition().x + ghostgap) / 16.0) + 1, (texture.OrangeGhost.getPosition().y / 16.0) + 1);
    bool isintersecdown = mapresloader.intersection((texture.OrangeGhost.getPosition().x / 16.0) + 1, ((texture.OrangeGhost.getPosition().y - ghostgap) / 16.0) + 1);
    bool isintersecup = mapresloader.intersection((texture.OrangeGhost.getPosition().x / 16.0) + 1, ((texture.OrangeGhost.getPosition().y + ghostgap) / 16.0) + 1);
    entered = 0;
    if ((ghostdirection.compare("Right") == 0 && isintersecright && isintersecleft)) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.OrangeGhost, "Right", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.OrangeGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Down") == 0 && isintersecdown && isintersecup) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.OrangeGhost, "Down", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.OrangeGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Left") == 0 && isintersecleft && isintersecright) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.OrangeGhost, "Left", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.OrangeGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (ghostdirection.compare("Up") == 0 && isintersecup && isintersecdown) {
        entered = 1;
        if (Mode == 1) {
            if (reincarnating == 1) {
                ghostprops(texture, mapresloader);
            }
            else if (callonce == 0) {
                ghostdirection = random_direction_generator(texture.OrangeGhost, "Up", mapresloader);
                callonce = 1;
            }
        }
        else if (callonce == 0) {
            ghostprops(texture, mapresloader);
            callonce = 1;
        }
        Ghost::ghostmove(texture.OrangeGhost, Mode, speed, revdirectiontrigger, reincarnating, ghostdirection, spritelocation);
    }
    if (entered == 0) {
        callonce = 0;
    }
    if (reincarnating == 0) {
        if (Mode != 1) {
            animate(texture.OrangeGhost, animateclock, leftintrect, resetvalue, spritelocation, 0);
        }
        else {
            if ((levelparameters[Level][7] - Timer.getElapsedTime().asSeconds()) <= 2.0) {
                animate(texture.OrangeGhost, animateclock, leftintrect, 8 * 15, 15, 1);
            }
            else
                animate(texture.OrangeGhost, animateclock, leftintrect, 8 * 15, 15, 0);
        }
    }
}

bool OrangeGhost::iscapture(Texture& texture)
{
    return Ghost::iscapture(texture.OrangeGhost, texture);
}
