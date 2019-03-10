#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	// The players public variables	
	bool hasKey = false;
	bool grounded = true;
	int currentHealth = 100;
	int maxHealth = 100;	
	int gravityForce = 5;
	int jumpForce = 6;
	float jumpCountDown = 0;
	

	// A Update function (a called every frame) 
	void Update(double deltaTime);

	// Functions for indivisial saveing and loading the location etc.
	virtual void Save(std::ofstream& fs);
	virtual void Load(std::ifstream& fs);

	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}
};

