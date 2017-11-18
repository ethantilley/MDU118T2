#include "stdafx.h"
#include "GameObject.h"
#include "GameManager.h"
#include <string>
GameObject::GameObject()
{
	imageID = "Wall";
	type = "Wall";

}


GameObject::~GameObject()
{
}

void GameObject::Save(std::ofstream & fs)
{	
	//Saves out the type than,
	fs << GetType() << std::endl;

	// Saves out is location on the canvas for the x and y.
	fs << location.X << "," << location.Y << std::endl;

	// And also saves out the imageID, cause i said i would in doco.....
	fs << imageID << std::endl;	
}

void GameObject::Load(std::ifstream & fs)
{	
	// Loads out that location saved for the x and y.
	fs >> location.X >> commer >> location.Y;
	fs >> imageID;
}

void GameObject::Draw(Gdiplus::Graphics & canvas)
{
	// Setting up the canvas???
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);
	canvas.TranslateTransform((Gdiplus::REAL)location.X, (Gdiplus::REAL)location.Y);	

	//Getting the images identifyer and then,
	ImageWrapper* image = GameFrameworkInstance.GetLoadedImage(imageID);
	// Drawing it.
	GameFrameworkInstance.DrawImage(canvas, Vector2i(-20, -20), image);

	//Resetting the canvas or it'll do some weird shit and move everything...
	canvas.SetTransform(&transform);
}
// That Update function that's called every frame.
void GameObject::Update(double deltaTime)
{

}
