#include "stdafx.h"
#include "GameManager.h"

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

void GameManager::BeginPlay()
{
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Wall.png"), "Wall"
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
	("Images/Zone1.png"), "Zone1"
	);

	// Getting the image for the Key through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Zone2.png"), "Zone2"
	);

	// Getting the image for the player through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/Player.png"), "Player"
	);

	// Getting the image for the Key through the files
	GameFrameworkInstance.LoadImageResource
	(AppConfigInstance.GetResourcePath
	("Images/UI.png"), "EditGameUI"
	);


}
// When the game is cloesed here I delete stuff to stop memory from leaking.
void GameManager::EndPlay()
{
	// Clearing up the memory in a function.
	CleanUpMemory();
}

void GameManager::Update(double deltaTime)
{
	if (player && player->jumpCountDown > 0)
		player->jumpCountDown -= (float)deltaTime;

	// If the end game bool is set to true then count down the timer, then if,
	if (endGame)
		endGameTimer -= (float)deltaTime;

	// The time is less than or equal to 0, Set the game to edit mode, reset the timer and end game bool.
	if (endGameTimer <= 0)
	{
		inEditMode = true;
		endGameTimer = 3;
		endGame = false;
	}
	if (!inEditMode)
	{
		// This is my enemy patrolling code
		// runs through the object that exist in the level
		for (GameObject* enemyToCheck : levelObjects)
		{
			// if theres a object that's of an enemy type
			if (enemyToCheck->type == "Enemy")
			{
#define enemyToCheckVar  dynamic_cast<Enemy*>(enemyToCheck)

				// check if the enemy has reached the same pos as any of the two vector2i's
				// if so it changes a bool
				if (enemyToCheckVar->location.X <= enemyToCheckVar->patrolPointA.X)
					enemyToCheckVar->positiveMovement = true;
				else if (enemyToCheckVar->location.X >= enemyToCheckVar->patrolPointB.X)
					enemyToCheckVar->positiveMovement = false;

				// checks if a bool is true and changes the direction to positive or negitive.
				enemyToCheckVar->location += Vector2i(enemyToCheckVar->positiveMovement ? enemy->enemySpeed : -enemy->enemySpeed, 0);
			}
		}
	}

	if (!inEditMode)
	{
		// Clamping the players health at its max health veriable
		if (player->currentHealth >= player->maxHealth)
			player->currentHealth = player->maxHealth;

		// My "gravity" solution
		// checks if the count down has been set if so revert the gravity for a set time.
		MovementHappened(Vector2i(0, player->jumpCountDown > 0 ? -player->jumpForce : player->gravityForce));

		// if the player lost all there health
		if (player->currentHealth <= 0)
		{
			player->currentHealth = 0;
			// end state... i suppose
			CleanUpMemory();
			inEditMode = true;
		}

	}

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
	if (inEditMode)
	{
		GameFrameworkInstance.DrawImage(canvas, Vector2i(0, 0), uiimage);
		GameFrameworkInstance.DrawRectangle(canvas, AABBi(Vector2i(UISelectorRecStartPoint), Vector2i(UISelectorRecEndPoint)), false, Gdiplus::Color::Red);

		// Displaying the file status
		GameFrameworkInstance.DrawTextW(canvas, Vector2i(10, 10), 15, "Arial", "The Current Level is: " + fileStatus, Gdiplus::Color::Black);
	}
	else
	{
		// drawing text that displays the players health
		GameFrameworkInstance.DrawTextW(canvas, Vector2i(10, 10), 20, "Arial", "Health: " + std::to_string(player->currentHealth), Gdiplus::Color::Red);
	}
}
// Called when pressing the '-' key.
void GameManager::Save()
{
	// Changing the file status
	fileStatus = "Saved";

	// Send out a file and calls it
	std::ofstream saveLevel("Objects.level");

	// Saving out the version number.
	saveLevel << versionNumber << std::endl;

	// Sending in the number of objects that are in the level.
	saveLevel << levelObjects.size() << std::endl;

	// loops over for the amount of objects.
	for (GameObject* GOToLoad : levelObjects)
	{
		// gos to the save function in the GameObject and runs that and what ever classes that are overiding doin other stuff.
		GOToLoad->Save(saveLevel);
	}

	// closing that save off
	saveLevel.close();
}
// Called when pressing the '+' key.
void GameManager::Load()
{
	// Changing the file status
	fileStatus = "Saved";

	// Clearing up the memory in a function.
	CleanUpMemory();

	// Resetting the level offset so it dosn't load weirdly.
	levelOffset = Vector2i::Zero;

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
		GameObject* gameObject = nullptr;

		// If you come across this sort ofstring then place a object from that class.

		//--------Wall Objects--------//
		if (GOType == "GameObjects.Wall")
			gameObject = new GameObject();

		//--------Door Objects--------//
		else if (GOType == "GameObjects.Door")
			gameObject = new Door();

		//--------Enemy Objects--------//
		else if (GOType == "GameObjects.Enemy")
		{
			gameObject = new Enemy();
			enemy = dynamic_cast<Enemy*>(gameObject);

		}
		//--------Key Objects--------//
		else if (GOType == "GameObjects.Key")
			gameObject = new Key();

		//--------Player Objects--------//
		else if (GOType == "GameObjects.Plyr")
		{
			gameObject = new Player();
			player = dynamic_cast<Player*>(gameObject);
		}
		//--------Zones Objects--------//
		else if (GOType == "GameObjects.Zone1")
		{
			gameObject = new Zone1();
			zone1 = dynamic_cast<Zone1*>(gameObject);
		}
		//--------Zones Objects--------//
		else if (GOType == "GameObjects.Zone2")
		{
			gameObject = new Zone2();
			zone2 = dynamic_cast<Zone2*>(gameObject);
		}
		// If there was one add it to the levelobjects list.
		if (gameObject)
		{
			gameObject->Load(loadLevel);
			levelObjects.push_back(gameObject);
		}
	}
	// If there's a enemy in the game then i here,
	// Seting the patrol points for enemy to move back and forth between
	if (enemy)
	{
		enemy->patrolPointA = Vector2i(enemy->location.X - enemy->patrolRange, enemy->location.Y);
		enemy->patrolPointB = Vector2i(enemy->location.X + enemy->patrolRange, enemy->location.Y);
	}

	loadLevel.close();
}

