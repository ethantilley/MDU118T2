#pragma once
#include "GameFramework.h"
#include <string>
#include <iostream>
#include <fstream>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Draw(Gdiplus::Graphics& canvas);
	void Update(double deltaTime);

	virtual void Save(std::ofstream& fs);
	virtual void Load(std::ifstream& fs);

	virtual std::string GetType()
	{
		return "GameObjects." + type;
	}
	
public:

	char commer;

	Vector2i location;

	std::string type;

protected:

	std::string imageID;

};

