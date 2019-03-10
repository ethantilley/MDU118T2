#include "stdafx.h"
#include "Door.h"


Door::Door()
{
	// Setting the indentify for finding the picture in the file i want to load
	imageID = "Door";
	// Setting the type I want this to save out as
	type = "Door";

}


Door::~Door()
{
}

void Door::Save(std::ofstream & fs)
{
	GameObject::Save(fs);
	
}

void Door::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	
}

// That Update function that's called every frame.
void Door::Update(double deltaTime)
{

}