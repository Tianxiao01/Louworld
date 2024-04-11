#include "characters.h"

//initialization 

void Characters::initidletextures(const std::string& idol)
{
	if (!this->idoltextures.loadFromFile(idol))
	{
		std::cout << "idoltextures loading failed" << "\n";
	}
}

void Characters::initslashtextures(const std::string& slash)
{
	this->slashtextures.loadFromFile(slash);
}

void Characters::initwalktextures(const std::string& walk)
{
	this->walktextures.loadFromFile(walk);
}

void Characters::inithurttextures(const std::string& hurt)
{
	this->hurttextures.loadFromFile(hurt);
}



//constructor and destructor
Characters::Characters(int initHP, int initstamina, int initDamage,
								   const std::string& idol, const std::string& slash, 
								   const std::string& walk, const std::string& hurt, 
								   int initteam,int inittype)
{
	this->HP=initHP;
	this->stamina = initstamina;
	this->team = initteam;
	this->type = inittype;
	this->alive = true;
	this->initidletextures(idol);
	this->initslashtextures(slash);
	this->initwalktextures(walk);
	this->inithurttextures(hurt);
}


Characters::~Characters()
{

}






//manage variables functions
void Characters::setHP(int hp)
{
	this->HP = hp;
}

int Characters::readHP()
{
	return this->HP;
}

void Characters::setstamina(int stmna)
{
	this->stamina = stmna;
}

int Characters::readstamina()
{
	return this->stamina;
}

int Characters::readDamage()
{
	return this->Damage;
}

sf::Sprite Characters::getappearance()
{
	return appearance;
}

bool Characters::isAlive()
{
	return true;
}

void Characters::setFaceDirecntion(std::string ChangeFaceDirection)
{
	this->facedirection = ChangeFaceDirection;
}

std::string Characters::getstate()
{
	return this->state;
}

void Characters::setstate(std::string setstate)
{
	this->state = setstate;
}

bool Characters::IsSlashingAnimationEnd()
{
	return this->isSlashinganimationEnd;
}

bool Characters::IsWalkingAnimationEnd()
{
	return this->isWalkinganimationEnd;
}

bool Characters::isChosen()
{
	return this->chosen;
}
void Characters::setChosen(bool trueorfalse)
{
	this->chosen = trueorfalse;
}

int Characters::getTeam() 
{
	return this->team;
}


std::string Characters::getFaceDirection()
{
	return facedirection;
}

std::string Characters::getDetectingDirection()
{
	return this->detectingdirection;
}


void Characters::SetIsChosenAsTarget(bool state)
{
	this->ChosenAsTarget = state;
}

bool Characters::IsChosenAsTarget()
{
	return this->ChosenAsTarget;
}


//animation functions

void Characters::idleanimation(float spawnpointX, float spawnpointY)
{
	/*
	此类型函数将改变appearance的值：
	每次执行一遍都会增加frametimer的数值，当frametimer到达frametimeMax时，
	appearance的texture将变为加载图片的另一区域 （将所有区域事先存入vector？） 
	*/
	
	this->detectingdirection = "None";

	if (this->Spawn == false)
	{
		this->appearance.setPosition(spawnpointX, spawnpointY); // spawn point
		this->isSpawn();
	}
	

	this->appearance.setTexture(idoltextures);

	const int frametimerMax = 20;
	const int totalframes = 2;


	sf::IntRect frames[2];

	if (this->facedirection == "front")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 2,64,64) };
		}
	}
	else if (this->facedirection == "back")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 0,64,64) };
		}
	}
	else if (this->facedirection == "left")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 1,64,64) };
		}
	}
	else if (this->facedirection == "right")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 3,64,64) };
		}
	}


	if (idleframe <= totalframes)
	{
		if (this->idleframetimer < frametimerMax)
		{
			this->appearance.setTextureRect(frames[idleframe - 1]);
			this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
			this->idleframetimer++;
		}
		else
		{

			idleframe++;
			this->idleframetimer = 0;
		}
	}
	else
	{
		this->appearance.setTextureRect(frames[0]);
		this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
		idleframe = 1;
	}
}

