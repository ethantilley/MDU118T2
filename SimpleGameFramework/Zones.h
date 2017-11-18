#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>

class Zones : public GameObject
{
public:
	Zones();
	virtual ~Zones();
	
	bool increaseHealthZone = true, decreaseHealthZone = false, isPlayerInside = false;
	int healAmount = 10, damageAmount = 10;

	virtual void Zones::Save(std::ofstream & fs);
	virtual void Zones::Load(std::ifstream & fs);

	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

	// A Update function (a called every frame) 
	void Update(double deltaTime);
};

