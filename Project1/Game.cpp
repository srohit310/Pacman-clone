#include "Game.h"

//priv functions

void Game::initvariable()
{
    this->window = nullptr;
    activeghosts = 0;
    flag = 0;
    triggerdeathanimation = 0;
    Lives = 3;
    Level = 0;

}

void Game::initwindow()
{
    this->videomode.height = 600;
    this->videomode.width = 480;
    this->window = new sf::RenderWindow(this->videomode, "Pacman", sf::Style::Titlebar);
    this->window->setFramerateLimit(150);
}

//constructors and destructors

Game::Game() : activateghosttiminings {3.0f,2.0f,4.0f,4.0f}, mapresloader(texture)
{
    this->initvariable();
    this->initwindow();
    red.ghostprops(texture,mapresloader);
    pink.ghostprops(texture,pacman.getdirection(), mapresloader);
    blue.ghostprops(texture, pacman.getdirection(), mapresloader);
    orange.ghostprops(texture, mapresloader);
    for (int i = 0; i < 4; i++)
        isfrightened[i] = false;
    fruitspawn = false;
    HighScore = 0;
    liferegen = 1;
    loadhighscore();
    std::cout << "\n PRESS E TO EXIT\n";
}

Game::~Game()
{
    delete this->window;
}

//accessors

void Game::reset()
{
    red.reset();
    pink.reset();
    blue.reset();
    orange.reset();
    pacman.reset();
    texture.resetpositions();
    red.ghostprops(texture, mapresloader);
    pink.ghostprops(texture, pacman.getdirection(), mapresloader);
    blue.ghostprops(texture, pacman.getdirection(), mapresloader);
    orange.ghostprops(texture, mapresloader);
    activeghosts = 0;
    activateghosts.restart();
    triggerdeathanimation = 0;
    flag = 0;
    for (int i = 0; i < 4; i++)
        isfrightened[i] = false;
    fruitspawn = false;
}

void Game::loadhighscore()
{
    std::ifstream fin;
    fin.open("E:/Highscore.dat", std::ios::in | std::ios::binary);
    fin.read((char*)&loadedhighscore, sizeof(long));
}

void Game::checkghostcollision()
{
    if (red.iscapture(texture)) {
        if (red.Mode != 1) {
            pacman.resetvalue = 0;
            triggerdeathanimation = 1;
            Lives--;
        }
        else if(red.reincarnating ==0){
            red.reincarnating = 1;
            isfrightened[0] = true;
            triggerdeathanimation = 1;
            texture.setpoints(ghostcapturecount, texture.RedGhost);
            HighScore = HighScore + pow(2, ghostcapturecount + 1) * 100;
            ghostcapturecount++;
        }
    }
    if (pink.iscapture(texture)) {
        if (pink.Mode != 1) {
            triggerdeathanimation = 1;
            pacman.resetvalue = 0;
            Lives--;
        }
        else if (pink.reincarnating == 0) {
            pink.reincarnating = 1;
            isfrightened[1] = true; 
            triggerdeathanimation = 1;
            texture.setpoints(ghostcapturecount, texture.PinkGhost);
            HighScore = HighScore + pow(2, ghostcapturecount + 1) * 100;
            ghostcapturecount++;
        }
    }
    if (blue.iscapture(texture)) {
        if (blue.Mode != 1) {
            triggerdeathanimation = 1;
            pacman.resetvalue = 0;
            Lives--;
        }
        else if (blue.reincarnating == 0) {
            blue.reincarnating = 1;
            isfrightened[2] = true;
            triggerdeathanimation = 1;
            texture.setpoints(ghostcapturecount, texture.BlueGhost);
            HighScore = HighScore + pow(2, ghostcapturecount + 1) * 100;
            ghostcapturecount++;
        }
    }
    if (orange.iscapture(texture)) {
        if (orange.Mode != 1) {
            triggerdeathanimation = 1;
            pacman.resetvalue = 0;
            Lives--;
        }
        else if (orange.reincarnating == 0) {
            orange.reincarnating = 1;
            isfrightened[3] = true;
            triggerdeathanimation = 1;
            texture.setpoints(ghostcapturecount, texture.OrangeGhost);
            HighScore = HighScore + pow(2, ghostcapturecount + 1) * 100;
            ghostcapturecount++;
        }
    }
}

void Game::frightentiming()
{
    int pelletsize = mapresloader.pellet((int)(texture.spritepacman.getPosition().x / 16.0), (int)(texture.spritepacman.getPosition().y / 16.0),texture);
    if (pelletsize == 10) {
        HighScore += 10;
    }
    if (pelletsize == 50) {
     
        HighScore += 50;
        ghostcapturecount = 0;
        if (activeghosts > 0)
            red.frightenedstatebeg();
        if (activeghosts > 1)
            pink.frightenedstatebeg();
        if (activeghosts > 2)
            blue.frightenedstatebeg();
        if (activeghosts > 3)
            orange.frightenedstatebeg();
    }
    if (activeghosts > 0)
        red.frightenedstateend(texture, mapresloader);
    if (activeghosts > 1)
        pink.frightenedstateend(texture, mapresloader);
    if (activeghosts > 2)
        blue.frightenedstateend(texture, mapresloader);
    if (activeghosts > 3)
        orange.frightenedstateend(texture, mapresloader);
}

