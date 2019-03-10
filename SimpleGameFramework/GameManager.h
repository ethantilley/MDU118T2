#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "GameFramework.h"

// Includes for my game.
#include "Zone1.h"
#include "Zone2.h"
#include "Player.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Door.h"
#include "Key.h"



class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	static GameManager& Instance();

	/** BeginPlay is called when the game first launches. It is only called once per launch. */
	void BeginPlay();

	/** EndPlay is called when the game is closing down. It is only called once and only on exit. */
	void EndPlay();

	/**
	 * Update is called every frame. Update is always called before render
	 *
	 * @param deltaTime The time in seconds since Update was last called.
	 */
	void Update(double deltaTime);

	/**
	 * Render is called every frame after Update is called. All drawing must happen in render.
	 *
	 * @param [in,out] canvas The canvas.
	 * @param clientRect	  The rectangle representing the drawable area.
	 */
	void Render(Gdiplus::Graphics& canvas, const CRect& clientRect);

	// A function for saveing and loading all objects.
	void Save();
	void Load();




	virtual std::string GetType()
	{
		return "You Shouldn't be Seeing this.";
	}

	Vector2i levelOffset;

	Vector2i UISelectorRecEndPoint;
	Vector2i UISelectorRecStartPoint;


	AABBi bounds;
	
	// Following two ints are for the images snapped locations so the placement is more consistance and precise.

	// Keep the same as the objects general resolution size (40)
	int objectGridSize = 40;

	// Best to keep 20 to make clicking on the object to remove or clicking on a grid to place more fair and exact.
	int clickGridSize = 20;

	// The movement speed of the canvas/player using WASD keys.
	int speed = 4;

	// A value that states the version of this app.
	int versionNumber = 2;

	bool inEditMode = true;

	// A string for displaying the status of the file (wheather the its been saved or not).
	std::string fileStatus = "UnSaved";

	// A function for when i left click which i use to place and remove.
	void LeftButtonDown(const Vector2i& point);

	void MovementHappened(const Vector2i& input);

	void DeleteKeyPressed();

	void CleanUpMemory();	
	
	float endGameTimer = 3;
	bool endGame = false;

	// A string that i can change in the game input and depending on that sting ill place a object.
	std::string objToPlace = "Players";
	Player* player;
private:

	GameObject* gameObject;

	Zone2* zone2;
	Zone1* zone1;
	Enemy* enemy;
	// A list I use to store all the objects that I place and use it to remove. 
	std::list<GameObject*> levelObjects;

};

/**
 * Retrieves the GameManagerInstance for the game.
 *
 * @return The game manager instance
 */
#define GameManagerInstance (GameManager::Instance())
