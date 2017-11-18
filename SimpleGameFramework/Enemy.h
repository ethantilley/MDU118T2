#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy();
		
	float enemySpeed = 3.5;
	int enemyDamageToGive = 5, scoreToGive = 10, enemyCurrentHealth = 100, enemyMaxHealth = 100;

	//Vector2i location;
	
	// A Update function (a called every frame) 
	void Update(double deltaTime);

	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

	// Functions for indivisial saveing and loading the location etc.
	virtual void Save(std::ofstream& fs);
	virtual void Load(std::ifstream& fs);

public:

	// A vector for the location of the door.
	//Vector2i location;
};


