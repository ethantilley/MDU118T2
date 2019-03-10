#include "stdafx.h"
#include "Zone2.h"

Zone2::Zone2()
{
	type = "Zone2";
	imageID = "Zone2";
	damageAmount = 10;
	isPlayerInside = false;
}
Zone2::~Zone2()
{
}

void Zone2::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << damageAmount << std::endl;
	fs  << isPlayerInside << std::endl;
}

void Zone2::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> damageAmount;
	fs >> isPlayerInside;
}



void Zone2::Update(double deltaTime)
{

}
