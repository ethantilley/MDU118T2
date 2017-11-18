#include "stdafx.h"
#include "GameManager.h"
//#include "GameInput.h"
#include "GameObject.h"
#include "Door.h"
#include "Player.h" 
#include "Enemy.h"
#include "Key.h"
#include "Zones.h"

GameManager& GameManager::Instance()
{
	static GameManager instance;

	return instance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

//const char* Image1 = "Image1";

void GameManager::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////
	// Begin example code

	// Loading the image files from the Images folder. and giveing it the unique name.

	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Wall.png"), "Wall"
	);

	// Getting the image for the player through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Player.png"), "Player"
	);

	// Getting the image for the Door through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Door.png"), "Door"
	);

	// Getting the image for the Enemy through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Enemy.png"), "Enemy"
	);

	// Getting the image for the Key through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Key.png"), "Key"
	);

	// Getting the image for the Key through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Zone.png"), "Zone"
	);


	//TODO,  isert zone 2 later


	// Getting the image for the Key through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/UI.png"), "EditGameUI"
	);




	objectPtr = new GameObject();
	objectPtr->location = Vector2i(20, 20);

	//End example code
}
// When the game is cloesed here I delete stuff to stop memory from leaking.
void GameManager::EndPlay()
{
	// Clearing up the memory in a function.
	CleanUpMemory();
}

void GameManager::Update(double deltaTime)
{

}

void GameManager::Render(Gdiplus::Graphics& canvas, const CRect& clientRect)
{
	// Save the current transformation of the scene

	// Setting the canvas.
	Gdiplus::Matrix transform;
	canvas.GetTransform(&transform);

	// Here is where the movement with W,A,S,D is acually being used to move the canvas.
	canvas.TranslateTransform((Gdiplus::REAL) levelOffset.X, (Gdiplus::REAL) levelOffset.Y);

	// These all call the draw function in the scripts of the object im trying to place.
	for (GameObject* objToDraw : levelObjects)
	{
		objToDraw->Draw(canvas);
	}

	// Restore the transformation of the canvas
	canvas.SetTransform(&transform);

	ImageWrapper* uiimage = GameFrameworkInstance.GetLoadedImage("EditGameUI");

	// Draw UI after here so it dosn't move.
	GameFrameworkInstance.DrawImage(canvas, Vector2i(0, 0), uiimage);

}
// Called when pressing the '-' key.
void GameManager::Save()
{
	// Send out a file and calls it
	std::ofstream saveLevel("Objects.level");

	// Saving out the version number.
	saveLevel << versionNumber << std::endl;

	// Sending in the number of objects that are in the level.
	saveLevel << levelObjects.size() << std::endl;

	// loops over for the amount of objects.
	for (GameObject* GOToLoad : levelObjects) {
		// gos to the save function in the GameObject and runs that and what ever classes that are overiding doin other stuff.
		GOToLoad->Save(saveLevel);
	}

	// closing that save off
	saveLevel.close();
}
// Called when pressing the '+' key.
void GameManager::Load()
{
	// Resetting the level offset so it dosn't load weirdly.
	levelOffset = Vector2i::Zero;

	// Clearing up the memory in a function.
	CleanUpMemory();


	// Grabbing the save file.
	std::ifstream loadLevel("Objects.level");
	
	// Making and Setting a int as the number of game objects in the level
	int gameObjectsToLoad = 0;
	gameObjectsToLoad = levelObjects.size();

	loadLevel >> versionNumber;
	loadLevel >> gameObjectsToLoad;
	// A loop that loops the amount fo objects that are in the level and places them.
	for (int i = 0; i < gameObjectsToLoad; i++)
	{
		// making a GameObjectType string and
		std::string GOType;
		// moving it into the load level file.
		loadLevel >> GOType;

		// setting a object point to places.
		GameObject* objectPtr = nullptr;

		// If you come across this sort ofstring then place a object from that class.

		//--------Wall Objects--------//
		if (GOType == "GameObjects.Wall")
			objectPtr = new GameObject();

		//--------Door Objects--------//
		else if (GOType == "GameObjects.Door")
			objectPtr = new Door();

		//--------Enemy Objects--------//
		else if (GOType == "GameObjects.Enemy")
			objectPtr = new Enemy();

		//--------Key Objects--------//
		else if (GOType == "GameObjects.Key")
			objectPtr = new Key();

		//--------Player Objects--------//
		else if (GOType == "GameObjects.Plyr")
			objectPtr = new Player();

		//--------Zones Objects--------//
		else if (GOType == "GameObjects.Zone")
			objectPtr = new Zones();


		// If there was one add it to the levelobjects list.
		if (objectPtr)
		{
			objectPtr->Load(loadLevel);
			levelObjects.push_back(objectPtr);
		}
	}

	loadLevel.close();
}

GameObject* newObjectPtr = nullptr;
// A function called if the left mouse button is cliccked,
void GameManager::LeftButtonDown(const Vector2i & point)
{
	// Setting up  a snapped img location for a grid effect for the placment of the objects.
	Vector2i imgSnapppedLocation;
	imgSnapppedLocation.X = objectGridSize * (((point.X - levelOffset.X) + clickGridSize) / objectGridSize);
	imgSnapppedLocation.Y = objectGridSize * (((point.Y - levelOffset.Y) + clickGridSize) / objectGridSize);

	// !!--------Placement for Walls Object--------!! //

	GameObject* foundObject = nullptr;
	// check if we've clicked on any level objects
	for (GameObject* objToTest : levelObjects)
	{
		// constructor bound for the click			
		AABBi bounds(objToTest->location - Vector2i(20, 20),
			objToTest->location + Vector2i(20, 20));

		// If there is a object where clicked than 
		if (bounds.Contains(imgSnapppedLocation))
		{
			// Add it to a found object and...
			foundObject = objToTest;
			break;
		}
	}
	if (foundObject)
	{
		// delete it
		levelObjects.remove(foundObject);
		delete foundObject;
		return;
	}

	// Checks to see if the string was set to these particular names.
	// And sets a newObjectPtr (a gameobject pointer), equal to the class corresponding to the name im checking.

	// !!--------Placement for Door Object--------!! //

	if (objToPlace == "Doors")
		newObjectPtr = new Door();

	// !!--------Placement for Player Object--------!! //

	else if (objToPlace == "Players")
		newObjectPtr = new Player();

	// !!--------Placement for Enemy Object--------!! //

	else if (objToPlace == "Enemys")
		newObjectPtr = new Enemy();

	// !!--------Placement for Key Object--------!! //

	else if (objToPlace == "Keys")
		newObjectPtr = new Key();

	// !!--------Placement for Walls Object--------!! //
	else if (objToPlace == "Walls")
		newObjectPtr = new GameObject();

	// !!--------Placement for Zones Object--------!! //
	else
		newObjectPtr = new Zones();

	// setted there location to the snapped location and 
	newObjectPtr->location = imgSnapppedLocation;

	// adds them to the list..
	levelObjects.push_back(newObjectPtr);

}
// Called if any of WASD was clicked
void GameManager::MovementHappened(const Vector2i & input)
{
	// Sets moves the levels offest by the input set in the game inout class.
	levelOffset -= input;
}

void GameManager::DeleteKeyPressed()
{
	CleanUpMemory();
}

void GameManager::CleanUpMemory()
{
	// Deleting Obect Ptr to stop memory leaks???
	delete objectPtr;
	// Looping throught the objects in level objetcs and deleting.
	for (GameObject* objToDraw : levelObjects)
	{
		delete objToDraw;
	}
	levelObjects.clear();
}


