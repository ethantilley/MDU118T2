#include "stdafx.h"
#include "Door.h"


Door::Door()
{
	// Setting the indentify for finding the picture in the file i want to load
	imageID = "Door";
	// Setting the type I want this to save out as
	type = "Door";
	doorOpen = false;
	playerHasKey = false;

}


Door::~Door()
{
}

void Door::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	fs << doorOpen << "," << playerHasKey << std::endl;	
}

void Door::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> doorOpen >> commer >> playerHasKey;
}

// That Update function that's called every frame.
void Door::Update(double deltaTime)
{

}