GameObject* newObjectPtr = nullptr;
// A function called if the left mouse button is cliccked,
void GameManager::LeftButtonDown(const Vector2i & point)
{
	// Changing the file status
	fileStatus = "UnSaved";

	// Setting up  a snapped img location for a grid effect for the placment of the objects.
	Vector2i imgSnapppedLocation;
	imgSnapppedLocation.X = objectGridSize * (((point.X - levelOffset.X) + clickGridSize) / objectGridSize);
	imgSnapppedLocation.Y = objectGridSize * (((point.Y - levelOffset.Y) + clickGridSize) / objectGridSize);

	DebugLog(point.Y);

	// Stoping the user from being able to place near the ui
	if (point.Y >= 519 || point.Y <= 34)
		return;

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
	// If there was a found object
	if (foundObject)
	{
		if (player == foundObject)
			player = nullptr;

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
	// Check if there's already a player, is there is then dont place one
	// casting the player as newObjectPtr so i can reference it (Same goes with the other if statements where i do this also)
	else if (objToPlace == "Players")
	{
		if (player)
			return;
		newObjectPtr = new Player();
		player = dynamic_cast<Player*>(newObjectPtr);

	}
	// !!--------Placement for Enemy Object--------!! //

	else if (objToPlace == "Enemys")
	{
		newObjectPtr = new Enemy();
		enemy = dynamic_cast<Enemy*>(newObjectPtr);

	}
	// !!--------Placement for Key Object--------!! //

	else if (objToPlace == "Keys")
		newObjectPtr = new Key();

	// !!--------Placement for Walls Object--------!! //
	else if (objToPlace == "Walls")
		newObjectPtr = new GameObject();

	// !!--------Placement for Zone1 Object--------!! //
	else if (objToPlace == "Zone1")
	{
		newObjectPtr = new Zone1();
		zone2 = dynamic_cast<Zone2*>(newObjectPtr);
	}
	else
	{
		newObjectPtr = new Zone2();
		zone2 = dynamic_cast<Zone2*>(newObjectPtr);
	}
	// setted there location to the snapped location and 
	newObjectPtr->location = imgSnapppedLocation;

	// If there's a enemy in the game then i here,
	// Seting the patrol points for enemy to move back and forth between
	if (enemy)
	{
		enemy->patrolPointA = Vector2i(enemy->location.X - enemy->patrolRange, enemy->location.Y);
		enemy->patrolPointB = Vector2i(enemy->location.X + enemy->patrolRange, enemy->location.Y);
	}
	// adds them to the list..
	levelObjects.push_back(newObjectPtr);

}
// Called if any of WASD was clicked
void GameManager::MovementHappened(const Vector2i & input)
{
	// Sets moves the levels offest by the input set in the game inout class.
	if (inEditMode)
		levelOffset -= input;
	else
	{
		// If the app is not in edit mode
		// The following is the collision for the player and tha movement.
		// creating a variable that i will use to destroy objects
		GameObject* objtodestroy = nullptr;

		// Setting the collision box or bounds for the player
		AABBi playerBounds(player->location + input - Vector2i(20, 20),
			player->location + input + Vector2i(20, 20));

		// Looping throught the level object list and checking for types and breaking out of the for loop if i want the player to not be able to collisde with the object.
		// also for some objects i set certain values and bools etc.
		for (GameObject* objsToCheck : levelObjects)
		{
			// If the object the loop ran into isn't the player then,
			if (objsToCheck->type != "Plyr")
			{
				// make bounds for that object				
				AABBi bounds(objsToCheck->location - Vector2i(17, 17),
					objsToCheck->location + Vector2i(17, 17));
				// If the the objects bounds intersected with the players bounds
				if (bounds.Intersects(playerBounds))
				{
					// if that object was the key 
					if (objsToCheck->type == "Key")
					{
						// Change a bool to true and destroy your self at the end of the loop
						player->hasKey = true;
						objtodestroy = objsToCheck;
						continue;
					}
					// if the object is the wall/ground im then, Setting a bool to true for the players ground check that stops the player from spaming 'W' and flying
					else if (objsToCheck->type == "Wall")
					{
						player->grounded = true;
						return;
					}
					// checking if the player has a key if so let the player walk through the door
					else if (objsToCheck->type == "Door")
					{
						if (player->hasKey == true)
						{
							endGame = true;
							break;
						}
					}
					// These check if the player is inside and if so take or give health from the player.
					else if (objsToCheck->type == "Zone1")
					{
						dynamic_cast<Zone1*>(objsToCheck)->isPlayerInside = true;
						if (dynamic_cast<Zone1*>(objsToCheck)->isPlayerInside)
							player->currentHealth += dynamic_cast<Zone1*>(objsToCheck)->healAmount / 10;
						break;
					}
					else if (objsToCheck->type == "Zone2")
					{
						dynamic_cast<Zone2*>(objsToCheck)->isPlayerInside = true;
						if (dynamic_cast<Zone2*>(objsToCheck)->isPlayerInside)
							player->currentHealth -= dynamic_cast<Zone2*>(objsToCheck)->damageAmount / 10;

						break;
					}
					else if (objsToCheck->type == "Enemy")
					{
						player->currentHealth -= dynamic_cast<Enemy*>(objsToCheck)->enemyDamageToGive / 5;

						return;
					}
				}
			}
		}
		// if there's objects to destroy then destoy them
		if (objtodestroy != nullptr)
		{
			levelObjects.remove(objtodestroy);
			delete objtodestroy;
			objtodestroy = nullptr;
		}
		// move the player if not collisions
		player->location += input;

		// move the "camera" with the player.
		levelOffset.X -= input.X;
	}
}

void GameManager::DeleteKeyPressed()
{
	CleanUpMemory();
}

void GameManager::CleanUpMemory()
{
	// Deleting Obect Ptr to stop memory leaks???
	delete gameObject;
	gameObject = nullptr;
	player = nullptr;
	// Looping throught the objects in level objetcs and deleting.
	for (GameObject* objToDraw : levelObjects)
	{
		delete objToDraw;
	}
	levelObjects.clear();
}