const bool Game::getIsWindowOpen()
{
    return this->window->isOpen();
}

//functions

void Game::pollevents()
{


    while (this->window->pollEvent(event)) {


        switch (event.type) {

        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            
            if (event.key.code == sf::Keyboard::E)
                this->window->close();

            if (event.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (activeghosts > 0) {
                if (event.key.code == sf::Keyboard::Right && pacman.flagright == 0) {
                    pacman.polleventresult("Right", texture);
                }
                else if (event.key.code == sf::Keyboard::Right)
                    pacman.buffereddirec = "Right";

                if (event.key.code == sf::Keyboard::Down && pacman.flagdown == 0) {
                    pacman.polleventresult("Down", texture);
                }
                else if (event.key.code == sf::Keyboard::Down)
                    pacman.buffereddirec = "Down";

                if (event.key.code == sf::Keyboard::Left && pacman.flagleft == 0) {

                    pacman.polleventresult("Left", texture);
                }
                else if (event.key.code == sf::Keyboard::Left)

                    pacman.buffereddirec = "Left";
                if (event.key.code == sf::Keyboard::Up && pacman.flagup == 0) {

                    pacman.polleventresult("Up", texture);
                }
                else if (event.key.code == sf::Keyboard::Up)
                    pacman.buffereddirec = "Up";

            }
            break;

        }
    }
}

void Game::fruitspawns()
{
    if (mapresloader.retpelletsleft() == 244 - 70) {
        fruitspawn = true;
        fruitTimer.restart();
    }
    if (mapresloader.retpelletsleft() == 244 - 170) {
        fruitspawn = true;
        fruitTimer.restart();
    }
    if (fruitspawn == true) {
        if (fruitTimer.getElapsedTime().asSeconds() >= 10.0f) {
            fruitspawn = false;
        }
        if (texture.fruitcollision(texture.spritepacman)) {
            HighScore += texture.bonus[Level].score;
            fruitTimer.restart();
        }
    }
    
}

void Game::levelincrement()
{
    Level++;
    red.Level++;
    pink.Level++;
    blue.Level++;
    orange.Level++;
    pacman.Level++;
    for (int i = 0; i < 4; i++) {
        activateghosttiminings[i] -= 0.5f;
    }
}

void Game::savehighscore()
{
    std::ofstream fout;
    fout.open("E:/Highscore.dat", std::ios::out | std::ios::binary);
    fout.write((char*)&HighScore, sizeof(HighScore));
    fout.close();
}

int Game::Update()
{   
    //block of code to activate the ghosts based on a timer
    if (HighScore > liferegen * 10000) {
        Lives++;
        liferegen++;
    }
    if (loadedhighscore < HighScore) {
        loadedhighscore = HighScore;
    }
    if(activeghosts<4)
        if (activateghosts.getElapsedTime().asSeconds() >= activateghosttiminings[activeghosts]) {
            activeghosts++;
            if (activeghosts > 0)
                triggerdeathanimation = 0;
            if (activeghosts == 1)
                red.redscattertrigger.restart();
            if (activeghosts == 2)
                pink.pinkscattertrigger.restart();
            if (activeghosts == 3)
                blue.bluescattertrigger.restart();
            if (activeghosts == 4)
                orange.orangescattertrigger.restart();
            activateghosts.restart();
            if (activeghosts == 4) {
                flag = 1;
            }
        }
    if (flag == 1) {
        activateghosts.restart();
    }

    pacman.collision(texture, mapresloader);
    
    this->pollevents();

    if (activeghosts > 0)
    red.ghostintersecmove(texture, mapresloader);
    if (activeghosts > 1)
        pink.ghostintersecmove(texture,pacman.getdirection(), mapresloader);
    if (activeghosts > 2)
        blue.ghostintersecmove(texture, pacman.getdirection(), mapresloader);
    if (activeghosts > 3)
        orange.ghostintersecmove(texture, mapresloader);
    
    if (activeghosts > 0)
        red.scatter();
    if (activeghosts > 1)
        pink.scatter();
    if (activeghosts > 2)
        blue.scatter();
    if (activeghosts > 3)
        orange.scatter();
    pacman.bufferdirec(texture);

    mapresloader.teleport(texture.spritepacman);
    mapresloader.teleport(texture.RedGhost);
    mapresloader.teleport(texture.PinkGhost);
    mapresloader.teleport(texture.BlueGhost);
    mapresloader.teleport(texture.OrangeGhost);
    
    checkghostcollision();

    frightentiming();

    if (clock.getElapsedTime().asSeconds() >= 0.0015f) {
        pacman.move(texture);
        if (activeghosts > 0)
        red.Redmove(texture);
        if (activeghosts > 1)
            pink.pinkmove(texture);
        if (activeghosts > 2)
            blue.bluemove(texture);
        if (activeghosts > 3)
            orange.Orangemove(texture);
        clock.restart();
    }

    fruitspawns();
    return triggerdeathanimation;
}

int Game::Render()
{
    if (mapresloader.retpelletsleft() == 0) {
        if (clock1.getElapsedTime().asSeconds() >= 1.50f) {
            if (Level < 7)
                levelincrement();
            reset();
            mapresloader.MapReset(texture);
            return 0;
        }
        return 1;
    }

    if (clock1.getElapsedTime().asSeconds() >= 0.15f) {
        if (triggerdeathanimation == 0) {
            if (texture.rectleft() == pacman.resetvalue + 30) {
                texture.setintrect(pacman.resetvalue, 0);
            }
            else {
                texture.setintrect(texture.rectleft() + 15, 0);
            }
            clock1.restart();
        }
        else if(pacman.resetvalue<180 && !(isfrightened[0] || isfrightened[1] || isfrightened[2] || isfrightened[3])){
            texture.intrect = sf::IntRect(pacman.resetvalue , 75 , 15, 15);
            texture.spritepacman.setTextureRect(texture.intrect);
            pacman.resetvalue += 15;
            clock1.restart();
        }
    }

    int i = 0;
    if (clock1.getElapsedTime().asSeconds()>= 1.0f) {
        for (i = 0; i < 4; i++) {
            if (isfrightened[i]) {
                switch (i){
                case 0:texture.seteyes(1, texture.RedGhost); break;
                case 1:texture.seteyes(1, texture.PinkGhost); break;
                case 2:texture.seteyes(1, texture.BlueGhost); break;
                case 3:texture.seteyes(1, texture.OrangeGhost); break;
                }
                break;
            }
        }
        if (triggerdeathanimation == 1 && Lives == 0) {
            if (HighScore >= loadedhighscore)
                savehighscore();
            this->window->close();
        }
        if(!(isfrightened[0] || isfrightened[1] || isfrightened[2] || isfrightened[3]))
            reset();
        else isfrightened[i] = false;
        triggerdeathanimation = 0;
        clock1.restart();
    }

    this->window->clear();
    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 36; j++) {
            this->window->draw(mapresloader.maze_layout[i][j]);
        }
    }
    static int entered = 0;
    if (fruitspawn == true || entered == 1) {
        if (texture.fruitcollision(texture.spritepacman) || entered == 1) {
            entered = 1;
            fruitspawn = false;
            this->window->draw(texture.bonus[Level].scoresprite);
            if (fruitTimer.getElapsedTime().asSeconds() >= 1.5f) {
                entered = 0;
            }
        }
        else if (entered == 0)
            this->window->draw(texture.bonus[Level].fruit);
    }
    if (!(isfrightened[0] || isfrightened[1] || isfrightened[2] || isfrightened[3]))
        this->window->draw(texture.spritepacman);
    if (triggerdeathanimation == 0 || (isfrightened[0] || isfrightened[1] || isfrightened[2] || isfrightened[3])) {
        this->window->draw(texture.RedGhost);
        this->window->draw(texture.PinkGhost);
        this->window->draw(texture.BlueGhost);
        this->window->draw(texture.OrangeGhost);
    }
    if (activeghosts == 0) {
        texture.setsign(1);
        this->window->draw(texture.sign);
    }
    if (triggerdeathanimation == 1 && Lives ==0) {
        texture.setsign(2);
        this->window->draw(texture.sign);
    }
    for (i = 0; i < Lives; i++) {
        if (i == 10) break;
        texture.Lives.setPosition(sf::Vector2f(20+30*i, 545));
        this->window->draw(texture.Lives);
    }
    int highscore = HighScore;
    std::stack<int> revhighscore;
    if (HighScore == 0) {
        texture.Number.setTextureRect(sf::IntRect(15, 185, 10, 10));
        texture.Number.setPosition(sf::Vector2f(10, 15));
        this->window->draw(texture.Number);
    }
    while (highscore > 0) {
        int d = highscore % 10;
        revhighscore.push(d);
        highscore = highscore / 10;
    }
    int highcount = 0;
    while (!revhighscore.empty()) {
        int d = revhighscore.top();
        revhighscore.pop();
        texture.Number.setTextureRect(sf::IntRect(15+d*10, 185, 10, 10));
        texture.Number.setPosition(sf::Vector2f(10+highcount*15,15));
        this->window->draw(texture.Number);
        highcount++;
    }
    highscore = loadedhighscore;
    if (highscore == 0) {
        texture.Number.setTextureRect(sf::IntRect(15, 185, 10, 10));
        texture.Number.setPosition(sf::Vector2f(200, 15));
        this->window->draw(texture.Number);
    }
    while (highscore > 0) {
        int d = highscore % 10;
        revhighscore.push(d);
        highscore = highscore / 10;
    }
    highcount = 0;
    while (!revhighscore.empty()) {
        int d = revhighscore.top();
        revhighscore.pop();
        texture.Number.setTextureRect(sf::IntRect(15 + d * 10, 185, 10, 10));
        texture.Number.setPosition(sf::Vector2f(200 + highcount * 15, 15));
        this->window->draw(texture.Number);
        highcount++;
    }
    this->window->display();
    return triggerdeathanimation;
}
