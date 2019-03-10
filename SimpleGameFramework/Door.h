#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>

class Door : public GameObject
{

public:
	Door();
	virtual ~Door();
	
	//// Function for drawing the object on the canvas
	//void Draw(Gdiplus::Graphics& canvas);
	// A Update function (a called every frame) 
	void Update(double deltaTime);
	
	virtual void Save(std::ofstream& fs);
	virtual void Load(std::ifstream& fs);
	
	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

};

