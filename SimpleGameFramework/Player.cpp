#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	imageID = "Player";
	type = "Plyr";

	speed = 5;
	jumpStrength = 5;
	currentHealth = 100;
	maxHealth = 100;
	damageToGive = 10;
	score = 0;	
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
	fs << speed << "," << jumpStrength << std::endl;

	fs << currentHealth << "," << maxHealth << "," << damageToGive << "," << score << std::endl;

	fs << hasKey << std::endl;

	
}

void Player::Load(std::ifstream & fs)
{
	//run loads from perant class.
	GameObject::Load(fs);

	// Loading out all the data
	fs >> speed >> commer >> jumpStrength;

	fs >> currentHealth >> commer >> maxHealth >> commer >> damageToGive >> commer >> score;

	fs >> hasKey;

	
}

// That Update function that's called every frame.
void Player::Update(double deltaTime)
{

}




















