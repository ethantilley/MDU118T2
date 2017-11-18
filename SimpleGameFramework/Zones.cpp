#include "stdafx.h"
#include "Zones.h"

// Aint gonna comment the same thing they all basically do the same thing. not actually the same thing but the same premise and i just would rather not..  thanks
Zones::Zones()
{
	type = "Zone";
	imageID = "Zone";
	healAmount = 10;
	damageAmount = 10;
	increaseHealthZone = true;
	decreaseHealthZone = false;
	isPlayerInside = false;
}
Zones::~Zones()
{
}

void Zones::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << healAmount << "," << damageAmount << std::endl;
	fs << increaseHealthZone << "," << decreaseHealthZone << "," << isPlayerInside << std::endl;
}

void Zones::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> healAmount >> commer >> damageAmount;
	fs >> increaseHealthZone >> commer >> decreaseHealthZone >> commer >> isPlayerInside;
}

void Zones::Update(double deltaTime)
{
}
