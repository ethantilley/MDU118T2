#include "stdafx.h"
#include "Zone1.h"

Zone1::Zone1()
{
	type = "Zone1";
	imageID = "Zone1";
	healAmount = 10;
	isPlayerInside = false;
}
Zone1::~Zone1()
{
}

void Zone1::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << healAmount << std::endl;
	fs << isPlayerInside << std::endl;
}

void Zone1::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> healAmount;
	fs >> isPlayerInside;
}

void Zone1::Update(double deltaTime)
{

}
