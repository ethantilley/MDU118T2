#pragma once
#include "GameFramework.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <fstream>
class Camera : public GameObject
{
public:
	Camera();
	virtual ~Camera();



	virtual void Camera::Save(std::ofstream & fs);
	virtual void Camera::Load(std::ifstream & fs);

	// A function for getting  the type of the object.
	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}

	// A Update function (a called every frame) 
	void Update(double deltaTime);
};