void Characters::slashanimation()
{	
	this->appearance.setTexture(this->slashtextures);
	const int frametimerMax = 6;
	const int totalframes = 5;
	sf::IntRect frames[totalframes];


	if (this->type==1)
	{
		if (this->facedirection == "front")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(192 * i,192 * 2,192,192) };
			}
		}
		else if (this->facedirection == "back")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(192 * i,192 * 0 ,192,192) };
			}
		}
		else if (this->facedirection == "left")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(192 * i,192 * 1,192,192) };
			}
		}
		else if (this->facedirection == "right")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(192 * i,192 * 3,192,192) };
			}
		}
	}
	else if (this->type == 2)
	{
		if (this->facedirection == "front")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(64 * i,64 * 2,64,64) };
			}
		}
		else if (this->facedirection == "back")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(64 * i,64 * 0 ,64,64) };
			}
		}
		else if (this->facedirection == "left")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(64 * i,64 * 1,64,64) };
			}
		}
		else if (this->facedirection == "right")
		{
			for (int i = 0;i < totalframes;i++)
			{
				frames[i] = { sf::IntRect(64 * i,64 * 3,64,64) };
			}
		}
	}
	


	this->isSlashinganimationEnd = false;
	if (this->slashframe <= totalframes)
	{
		if (this->slashframetimer < frametimerMax)
		{
			this->appearance.setTextureRect(frames[this->slashframe - 1]);
			this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
			this->slashframetimer++;
		}
		else
		{
			this->slashframe++;
			this->slashframetimer = 0;
		}
	}
	else
	{
		this->appearance.setTextureRect(frames[0]);
		this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
		this->slashframe = 1;
		this->isSlashinganimationEnd = true;
		this->chosen = false;
	}
}

void Characters::walk()

{
	this->appearance.setTexture(this->walktextures);
	const int frametimerMax = 8;
	const int totalframes = 8;
	this->totalBlockToGo = this->path.size()-1; // the block where it set off do not counted
	this->BlocksHaveBeenTo;




	sf::IntRect frames[totalframes];
	if (this->facedirection == "front")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 2,64,64) };
		}
	}
	else if (this->facedirection == "back")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 0,64,64) };
		}
	}
	else if (this->facedirection == "left")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 1,64,64) };
		}
	}
	else if (this->facedirection == "right")
	{
		for (int i = 0;i < totalframes;i++)
		{
			frames[i] = { sf::IntRect(64 * i,64 * 3,64,64) };
		}
	}


	if (this->path.size() >= 2)
	{
		this->isWalkinganimationEnd = false;
		if (this->walkframe <= totalframes)
		{
			if (this->walkframetimer < frametimerMax)
			{
				this->appearance.setTextureRect(frames[this->walkframe - 1]);
				this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
				if (this->path[this->BlocksHaveBeenTo + 1].first - this->path[this->BlocksHaveBeenTo].first == 1)
				{
					this->facedirection = "right";
					this->detectingdirection = "right";
					this->appearance.move(1, 0);
				}
				else if (this->path[this->BlocksHaveBeenTo + 1].first - this->path[this->BlocksHaveBeenTo].first == -1)
				{
					this->facedirection = "left";
					this->detectingdirection = "left";
					this->appearance.move(-1, 0);
				}
				else if (this->path[this->BlocksHaveBeenTo + 1].second - this->path[this->BlocksHaveBeenTo].second == 1)
				{
					this->appearance.move(0, 1);
					this->facedirection = "front";
					this->detectingdirection = "front";
				}
				else if (this->path[this->BlocksHaveBeenTo + 1].second - this->path[this->BlocksHaveBeenTo].second == -1)
				{
					this->appearance.move(0, -1);
					this->facedirection = "back";
					this->detectingdirection = "back";
				}
				this->walkframetimer++;
			}
			else
			{
				this->walkframe++;
				this->walkframetimer = 0;
			}
		}
		else
		{
			this->appearance.setTextureRect(frames[0]);
			this->walkframe = 1;
			this->BlocksHaveBeenTo++;
			if (this->BlocksHaveBeenTo == this->totalBlockToGo)
			{
				this->isWalkinganimationEnd = true;
				this->chosen = false;
				this->BlocksHaveBeenTo = 0;
			}
		}
	}
	else
	{
		this->isWalkinganimationEnd = true;
		this->chosen = false;
		this->BlocksHaveBeenTo = 0;
	}
}
	
	
void Characters::hurtanimation()

{
	this->appearance.setTexture(this->hurttextures);
	const int frametimerMax = 10;
	int totalframes;
	unsigned int counter = 1;
	if (this->HP <= 0)
	{
		totalframes = 5;   //this is the animation when the character is dead
	}
	else
	{
		totalframes = 3;  // this is the regular hurt animation
	}

	std::vector<sf::IntRect> frames;
	for (int i=0; i<totalframes;i++)
		{
		frames.push_back( sf::IntRect(64 * i,64 * 0,64,64) );
		}
	
	if (this->hurtframe <= totalframes)
	{
		if (this->hurtframetimer < frametimerMax)
		{
			this->appearance.setTextureRect(frames[this->hurtframe - 1]);
			this->appearance.setOrigin(appearance.getLocalBounds().width / 2, appearance.getLocalBounds().height / 2);
			this->hurtframetimer++;
		}
		else
		{
			this->hurtframe++;
			this->hurtframetimer = 0;
		}
	}
	else
	{
		this->appearance.setTextureRect(frames[0]);
		this->hurtframe = 1;
		this->ChosenAsTarget = false;
	}
}



//logic function
void Characters::upgrade()
{

}


void Characters::attack(Characters* target)
{
	target->HP-=this->Damage;
}


void Characters::CheckAlive()
{
	if (this->HP <= 0)
	{
		this->alive = false;
	}
}