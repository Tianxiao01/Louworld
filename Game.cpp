#include "Game.h"
#include "Pathfinding.h"


//initialization
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initplayercharacters()
{
    //player
    
    
    for (int i = 1;i <= 14;i++)
    {
    
    this->swordman = new Characters(10, 1, 2, "textures/characters/swordman01/swordman01_idle.png",
                                            "textures/characters/swordman01/swordman01_slash.png",
                                            "textures/characters/swordman01/swordman01_walk.png",
                                            "textures/characters/swordman01/swordman01_hurt.png",
                                            1, 1);
    this->playablecharacters.push_back(swordman);
    this->Allcharacters.push_back(swordman);
    this->swordmanpointers.push_back(swordman);
    }
  
    

    this->knight = new Characters(10, 1, 5, "textures/characters/knight02/knight02_idle.png",
                                        "textures/characters/knight02/knight02_slash.png",
                                        "textures/characters/knight02/knight02_walk.png",
                                        "textures/characters/knight02/knight02_hurt.png",
                                        1, 1);
    
    this->playablecharacters.push_back(knight);
    this->Allcharacters.push_back(knight);

    
    this->shellman = new Characters(10, 1, 1,"textures/characters/shellman01/shellman01_idle.png",
                                        "textures/characters/shellman01/shellman01_slash.png",
                                        "textures/characters/shellman01/shellman01_walk.png",
                                        "textures/characters/shellman01/shellman01_hurt.png",
                                        1, 1);

    this->playablecharacters.push_back(shellman);
    this->Allcharacters.push_back(shellman);
    

    //AI

    this->orc_axe = new Characters(10,1,2, "textures/characters/orc_axe01/orc_axe01_idle.png",
                                            "textures/characters/orc_axe01/orc_axe01_slash.png",
                                            "textures/characters/orc_axe01/orc_axe01_walk.png",
                                            "textures/characters/orc_axe01/orc_axe01_hurt.png",
                                            2, 2);

    this->AIcharacters.push_back(orc_axe);
    this->Allcharacters.push_back(orc_axe);
    
}

void Game::initmaps()
{
    this->map = new Map("textures/maps/grassland01_copy.png");
}
    
void Game:: initWindow()
{
    this->videomode.height = 832;
    this->videomode.width = 1082;
    this->window = new sf::RenderWindow(this->videomode, "Louworld");
    this->window->setFramerateLimit(60);
}

//constructor and destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initmaps();
    this->initplayercharacters();
}

Game::~Game()
{
    delete this->window;
    
    
    for (Characters* swordman : swordmanpointers)
    {
        delete this->swordman;
    }
    
    delete this->knight;
    delete this->shellman;
    delete this->orc_axe;
    delete this->map;
}

//accessory
const bool Game::running() const
{
    return this->window->isOpen();
}

//functions
//hardwareacivity detection
void Game::pollevent()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::GetMouseActivity()
{
    this->localMousePosition = sf::Mouse::getPosition(*this->window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    
    {
        this->ButtonClicked = "Left";
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->ButtonClicked = "Right";
    }
    else
    {
        this->ButtonClicked = "None";
    }
}





//check objects' states things
void Game::checkTerrainstate()
{
    int terrainnum = 0;
    for (sf::Sprite& terrain : this->map->TerrainsArray)
    {
        terrainnum++;
        if (this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] != 999)
        {
            bool TerrainChecked = false;
            for (Characters* character : this->Allcharacters)
            {
                if (round(terrain.getPosition().x + 32) == round(character->getappearance().getPosition().x)
                    && round(terrain.getPosition().y + 32) == round(character->getappearance().getPosition().y))
                {
                    if (character->getTeam() == 1)
                    {
                        this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] = 100;  //this->map->Terrainstate[][]=100
                        TerrainChecked = true;
                        //std::cout << this->TerrainsState[0][0] << "\n";
                    }
                    else if (character->getTeam() == 2)
                    {
                        this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] = 200;
                        TerrainChecked = true;
                        //std::cout << this->TerrainsState[12][12] << "\n";
                    }
                }
                else if (TerrainChecked == false)
                {
                    this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] = 0;
                }
            }
        }
        
    }
    //std::cout << this->TerrainsState[0][0] << "\n";
}

