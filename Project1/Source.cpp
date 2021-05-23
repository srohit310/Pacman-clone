#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Game.h"
#include <iostream>

Game game;

int main()
{
    int setpause = 0;

    while (game.getIsWindowOpen()) {

        //Update
        if (setpause == 0)
            setpause = game.Update();
        //Rendere
        setpause = game.Render();
    }

    //Game ends
    return 0;
}