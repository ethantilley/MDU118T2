#include "stdafx.h"
#include "GameInput.h"
#include "GameManager.h"

GameInput& GameInput::Instance()
{
	static GameInput instance;

	return instance;
}

GameInput::GameInput()
{
}

GameInput::~GameInput()
{
}

void GameInput::BeginPlay()
{

}

void GameInput::EndPlay()
{

}

void GameInput::Update(double deltaTime)
{
	Vector2i input = Vector2i::Zero;

	// The code below polls individual keys to determine if they are currently down.
	if (GetKeyState('W') & 0x8000)
	{
		if (!GameManagerInstance.inEditMode && GameManagerInstance.player->jumpCountDown <= 0 && GameManagerInstance.player->grounded)
		{
			GameManagerInstance.player->jumpCountDown = 0.5f;
			GameManagerInstance.player->grounded = false;
		}

		// These are the input for the canvas movement during the edit move.
		if (GameManagerInstance.inEditMode)
			input.Y = -GameManagerInstance.speed;
	}
	if (GetKeyState('A') & 0x8000)
	{

		input.X = -GameManagerInstance.speed;
	}
	if (GetKeyState('S') & 0x8000)
	{

		input.Y = GameManagerInstance.speed;
	}
	if (GetKeyState('D') & 0x8000)
	{

		input.X = GameManagerInstance.speed;
	}

	// Calling the function in the gamemanager and passing through the input that's being changed by the 'editModeCanvasMovementSpeed', depending on the keys being pressed.
	GameManagerInstance.MovementHappened(input);
}

void GameInput::OnKeyDown(UINT keyCode, UINT repeatCount)
{
	// NOTE: This method will not detect multiple simultaneous key presses.
	// To detect simultaneous presses you must use GetKeyState and check
	// each key of interest.




	switch (keyCode)
	{
	case 'W':
		break;
	case 'A':
		break;
	case 'S':
		break;
	case 'D':
		break;
	case 'Q':
		break;
	case 'E':
		break;
	case 'F':
		break;
	case 'C':
		break;
	case 'L':

		break;

	case VK_TAB:

		if (GameManagerInstance.player)
		{
			GameManagerInstance.inEditMode = !GameManagerInstance.inEditMode;
		}
		break;

	case VK_DELETE:
		// delete all in level.
		if (GameManagerInstance.inEditMode)
			GameManagerInstance.DeleteKeyPressed();
		break;

		//Editor Avitivate and deactivate 

	case VK_OEM_MINUS:
		GameManagerInstance.Save();
		DebugLog("Saving...");
		break;
	case VK_OEM_PLUS:
		GameManagerInstance.Load();
		DebugLog("Loading...");
		break;

	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	case VK_UP:
		break;
	case VK_DOWN:
		break;

	case VK_CONTROL:
		break;
	case VK_SPACE:
		break;
	case VK_SHIFT:
		break;


	case '1':
		// Same as Walls but for the Zones and you press 1
		if (GameManagerInstance.objToPlace != "Zone2")
		{
			GameManagerInstance.objToPlace = "Zone2";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(181, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(223, 573);
			DebugLog("Zone2 Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;
	case '2':
		// Same as Walls but for the Zones and you press 2
		if (GameManagerInstance.objToPlace != "Zone1")
		{
			GameManagerInstance.objToPlace = "Zone1";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(251, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(291, 572);
			DebugLog("Zone1 Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;

		
	case '3':
		// And if the objtoplace is not "Walls" 
		if (GameManagerInstance.objToPlace != "Walls")
		{
			// Than Set it to walls
			GameManagerInstance.objToPlace = "Walls";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(318, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(359, 572);
			DebugLog("Wall And Ground Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;
		
	case '4':

		// Same as Walls but for the Player and you press 4
		if (GameManagerInstance.objToPlace != "Players")
		{
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(586, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(427, 572);
			GameManagerInstance.objToPlace = "Players";
		
			DebugLog("Player Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;
				
	case '5':
		// Same as Walls but for the Key and you press 5
		if (GameManagerInstance.objToPlace != "Keys")
		{
			GameManagerInstance.objToPlace = "Keys";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(440, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(479, 572);
			DebugLog("Key Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;
	case '6':
		// Same as Walls but for the door and you press 6
		if (GameManagerInstance.objToPlace != "Doors")
		{
			GameManagerInstance.objToPlace = "Doors";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(490, 532);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(532, 572);
			DebugLog("Door Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;
	case '7':
		// Same as Walls but for the Enemys and you press 7
		if (GameManagerInstance.objToPlace != "Enemys")
		{
			GameManagerInstance.objToPlace = "Enemys";
			GameManagerInstance.UISelectorRecStartPoint = Vector2i(558, 531);
			GameManagerInstance.UISelectorRecEndPoint = Vector2i(600, 572);
			DebugLog("Enemys Object Selected. Left Click To Place, And Right Click To Remove.")
		}
		break;

	case VK_F1:
		break;
	case VK_F2:
		break;
	case VK_F3:
		break;
	case VK_F4:
		break;
	case VK_F5:
		break;
	case VK_F6:
		break;
	case VK_F7:
		break;
	case VK_F8:
		break;
	case VK_F9:
		break;
	case VK_F10:
		break;
	case VK_F11:
		break;
	case VK_F12:
		break;
	}
}

void GameInput::OnKeyUp(UINT keyCode, UINT repeatCount)
{
	// NOTE: This method will not detect multiple simultaneous key presses.
	// To detect simultaneous presses you must use GetKeyState and check
	// each key of interest.

	switch (keyCode)
	{
	case 'W':
		break;
	case 'A':
		break;
	case 'S':
		break;
	case 'D':
		break;
	case 'Q':
		break;
	case 'E':
		break;
	case 'F':
		break;
	case 'C':
		break;

	case VK_RIGHT:
		break;
	case VK_UP:
		break;
	case VK_DOWN:
		break;

	case VK_CONTROL:
		break;
	case VK_SPACE:
		break;
	case VK_SHIFT:
		break;



		// If the F1 button is pressed,
	case VK_F1:

		break;
	case VK_F2:

		break;
	case VK_F3:

		break;
	case VK_F4:

		break;
	case VK_F5:

		break;
	case VK_F6:
		break;
	case VK_F7:
		break;
	case VK_F8:
		break;
	case VK_F9:
		break;
	case VK_F10:
		break;
	case VK_F11:
		break;
	case VK_F12:
		break;
	}
}

void GameInput::OnLButtonDown(const Vector2i& point)
{
	DebugLog("OnLButtonDown at " << point.X << "," << point.Y);
	// If the left button is clicked than it runs the 'LeftButtonDown' function and sends out the out the point it was clicked throught that function. 
	if (GameManagerInstance.inEditMode)
		GameManagerInstance.LeftButtonDown(point);

}

void GameInput::OnLButtonUp(const Vector2i& point)
{
	DebugLog("OnLButtonUp at " << point.X << "," << point.Y);
}

void GameInput::OnLButtonDblClk(const Vector2i& point)
{
	DebugLog("OnLButtonDblClk at " << point.X << "," << point.Y);
}

void GameInput::OnRButtonDown(const Vector2i& point)
{
	DebugLog("OnRButtonDown at " << point.X << "," << point.Y);
}

void GameInput::OnRButtonUp(const Vector2i& point)
{
	DebugLog("OnRButtonUp at " << point.X << "," << point.Y);
}

void GameInput::OnRButtonDblClk(const Vector2i& point)
{
	DebugLog("OnRButtonDblClk at " << point.X << "," << point.Y);
}

void GameInput::OnMouseMove(const Vector2i& point)
{
}
