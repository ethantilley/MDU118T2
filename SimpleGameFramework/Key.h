#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>
class Key : public GameObject
{
public:
	Key();
	virtual ~Key();

	// A Update function (a called every frame) 
	void Update(double deltaTime);


	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

	virtual void Save(std::ofstream& fs);
	virtual void Load(std::ifstream& fs);

public:
	// A vector for the location of the door.
	//Vector2i location;

};

