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

	int enemySpeed = 2, enemyDamageToGive = 5, patrolRange = 100;

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

	// vector2i's that are two patrol points i chose
	Vector2i patrolPointA;
	Vector2i patrolPointB;

	// Bool for whether the enemy will move left or right.
	bool positiveMovement = false;
	
};


