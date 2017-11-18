#include "stdafx.h"
#include "Key.h"


Key::Key()
{
	// Setting the indentify for finding the picture in the file i want to load
	imageID = "Key";
	// Setting the type I want this to save out as
	type = "Key";
	keyPickedUP = false;
	
}


Key::~Key()
{
}
void Key::Save(std::ofstream & fs)
{
	GameObject::Save(fs);	
	fs << keyPickedUP << std::endl;
}

void Key::Load(std::ifstream & fs)
{
	GameObject::Load(fs);	
	fs >> keyPickedUP;
}

// That Update function that's called every frame.
void Key::Update(double deltaTime)
{

}