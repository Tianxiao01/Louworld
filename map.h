#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class Map
{
private:
	sf::Texture mapimage;

	

	//initialization
	void initTerrainSprites();
	void initMaptextures(std::string initmap);

public:

	sf::Sprite TerrainsArray[169];


	//constructor and destructor
	Map(std::string initmap);
	virtual ~Map();

	//accessories
	


	//funcitons 
	
};