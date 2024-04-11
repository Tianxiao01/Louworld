#include "map.h"

//initialization
void Map::initMaptextures(std::string initmap)
{
	if (!this->mapimage.loadFromFile(initmap))
	{
		std::cout << "map loading failed\n";
	};
}

void Map::initTerrainSprites()
{	
	for (int i = 1;i <= 169;i++)
	{
		this->TerrainsArray[i - 1] = sf::Sprite();
		this->TerrainsArray[i - 1].setTexture(this->mapimage);;
	}

	for (int i = 0;i < 13;i++)
	{
		for (int j = 0; j < 13;j++)
		{
			this->TerrainsArray[j + i * 13].setTextureRect(sf::IntRect(j*64,i*64,64,64));
			this->TerrainsArray[j + i * 13].setScale(0.98,0.98);   //(0.98, 0.98)
			this->TerrainsArray[j + i * 13].setPosition(j * 64, i * 64);
		}
	}
	//std::cout << TerrainsArray[0].getScale().x<<" "<< TerrainsArray[0].getScale().y << "\n";
		
}




//constructor and destructor
Map::Map(std::string initmap)
{
	this->initMaptextures(initmap);
	this->initTerrainSprites();
}

Map::~Map()
{

}

//accessaries

