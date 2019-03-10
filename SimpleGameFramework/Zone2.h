#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>

class Zone2 : public GameObject
{
public:
	Zone2();
	virtual ~Zone2();

	bool isPlayerInside = false;
	int damageAmount = 10;

	virtual void Zone2::Save(std::ofstream & fs);
	virtual void Zone2::Load(std::ifstream & fs);

	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

	// A Update function (a called every frame) 
	void Update(double deltaTime);
};