void Game::checkCharactersState()
{
    this->GetMouseActivity();
    for (Characters* character : Allcharacters)
    {
        if (character->getappearance().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->localMousePosition)) 
            && this->ButtonClicked=="Left" && this->ACharacterischosen==false)
        {
            character->setChosen(true);
            this->ACharacterischosen = true;
            this->team_characterChosen = character->getTeam();
            //this->damagePoint_chosenChar=character->readDamage();
        }
        else if (character->getappearance().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->localMousePosition))
            && this->ButtonClicked == "Right" && this->ACharacterischosen && character->getTeam()!=this->team_characterChosen)
        {
            character->SetIsChosenAsTarget(true);
            this->targetPosition = character->getappearance().getPosition();
            this->aTargetIsChosen = true;
        }
    }
    /*
    if (operating_team==2)
    {
        for (Characters* character : AIcharacters)
        {

        }
    }
    */
}


//border
void Game::drawBorder(sf::RectangleShape& border)
{
    for (sf::Sprite& terrain : this->map->TerrainsArray)
    {
        if (terrain.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->localMousePosition)))
        {
            border = sf::RectangleShape(sf::Vector2f(terrain.getGlobalBounds().width, terrain.getGlobalBounds().height));
            border.setPosition(terrain.getPosition());
            border.setOutlineThickness(2.f);
            if (ButtonClicked == "None")
            {
                border.setOutlineColor(sf::Color(192, 192, 192));
            }
            else if (ButtonClicked == "left")
            {
                border.setOutlineColor(sf::Color::Red);
            }
            border.setFillColor(sf::Color::Transparent);
        }
    }


}


//walking distance things


void Game::Construct_path(Characters* character, sf::Vector2i goal)
{
    PathFinding pf;
    std::unordered_map<std::pair<int,int>, std::pair<int, int>> came_from;
    std::unordered_map<std::pair<int, int>, double> cost_so_far;

    pf.a_star_search(
        std::pair<int, int>(character->getappearance().getPosition().x, character->getappearance().getPosition().y),
        std::pair<int, int> {goal.x, goal.y},
        came_from,
        cost_so_far,
        this->TerrainsState);


    character->path = pf.returnPath(
        std::pair<int, int>(character->getappearance().getPosition().x, character->getappearance().getPosition().y),
        std::pair<int, int>{goal.x, goal.y},
        came_from);
    /*
    std::cout << character->path.size() << "\n";
    for (int i = 0; i < character->path.size();i++)
    {
        std::cout << character->path[i].first<<" "<< character->path[i].second<<"\n";
    }
    */
}


void Game::MeasureDistance()
{
    if (operating_team == 1)
    {
        int terrainnum = 0;
        for (sf::Sprite& terrain : this->map->TerrainsArray)   //some possible optimization here, kick out all not passable blocks and then iterate
        {
            terrainnum++;
            if (terrain.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->localMousePosition))
                && ButtonClicked == "Left"
                && this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] != 100
                && this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] != 200
                && this->TerrainsState[(terrainnum - 1) / 13][(terrainnum - 1) % 13] != 999)
            {  //&& block number !=999 or 100 or 200
                for (Characters* character : Allcharacters) //playablecharacters
                {
                    if (character->isChosen())
                    {
                        this->Block_clicking_onX = round(terrain.getPosition().x + 32);
                        this->Block_clicking_onY = round(terrain.getPosition().y + 32);
                        ABlockischosen = true;
                        if (character->IsWalkingAnimationEnd())
                        {
                            this->Construct_path(character, sf::Vector2i(this->Block_clicking_onX, this->Block_clicking_onY));
                        }
                    }
                }
            }
        }
    }
    /*
    else if (operating_team == 2)
    {
        for (Characters* character : AIcharacters)
        {
            if (character->isChosen())
            {
                this->Block_clicking_onX = ;  //choose a prior target and froward towards that. if it is in range then attack
                this->Block_clicking_onY = ;
                ABlockischosen = true;
                if (character->IsWalkingAnimationEnd())
                {
                    this->Construct_path(character, sf::Vector2i(this->Block_clicking_onX, this->Block_clicking_onY));
                }
            }
        }
    }  
    */
}





//character logic things
void Game::identifymovement()
{
    this->checkCharactersState();
    this->MeasureDistance();
    
    for (Characters* character : Allcharacters)
    {
        if (character->isChosen())
        {
            if (ABlockischosen && character->IsSlashingAnimationEnd())
            {
                character->setstate("walking");
                ABlockischosen = false;
            }
            else if (this->ButtonClicked == "Right"
                && character->IsWalkingAnimationEnd()
                && this->aTargetIsChosen) //&& TargetIsChosen 
            {
                //enemy direction identification
                character->setstate("slashing");
            }
            else if (this->ButtonClicked == "None"
                && character->IsSlashingAnimationEnd()
                && character->IsWalkingAnimationEnd())
            {
                character->setstate("idle");
            }
            //std::cout << "is chosen" << "\n";
        }
        
        else if (character->isChosen() == false && character->IsChosenAsTarget()==false)
        {
            character->setstate("idle");
            //std::cout << "not chosen" << "\n";
        }
        else if (character->isChosen() == false && character->IsChosenAsTarget())
        {
            //std::cout << character->IsChosenAsTarget() << "\n";
            character->setstate("hurting");
            //character->setHP(character->readHP() - damagepoint of attacker);
        }
    }
}
                                                             


