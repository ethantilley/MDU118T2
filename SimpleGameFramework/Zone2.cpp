#include "stdafx.h"
#include "Zone2.h"

// Aint gonna comment the same thing they all basically do the same thing. not actually the same thing but the same premise and i just would rather not..  thanks
Zone2::Zone2()
{
	type = "Zone2";
	imageID = "Zone2";
	healAmount = 10;
	damageAmount = 10;
	increaseHealthZone = false;
	decreaseHealthZone = true;
	isPlayerInside = false;
}
Zone2::~Zone2()
{
}

void Zone2::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << healAmount << "," << damageAmount << std::endl;
	fs << increaseHealthZone << "," << decreaseHealthZone << "," << isPlayerInside << std::endl;
}

void Zone2::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> healAmount >> commer >> damageAmount;
	fs >> increaseHealthZone >> commer >> decreaseHealthZone >> commer >> isPlayerInside;
}

void Zone2::Update(double deltaTime)
{
}
