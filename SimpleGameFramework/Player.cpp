#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	imageID = "Player";
	type = "Plyr";
	
	gravityForce = 5;
	jumpForce = 6;
	currentHealth = 100;
	maxHealth = 100;
	hasKey = false;
}


Player::~Player()
{
}

void Player::Save(std::ofstream & fs)
{
	//run save from perant class.
	GameObject::Save(fs);

	//Saves out all tha veriables
	fs << gravityForce << "," << jumpForce << "," << currentHealth << "," << maxHealth << std::endl;

	fs << hasKey << std::endl;


}

void Player::Load(std::ifstream & fs)
{
	//run loads from perant class.
	GameObject::Load(fs);

	// Loading out all the data
	fs >> gravityForce >> commer >> jumpForce >> commer >> currentHealth >> commer >> maxHealth;

	fs >> hasKey;


}

// That Update function that's called every frame.
void Player::Update(double deltaTime)
{
	
}




















