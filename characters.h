#pragma once


#include "map.h"


class Characters
{
private:
	//varaible 
	int HP;
	int stamina; 	//distance that the character can go
	int team;
	int type;
	int Damage;

	sf::Sprite appearance;
	sf::Texture walktextures;
	sf::Texture slashtextures;
	sf::Texture hurttextures;
	sf::Texture idoltextures;

	bool alive;
	bool isSlashinganimationEnd = true;
	bool isWalkinganimationEnd = true;
	bool chosen = false;
	bool Spawn = false;
	bool ChosenAsTarget = false;

	std::string facedirection = "front";
	std::string detectingdirection = "None";
	std::string state = "idle";


	//animation/action varaibles

	int slashframe=1;
	int walkframe=1;
	int idleframe=1;
	int hurtframe=1;
	int slashframetimer=0;
	int walkframetimer=0;
	int idleframetimer=0;
	int hurtframetimer=0;
	int totalBlockToGo=0;
	int BlocksHaveBeenTo = 0;;
	int detectDirectionCounter = 1;
	bool ObstacleOnFacr = false;

	//initialization 
	void initidletextures(const std::string& idol);
	void initslashtextures(const std::string& slash);
	void initwalktextures(const std::string& walk);
	void inithurttextures(const std::string& hurt);

public:

	//change varaibels functions
	void setHP(int hp);
	int readHP();

	void setstamina(int stmna);
	int readstamina();

	int readDamage();

	sf::Sprite getappearance();

	bool isAlive();

	void setFaceDirecntion(std::string ChangeFaceDirection);

	std::string getstate();
	void setstate(std::string setstate);

	bool IsSlashingAnimationEnd();
	bool IsWalkingAnimationEnd();

	bool isChosen();
	void setChosen(bool trueorfalse);
	
	void isSpawn()
	{
		this->Spawn = true;
	};

	int getTeam();

	std::string getFaceDirection();
	void setFaceDirection(std::string changefacederection);

	std::string getDetectingDirection();

	void SetIsChosenAsTarget(bool state);

	bool IsChosenAsTarget();


	//constructor and destructor
	Characters(int initHP, int initstamina, int initDamage,
		const std::string& idol, const std::string& slash,
		const std::string& walk, const std::string& hurt,
		int initteam, int inittype);
	virtual ~Characters();

	//animation functions
	void idleanimation(float spawnpointX, float spawnpointY);
	void slashanimation();
	int distanceX;						// these 2 varaible and 1 function are related
	int distanceY;						//
	std::vector<std::pair<int, int>> path;     //
	void walk();						//
	void hurtanimation();


	//functions
	void attack(Characters* target);
	void upgrade();
	void CheckAlive();

};


class Playercharacters02 : public Characters
{

};