void Game::updatePlayerCharacters()
{
    int spawnpointFactor_Player = 0;
    for (Characters* character : playablecharacters) //update the appearances of characters behind screen
    {
        bool isSpawn = false;
        spawnpointFactor_Player++;

        character->CheckAlive();

        if (character->isAlive())
        {
            /*
            如果没有任何输入时
            执行idolanimation
            如果人物走动（鼠标点击了其它地块，并且二维数组中地块对应数据为“0”）：
            执行walkanimation
                1）右走（目的地x坐标大于出发地）
                2）。。。
            */
            if (character->getstate() == "idle")
            {
                while (isSpawn == false)
                {
                    if (this->TerrainsState[(spawnpointFactor_Player - 1) / 13][(spawnpointFactor_Player - 1) % 13] != 999)
                    {
                        character->idleanimation(((spawnpointFactor_Player - 1) % 13 + 1) * 64 - 32,
                            ((spawnpointFactor_Player - 1) / 13 + 1) * 64 - 32);
                        // the parameters is the spawn point of the character
                        isSpawn = true;
                    }
                    else
                    {
                        spawnpointFactor_Player++;
                    }
                }
            }
            else if (character->getstate() == "slashing")
            {
                character->slashanimation();
                this->aTargetIsChosen = !character->IsSlashingAnimationEnd();
                this->ACharacterischosen = character->isChosen();
            }
            else if (character->getstate() == "walking")
            {
                character->walk(); 
                this->ACharacterischosen = character->isChosen();           
            }
            else if (character->getstate() == "hurting")
            {
                character->hurtanimation();
            }
        }
        /*
        the character will die and remove from the screen (delete the pointer)
        else
        {

        }
        */
    } 
}

void Game::updateAICharacters()
{
    
    int spawnpointFactor_AI = 0;
    for (Characters* character : AIcharacters) //update the appearances of characters behind screen
    {
        bool isSpawn = false;
        spawnpointFactor_AI++;

        character->CheckAlive();

        if (character->isAlive())
        {
            /*
            如果没有任何输入时
            执行idolanimation
            如果人物走动（鼠标点击了其它地块，并且二维数组中地块对应数据为“0”）：
            执行walkanimation
            */
            if (character->getstate() == "idle")
            {
                while (isSpawn == false)
                {
                    if (this->TerrainsState[12 - ((spawnpointFactor_AI - 1) / 13)][12 - ((spawnpointFactor_AI - 1) % 13)] != 999)
                    {
                        character->idleanimation((13 - (spawnpointFactor_AI - 1) % 13) * 64 - 32,
                            (13 - (spawnpointFactor_AI - 1) / 13) * 64 - 32);
                        // the parameters is the spawn point of the character
                        isSpawn = true;
                    }
                    else
                    {
                        spawnpointFactor_AI++;
                    }
                }
            }
            else if (character->getstate() == "slashing")
            {
                character->slashanimation();
                this->aTargetIsChosen = !character->IsSlashingAnimationEnd();
                this->ACharacterischosen = character->isChosen();
            }
            else if (character->getstate() == "walking")
            {
                character->walk();
                this->ACharacterischosen = character->isChosen();
            }
            else if (character->getstate() == "hurting")
            {
                character->hurtanimation();
            }
        }
        /*
        else
        {

        }
        */
    }
}

//update logic things
void Game::updatecharacters()
{
    this->identifymovement();
    this->updatePlayerCharacters();
    this->updateAICharacters();
}

void Game::updateterrains()
{
    this->checkTerrainstate();
}

//render things
void Game::rendercharacters()
{
    for (Characters* character : Allcharacters)
    {
        this->window->draw(character->getappearance());
    }
}

void Game::rendermap()
{
    for (int i = 0;i < 169;i++)
    {
        this->window->draw(this->map->TerrainsArray[i]);
    }
}



// update and render on window
void Game::update()
{
    //detect whether the game is quit
    this->pollevent();

    //get each block's value
    this->updateterrains();

    this->MeasureDistance();
    this->drawBorder(this->border);
    
    this->updatecharacters();
}

void Game::render()
{
    this->window->clear(sf::Color(0, 0, 0));
    this->rendermap();
    this->window->draw(this->border);
    this->rendercharacters();
    this->window->display();
}


/*
我应该在哪里初始化新购买的角色
*/


