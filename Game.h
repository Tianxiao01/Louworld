#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "characters.h"
#include "UImenue.h"

class Game 
{
private :
	// arrays representing the terrians
	int TerrainsState[13][13]= {	{999, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },   //x axis *64, y axis *64
									{ 0 , 0 , 0 , 0 , 0 ,999,999, 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 ,999, 0 , 0 , 0 , 0 , 0 , 0 , 0 },    //0 means the block is not occupied
									{ 0 , 0 , 0 , 0 , 0 ,999, 0 , 0 , 0 , 0 , 0 , 0 , 0 },    //1 means team1 character is on the block
									{999,999, 0 ,999,999,999, 0 , 0 , 0 , 0 , 0 , 0 , 0 },    //2 means team2 character is on the block
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },    //9 means the block is not passable
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
									{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } };  // the terrainstatearray will be an attibute of 
																							  // class Map and each map have different array

	sf::RectangleShape border;

	//general varaible
	int operating_team = 1;

	//movement varaibles
	int Block_clicking_onX;
	int Block_clicking_onY;
	bool ABlockischosen = false;
	bool ACharacterischosen = false;
	int team_characterChosen = 0;

	//attack varaibles
	sf::Vector2f targetPosition;
	bool aTargetIsChosen=false;

	//variabel & window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videomode;
	//playercharacters
	Characters* swordman;
	std::vector<Characters*> swordmanpointers;
	Characters* knight;
	Characters* shellman;
	//AIcharacters
	Characters* orc_axe;
	//map
	Map* map;
	//characters vecter
	std::vector<Characters*> playablecharacters;
	std::vector<Characters*> AIcharacters;
	std::vector<Characters*> Allcharacters;

	//input variables
	sf::Vector2i localMousePosition;
	std::string ButtonClicked="None";

	//initial initialization
	void initVariables();
	void initplayercharacters();
	void initmaps();
	void initWindow();
	void initUImenue();

	// ingame initialization
	void initnewunits();

public :
	//constructor and destructor
	Game();
	virtual ~Game();

	//accessory
	const bool running() const;

	//functions
	void pollevent();
	void GetMouseActivity();

	void checkTerrainstate();
	void checkCharactersState();

	void drawBorder(sf::RectangleShape& border);
	void MeasureDistance();
	void calculatedistance();
	void Construct_path(Characters* character, sf::Vector2i goal);

	void identifymovement();
	bool detect_while_walk(Characters* target);
	void updatePlayerCharacters();
	void updateAICharacters();
	void updatecharacters();
	void updateterrains();
	void rendercharacters();
	void rendermap();

	void update();
	void render();
};

#endif 
