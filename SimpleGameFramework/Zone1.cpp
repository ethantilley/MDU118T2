#include "stdafx.h"
#include "Zone1.h"

// Aint gonna comment the same thing they all basically do the same thing. not actually the same thing but the same premise and i just would rather not..  thanks
Zone1::Zone1()
{
	type = "Zone1";
	imageID = "Zone1";
	healAmount = 10;
	damageAmount = 10;
	increaseHealthZone = true;
	decreaseHealthZone = false;
	isPlayerInside = false;
}
Zone1::~Zone1()
{
}

void Zone1::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << healAmount << "," << damageAmount << std::endl;
	fs << increaseHealthZone << "," << decreaseHealthZone << "," << isPlayerInside << std::endl;
}

void Zone1::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> healAmount >> commer >> damageAmount;
	fs >> increaseHealthZone >> commer >> decreaseHealthZone >> commer >> isPlayerInside;
}

void Zone1::Update(double deltaTime)
{
}
