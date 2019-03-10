#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{


	// Setting the indentify for finding the picture in the file i want to load
	imageID = "Enemy";
	// Setting the type I want this to save out as
	type = "Enemy";
	enemySpeed = 2;
	enemyDamageToGive = 5;
	patrolRange = 100;
}

Enemy::~Enemy()
{
}

void Enemy::Save(std::ofstream & fs)
{
	GameObject::Save(fs);

	//Save all numeric data witt commas inbetween (nospaces)
	fs << enemySpeed << "," << patrolRange << std::endl;
}

void Enemy::Load(std::ifstream & fs)
{
	GameObject::Load(fs);
	fs >> enemySpeed >> commer >> patrolRange;
}

// That Update function that's called every frame.
void Enemy::Update(double deltaTime)
{

}